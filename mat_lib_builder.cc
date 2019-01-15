#include <iostream>
#include <vector>

// HDF5
//#include "h5wrap.h"

// PyNE
#include <material.h>

// G4
#include <G4NistElementBuilder.hh>
#include <G4Types.hh>
#include <G4UnitsTable.hh>
#include "G4NistManager.hh"

typedef std::map<int, double> comp_map;
typedef comp_map::iterator comp_iter;

int pyne_nucid(int Z, int A, int I = 0) {
  // ZZZAAASSSS

  return I + A * 10000 + Z * 10000000;
}

pyne::Material G4_2_Pyne_Material(G4Material* G4mat) {
  pyne::Material Pmat = pyne::Material();
  const G4ElementVector G4elements = *G4mat->GetElementVector();
  const G4double* G4Frac = G4mat->GetFractionVector();
  for (auto i = 0; i < G4mat->GetNumberOfElements(); i++) {
    int Z = G4elements[i]->GetZ();
    int A = G4elements[i]->GetA();
    if (A < 0) {
      for (auto j = Z; j < Z * 3; j++) {
        comp_map pyne_element;
        double abondance = pyne::natural_abund(pyne_nucid(Z, j));

        if (abondance > 0) {
          pyne_element.insert(
              std::pair<int, double>(pyne_nucid(Z, A), abondance));
          Pmat = Pmat + pyne::Material(pyne_element, G4Frac[i]);
        }
      }
    }
  }

  return Pmat;
}

void write_nucids(std::string filename, std::string nucpath,
                  std::set<int> nuclides) {
  int nuc_size;
  hsize_t nuc_dims[1];
  nuc_size = nuclides.size();

  // Create the data if it doesn't exist
  int nuc_data[nuc_size];
  int n = 0;
  for (auto it = nuclides.begin(); it != nuclides.end(); it++) {
    nuc_data[n] = (*it);
    n++;
  }
  nuc_dims[0] = nuc_size;

  // Turn off annoying HDF5 errors
  H5Eset_auto2(H5E_DEFAULT, NULL, NULL);

  // Set file access properties so it closes cleanly
  hid_t fapl;
  fapl = H5Pcreate(H5P_FILE_ACCESS);
  H5Pset_fclose_degree(fapl, H5F_CLOSE_STRONG);
  // Create new/open datafile.
  hid_t db;
  if (pyne::file_exists(filename)) {
    bool ish5 = H5Fis_hdf5(filename.c_str());
    if (!ish5) throw h5wrap::FileNotHDF5(filename);
    db = H5Fopen(filename.c_str(), H5F_ACC_RDWR, fapl);
  } else {
    db = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, fapl);
  }

  hid_t nuc_space = H5Screate_simple(1, nuc_dims, NULL);
  hid_t nuc_set = H5Dcreate2(db, nucpath.c_str(), H5T_NATIVE_INT, nuc_space,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  H5Dwrite(nuc_set, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, nuc_data);
  H5Fflush(db, H5F_SCOPE_GLOBAL);
  // Close out the Dataset
  H5Tclose(db);
}

void append_to_nuclide_set(std::set<int>& nuclide_set,
                           pyne::comp_map my_compo) {
  for (auto it = my_compo.begin(); it != my_compo.end(); it++) {
    nuclide_set.insert(it->first);
  }
}

int main() {
  std::string filename = "mat_lib.h5m";
  std::string datapath = "/materials";
  std::string nucpath = "/nucid";
  
  // PyNE containers
  std::vector<pyne::Material> pyne_material_lib;
  std::set<int> nuclides;
  
  // G4 containers
  G4NistManager* manager = G4NistManager::Instance();
  std::vector<G4String> mat_list = manager->GetNistMaterialNames();

  for (int i = 0; i < mat_list.size(); i++) {
    G4Material* g4_mat = manager->FindOrBuildMaterial(mat_list[i]);
    double density = (g4_mat->GetDensity()) * CLHEP::cm3 / CLHEP::g;

    pyne::Material pyne_mat = G4_2_Pyne_Material(g4_mat);
    pyne_mat.metadata["name"] = g4_mat->GetName();
    pyne_mat.metadata["density"] = std::to_string(density);
    pyne_material_lib.push_back(pyne_mat);
    append_to_nuclide_set(nuclides, pyne_mat.comp);
  }

  write_nucids(filename, nucpath, nuclides);

}

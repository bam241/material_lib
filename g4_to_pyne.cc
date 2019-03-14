#include "mat_lib_builder.h"

#include <iostream>
#include <vector>



pyne::MaterialLibrary build_g4_matlib() {
  
  pyne::MaterialLibrary g4_mat_lib = pyne::MaterialLibrary();
  // PyNE containers
  std::vector<pyne::Material> pyne_material_vec;
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
    g4_mat_lib.add_material(pyne_mat);
  }
  return g4_mat_lib;
}

int pyne_nucid(int Z, int A, int I) {
  // ZZZAAASSSS nuclide name
  return I + A * 10000 + Z * 10000000;
}

// Convert a G4_material into a PyNE_material
pyne::Material G4_2_Pyne_Material(G4Material* G4mat) {
  pyne::Material Pmat = pyne::Material();
  const G4ElementVector G4elements = *G4mat->GetElementVector();
  const G4double* G4Frac = G4mat->GetFractionVector();
  // Loop over List of elements
  for (auto i = 0; i < G4mat->GetNumberOfElements(); i++) {
    int Z = G4elements[i]->GetZ();
    int A = G4elements[i]->GetA();
    // If not nuclide are there fill up with natural abondance
    if (A < 0) {
      comp_map pyne_element;
      for (auto j = Z; j < Z * 3; j++) {
        double abondance = pyne::natural_abund(pyne_nucid(Z, j));
        if (abondance > 0) {
          pyne_element.insert(
              std::pair<int, double>(pyne_nucid(Z, j), abondance));
        }
      }
      Pmat = Pmat + pyne::Material(pyne_element, G4Frac[i]);
    } else {
      // If single element add it.
      comp_map pyne_element;
      pyne_element.insert(std::pair<int, double>(pyne_nucid(Z, A), 1));
      Pmat = Pmat + pyne::Material(pyne_element, G4Frac[i]);
    }
  }

  return Pmat;
}


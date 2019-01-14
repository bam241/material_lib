#include <iostream>
#include<vector>
// G4
#include "G4NistMaterialBuilder.hh"
#include <G4NistElementBuilder.hh>
#include <material.h>
#include <G4Types.hh>

typedef std::map< int, double > 	comp_map;
typedef comp_map::iterator 	comp_iter;

int pyne_nucid(int Z, int A, int I=0){

// ZZZAAASSSS

  return I + A*10000 + Z*10000000;

}

pyne::Material G4_2_Pyne_Material(G4Material* G4mat){
 
  pyne::Material Pmat = pyne::Material();
  const G4ElementVector G4elements = *G4mat->GetElementVector();
  const G4double* G4Frac = G4mat->GetFractionVector();
  for (auto i = 0; i < G4mat->GetNumberOfElements(); i++){
      int Z = G4elements[i]->GetZ();
      int A = G4elements[i]->GetA();
      std::cout << "Frac: " << G4Frac[i] << std::endl;
      if( A < 0){ 
        for( auto j = Z; j < Z*3; j++){
          comp_map pyne_element;
          double abondance = pyne::natural_abund(pyne_nucid(Z,j));
          
          if (abondance > 0){
            std::cout << "ZA: " << Z << " " << j <<" Frac: " <<  abondance/100.*G4Frac[i]<< std::endl;
            pyne_element.insert( std::pair<int,double>(pyne_nucid(Z,A),abondance));
            Pmat = Pmat + pyne::Material(pyne_element, G4Frac[i]);
          }
        }
      }
    }

  return Pmat;
}



int main() {
  G4NistMaterialBuilder* manager = new G4NistMaterialBuilder(new G4NistElementBuilder(0));
  std::vector<G4String> mat_list = manager->GetMaterialNames();
  for (int i = 0; i < mat_list.size(); i++) {
    std::cout << mat_list[i] << std::endl;
      G4Material* g4_mat = manager->FindOrBuildMaterial(mat_list[i], true);
      double density = (g4_mat->GetDensity());
      
      
      pyne::Material pyne_mat = G4_2_Pyne_Material(g4_mat);
      pyne_mat.metadata["name"] density = g4_mat->GetDensity();
      std::cout << pyne_mat.mass << std::endl;
  }

}



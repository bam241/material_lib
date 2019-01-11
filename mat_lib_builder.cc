#include <iostream>
#include<vector>
// G4
#include "G4NistMaterialBuilder.hh"
#include <G4NistElementBuilder.hh>
#include <material.h>
#include <G4Types.hh>

typedef std::map< int, double > 	comp_map;
typedef comp_map::iterator 	comp_iter;

int main() {
  G4NistMaterialBuilder* manager = new G4NistMaterialBuilder(new G4NistElementBuilder(0));
  std::vector<G4String> mat_list = manager->GetMaterialNames();
  for (int i = 0; i < mat_list.size(); i++) {
      G4Material* g4_mat = manager->FindOrBuildMaterial(mat_list[i], true);
      double density = (g4_mat->GetDensity());

      std::cout << "Density: " << density << std::endl;
      if ( g4_mat->GetNumberOfElements () == 1) {
      double Z = (g4_mat->GetZ());
      std::cout << "Z: " << Z << std::endl;
      }
  }

  pyne::Material* pyne_mat = new pyne::Material();
}


pyne::Material G4_2_Pyne_Material(G4Material* g4mat){

  std::map< G4Material *, G4double > G4comp = g4mat->GetMatComponents ();

  for( auto G4it = G4comp.begin(); G4it != G4comp.end(); G4it++){
    pyne::Material Pmat = new pyne::Material();
    if( GetNumberOfElements () != 1){
      Pmat += G4_2_Pyne_Material(G4it->first) * G4it->second;
    }
    else {
      int Z = G4it->first->GetZ();
      int A = G4it->first->GetA();
      
      Pmat
    }

  }


}

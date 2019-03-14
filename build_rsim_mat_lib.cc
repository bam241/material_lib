#include "mat_lib_merge.h"
#include "g4_to_pyne.h"


int main(){
  
  pyne::MaterialLibrary g4_lib = build_g4_matlib();
  g4_lib = set_namespace(g4_lib, "G4_NIST");

  pyne::MaterialLibrary pyne_lib = pyne::MaterialLibrary() 


}

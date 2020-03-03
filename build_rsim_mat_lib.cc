#include "g4_to_pyne.h"
#include "mat_lib_merge.h"

int main() {
  pyne::MaterialLibrary g4_lib = build_g4_matlib();
  g4_lib = set_namespace(g4_lib, "G4_NIST");

  pyne::MaterialLibrary pyne_lib = pyne::MaterialLibrary();

    std::cout  << __LINE__ << std::endl;
  pyne_lib.from_hdf5("/home/mouginot/work/material_test/materialibrary.h5", "/materials" );
    std::cout  << __LINE__ << std::endl;
  //pyne_lib = set_namespace(pyne_lib, "pyne");
    std::cout  << __LINE__ << std::endl;
  
    std::cout  << __LINE__ << std::endl;
  //pyne_lib.merge(g4_lib);
    std::cout  << __LINE__ << std::endl;
  pyne::matname_set my_name_set = pyne_lib.get_keylist();
  std::cout << "SIZE " << my_name_set.size() << std::endl; 
  std::cout  << __LINE__ << std::endl;
  pyne_lib.write_hdf5("full_lib.h5m" , "/materials");
    std::cout  << __LINE__ << std::endl;
}

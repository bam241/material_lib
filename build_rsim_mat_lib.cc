#include "g4_to_pyne.h"
#include "mat_lib_merge.h"

int main() {
  pyne::MaterialLibrary g4_lib = build_g4_matlib();
  g4_lib = set_namespace(g4_lib, "G4_NIST");

  pyne::MaterialLibrary pyne_lib = pyne::MaterialLibrary();

  pyne_lib.from_hdf5(
      "/Users/mouginot/.local/lib/python3.6/site-packages/pyne/nuc_data.h5", "/material_library/materials" );
  pyne_lib = set_namespace(pyne_lib, "pyne");
  
  pyne_lib.merge(g4_lib);
  pyne::matname_set my_name_set = pyne_lib.get_keylist();
  pyne_lib.write_hdf5("full_lib.h5m");
}

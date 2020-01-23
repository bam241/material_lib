#ifndef _MAT_LIB_MERGE_
#define _MAT_LIB_MERGE_
#include "mat_lib_merge.h"

#include <iostream>
#include <vector>

pyne::MaterialLibrary merge(pyne::MaterialLibrary lib1,
                            pyne::MaterialLibrary lib2,
                            std::string merged_libname, std::string datapaths,
                            std::string nucpath) {
  pyne::MaterialLibrary merged_lib = lib1;

  pyne::matname_set mat_list2 = lib2.get_keylist();
  for (auto it = mat_list2.begin(); it != mat_list2.end(); it++) {
    pyne::Material mat_tmp = lib2.get_material(*it);
    merged_lib.add_material(mat_tmp);
  }
  return merged_lib;
}

pyne::MaterialLibrary set_namespace(pyne::MaterialLibrary lib, std::string name) {
  pyne::MaterialLibrary namespaced_lib = pyne::MaterialLibrary();

  pyne::matname_set mat_list = lib.get_keylist();
  for (auto it = mat_list.begin(); it != mat_list.end(); it++) {
    pyne::Material mat_tmp = lib.get_material(*it);
    mat_tmp.metadata["name"] =
        name + "::" +
        mat_tmp.metadata["name"].asString();
    namespaced_lib.add_material(mat_tmp);
  }
  return namespaced_lib;
}
#endif // end _MAT_LIB_MERGE_

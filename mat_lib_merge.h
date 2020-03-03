// PyNE
#include "pyne.h"

pyne::MaterialLibrary merge(pyne::MaterialLibrary lib1,
                            pyne::MaterialLibrary lib2,
                            std::string merged_libname = "merged_lib",
                            std::string datapaths1 = "",
                            std::string datapaths2 = "",
                            std::string nucpath1 = "",
                            std::string nucpath2 = "");

pyne::MaterialLibrary set_namespace(pyne::MaterialLibrary lib, std::string name);

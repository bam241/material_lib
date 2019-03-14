#ifndef _G4_TO_PYNE_
#define _G4_TO_PYNE_
// PyNE
#include <material.h>
#include <material_library.h>

// G4
#include "G4NistManager.hh"

typedef std::map<int, double> comp_map;
typedef comp_map::iterator comp_iter;

int pyne_nucid(int Z, int A, int I = 0);

pyne::Material G4_2_Pyne_Material(G4Material* G4mat);

pyne::MaterialLibrary build_g4_matlib();
#endif // end _G4_TO_PYNE_

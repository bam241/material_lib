// PyNE
#include <material.h>

// G4
#include "G4NistManager.hh"


typedef std::map<int, double> comp_map;
typedef comp_map::iterator comp_iter;


int pyne_nucid(int Z, int A, int I = 0);

pyne::Material G4_2_Pyne_Material(G4Material* G4mat);

void append_to_nuclide_set(std::set<int>& nuclide_set,
                           pyne::comp_map my_compo);

void write_nucids(std::string filename, std::string nucpath,
                  std::set<int> nuclides);

void write_mats(std::string filename, std::string datapath, std::string nucpath, std::vector<pyne::Material> materials);

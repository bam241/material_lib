from pyne.material import MaterialLibrary


def merge_material_library(merged_libname, matlibs, datapaths=[], nucpaths=[]):

    if len(datapaths) == 0:
        print("No datapaths provided, using \"/Materials\" as default.")
        for i in range(0, len(matlibs)):
            datapaths.append("/Materials")
    elif len(datapaths) != len(matlibs):
        print("!Error! Number of matlibs does not match number of datapaths")

    if len(nucpaths) == 0:
        print("No nucpaths provided, using \"/nucid\" as default.")
        for i in range(0, len(matlibs)):
            nucpaths.append("/nucpaths")
    elif len(nucpaths) != len(matlibs):
        print("!Error! Number of matlibs does not match number of nucpaths")

    merged_mat_library = MaterialLibrary()

    for index, (filename, datapath, nucpath) in enumerate(zip(matlibs, datapaths, nucpaths)):
        mat_lib = MaterialLibrary()
        mat_lib.from_hdf5(filename, datapath, nucpath)
        for item in mat_lib.items():
            merged_mat_library.__setitem__(item[0], item[1])

    merged_mat_library.write_hdf5(
        merged_libname, datapath="/materials", nucpath="/nucid")

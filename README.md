# n_assignment
assignment

# developed environment
* Windows 10 X64
* Visual Studio 2015

# used library & api
* Windows API
* Direct2D
* shapelib(http://shapelib.maptools.org/)
  * load shp, dbf files

# build
you can use Visual Studio solution or CMake.
## Visual Stuidio solution
open `assignments.sln` with visual studio and build it.

## CMake
```
mkdir build
cd build
cmake ..
```

# usage
## assignment3
1. open `MOCT_NODE.shp` and `MOCT_LINK.shp` with file open dialog.
2. wait loading
3. click right mouse button to open context menu
4. select start point & end point for finding path.
5. mouse wheel can change zoom level.
6. moving center of map with left click & drag

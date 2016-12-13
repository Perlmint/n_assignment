# n_assignment
assignment

# developed environment
* Windows 10 x64
* Visual Studio 2015

# used library & api
* Windows API
* Direct2D
* shapelib(http://shapelib.maptools.org/)
  * load shp, dbf files

# build
you can use Visual Studio solution file or CMake.
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
  - select start point & end point to find path.
5. change zoom level with mouse wheel scroll.
6. moving center of map with left click & drag

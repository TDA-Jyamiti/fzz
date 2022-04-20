# Fast Computation of Zigzag Persistence

This project implements the algorithms described in the following paper:

[Fast Computation of Zigzag Persistence](https://)

by Tamal K. Dey and Tao Hou.

## Group Information

This project is developed by [Tao Hou](https://taohou01.github.io) under the [CGTDA](https://www.cs.purdue.edu/homes/tamaldey/CGTDAwebsite/) research group at Purdue University lead by [Dr. Tamal K. Dey](http://web.cse.ohio-state.edu/~dey.8/).

## About the Implementation

This implemented algorithm converts input simplex-wise zigzag filtration to a **cell-wise non-zigzag** filtration of a Delta-complex with the same length, where the cells are copies of the input simplices. Then, the barcode of the original filtration is read from the barcode of the new cell-wise filtration. Details of the algorithm along with the proof can be seen in the paper. 

Computation of the statndard (non-zigzag) persistence is done by invoking the [phat](https://github.com/blazs/phat) library.

## Building

The building utilized [cmake](https://cmake.org/) software, and all building problems should be solvable by inspecting and changing the CMakeLists.txt file. Currently the building has two dependencies: one is boost, which is quite standard (please see CMakeLists.txt); the other is [phat](https://github.com/blazs/phat), for which users should first download the codes themselves and then include the header files of phat into the project by adding

```
include_directories( "path/to/phat/include" ) 
```

into CMakeLists.txt.

Commands for building are quite standard

```
cd [dir-to-fzz]
mkdir build
cd build
cmake ..
make
```

The software is developed and tested under MacOS. Compiling and running under other platforms shouldn't have any problems both the language and the compiling softwares are cross-platform.


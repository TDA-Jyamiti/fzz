# Fast Computation of Zigzag Persistence

This project implements the algorithm described in the following paper:

[Fast Computation of Zigzag Persistence](https://arxiv.org/pdf/2204.11080.pdf)

by Tamal K. Dey and Tao Hou, which appears on the 2022 European Symposium on Algorithms (ESA). The programming language used is C++, but you can also use **Python** to invoke the libary with the python bindings.

## Change Log

### 2023.10.01

- We are pleased to announce python bindings of FastZigzag

### 2022.08.16

- Wrap the computation into class `FZZ::FastZigzag` for easy invoking from C++ codes
- Filtration does not need to end with empty complex

## Group Information

This project is developed by [Tao Hou](https://taohou01.github.io) under the [CGTDA](https://www.cs.purdue.edu/homes/tamaldey/CGTDAwebsite/) research group at Purdue University lead by [Dr. Tamal K. Dey](https://www.cs.purdue.edu/homes/tamaldey/). Python bindings are due to [Soham Mukherjee](https://www.cs.purdue.edu/homes/mukher26/) who also belongs to the [CGTDA](https://www.cs.purdue.edu/homes/tamaldey/CGTDAwebsite/) research group.

## About the Implementation

This implemented algorithm converts the input simplex-wise zigzag filtration to a **cell-wise non-zigzag** filtration of a Delta-complex with the same length, where the cells are copies of the input simplices. Then, the barcode of the original filtration is read from the barcode of the new cell-wise filtration. Details of the algorithm along with the proof can be seen in the [paper](https://arxiv.org/pdf/2204.11080.pdf). 

Computation of the standard (non-zigzag) persistence is done by invoking the [phat](https://github.com/blazs/phat) library.

## Using Python Version
Assuming you have cloned the repository to a directory denoted as 'FZZ_REPO_DIR', do the following to install the FastZigzag python package:

```
cd [FZZ_REPO_DIR]
python -m pip install -e .
```

Check `test_fzz.py` for usage example.

We also recommend using anaconda ([homepage](https://www.anaconda.com/)) to manage your python development environment. The following several lines create a virtual environment dedicated for a test run of FastZigzag and install necessary packages. After that you can install FastZigzag as specified above to the dedicated environment.

```
conda create -n fzz python=3.7
conda activate fzz
conda install boost pybind11
```

### Python API
Import the `pyfzz` class by:


```python
from pyfzz import pyfzz
```

Create a class instance by:

```python
fzz = pyfzz()
```
Now you can use the instance to compute barcodes by invoking `fzz.compute_zigzag(data)`. `data` encodes the input zigzag filtration which should be a list of tuples where each tuple consists of an insertion (`i`) or deletion (`d`) and the simplex being inserted or deleted; the simplex is denoted as a list of vertices, increasingly ordered. For example, a small code snippet should look like this:

```python
fzz = pyfzz()
data = [('i', [0]), ('i', [1]), ('i', [0, 1]), ('d', [0, 1]), ('d', [1])]
bars = fzz.compute_zigzag(data)
```
`bars` contains the barcode, a list of tuples, where each tuple is of the form `(b, d, p)` with `b` denoting the birth index, `d` denoting the death index and `p` being the homology dimension. For additional details about the format of a filtration, please consult the section [Filtration format](#filtration-format).

Alternatively you can use `fzz.read_file('sample_filt')` to read the zigzag filtration and `fzz.write_file('sample_filt_pers', bars)` to write the barcodes to a file. The file format is described in the section [Filtration format](#filtration-format).




## C++ Building

Building the C++ programs utilized [cmake](https://cmake.org/) software, and all building problems should be solvable by inspecting and changing the CMakeLists.txt file. Currently the building has two dependencies: one is boost, which is quite standard (please see CMakeLists.txt); the other is [phat](https://github.com/blazs/phat), for which users should first download the codes themselves and then include the header files of phat into the project by adding

```
include_directories( "path/to/phat/include" ) 
```

into CMakeLists.txt.

Commands for building are quite standard:

```
cd [dir-to-fzz]
mkdir build
cd build
cmake ..
make
```

The software is developed and tested under MacOS and Linux. 

## Using the C++ Program

### Using from command line

The compiled software runs with the following command:

```
./fzz input_filtration_file
```

### Filtration format

A sample input filtration file is provided with the source codes:

```
i 0
i 1
i 2
i 0 1
i 0 2
i 1 2
i 0 1 2
d 0 1 2
d 1 2
d 0 1
```

Each line specifies an insertion (`i`) or deletion (`d`) and the simplex being inserted or deleted; the simplex is denoted as a list of vertices, increasingly ordered. An output file containing the barcode is written to the current working directory with name starting with that of the input file and ending with `_pers`.

The input format is as described in the [paper](https://arxiv.org/pdf/2204.11080.pdf), with the starting complex being empty (the last complex does *not* need to be empty). The filtration has the following numbering (`K_0` is empty):

```
F = K_0 <-> K_1 <-> ... <-> K_{m-1} <-> K_m
```

where each simplex-wise inclusion `K_i <-> K_{i+1}` (differing on only one simplex) is specified in the input filtration file. 

The output for the sample input is as follows:

```
0 2 3
0 3 4
1 6 6
0 1 10
0 10 10
1 8 8
```
Each line denotes an interval in the barcode, with the first number being the dimension and the rest being birth and death. Note that the birth and death are start and end of the **closed** integral interval, i.e., a line `p b d` indicates a persistence interval [*b*,*d*] in dimensional *p* starting with the complex `K_b` and ending with the complex `K_d`.

### Invoking from C++ source codes

To integrate the computation into your own source codes written in C++, you just need to include the source files `fzz.h` and `fzz.cpp` (which define the class `FZZ::FastZigzag`). The function which does the computation is the `compute` member function in `FZZ::FastZigzag`. See the provided example main function in `fzz_main.cpp` and the comments in `fzz.h` for the usage.

## License

THIS SOFTWARE IS PROVIDED "AS-IS". THERE IS NO WARRANTY OF ANY KIND. NEITHER THE AUTHORS NOR PURDUE UNIVERSITY WILL BE LIABLE FOR ANY DAMAGES OF ANY KIND, EVEN IF ADVISED OF SUCH POSSIBILITY. 

This software was developed (and is copyrighted by) the CGTDA research group at Purdue University. Please do not redistribute this software. This program is for academic research use only. This software uses the Boost and phat library, which are covered under their own licenses.

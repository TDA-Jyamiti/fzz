# Fast Computation of Zigzag Persistence

This project implements the algorithms described in the following paper:

[Fast Computation of Zigzag Persistence](https://)

by Tamal K. Dey and Tao Hou.

## Group Information

This project is developed by [Tao Hou](https://taohou01.github.io) under the [CGTDA](https://www.cs.purdue.edu/homes/tamaldey/CGTDAwebsite/) research group at Purdue University lead by [Dr. Tamal K. Dey](http://web.cse.ohio-state.edu/~dey.8/).

## About the Implementation

This implemented algorithm converts input simplex-wise zigzag filtration to a **cell-wise non-zigzag** filtration of a Delta-complex with the same length, where the cells are copies of the input simplices. Then, the barcode of the original filtration is read from the barcode of the new cell-wise filtration. Details of the algorithm along with the proof can be seen in the paper. 

Computation of the statndard (non-zigzag) persistence is done by invoking the [phat](https://github.com/blazs/phat) library.

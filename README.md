rankSynergy
===========

The rankSynergy is a C++ implementation of the algorithm proposed in the paper below for measuring synergistic effects between two gene sets.

Please mail friend1ws@gmail.com for problems or questions.



Paper
----------

"[A rank-based statistical test for measuring synergistic effects between two gene sets](http://bioinformatics.oxfordjournals.org/content/27/17/2399.full)", Shiraishi et al., Bioinformatics, 2011.


Prepare Input Data
----------

Two input files representing ranked genes (e.g., according to expression values) with indicator value (1: included in the gene set, 0: otherwise) is necessary.
For example, the following file

  1
  0
  0
  1
  1
  0
  1
  0
  0
  
shows that among 10 ranked genes, the 1st, 4th, 5th and 7th are included in the specific gene set.
Please check the E2F_rank.txt and NFY_rank.txt files, that show whether each gene has E2F and NFY motifs, respectively, in its promoter sequence,

Please note that the two input file are ranked by the same criterian.
Therefore, the 100th gene in the first and second input files is the same gene.

We recommend that the ratio of genes included in the gene set does not exceed 50%.


How to run
---

Compile C++ programs

	$ make

Just type the following command

	$ ./rankSynergy {the first input file> <the second input file> <the output file> <the number of MCMC cycles (optional)> <the number of burn-in cycles (optional)>

Then you will get the result in the output file.

under the specified output directory.



SetUp and test
----------
1.  compile the code (by typing 'make')
2.  Run rankSynergy as: ""rankrankSynergy E2F_rank.txt NFY_rank.txt output.txt"


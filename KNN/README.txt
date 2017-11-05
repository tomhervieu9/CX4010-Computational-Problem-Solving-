Isak Thomas: kmeans.c (KMEANS) - can be found in KMEANS folder
When running the code there are 3 command line arguments that need to be implemented: file to be read, the amunt of centroids,
										      Kmeans output file
I compile and run the code on the terminal in linux. 
To compile type to terminal: gcc -o kmeans kmeans.c -lm
-lm links the math.h library
to run type to terminal: ./kmeans input file number of centroids output file

Output file has format: [dim1, dim2, ..., dim n, label] with column headers as integers: [numRows, nuColumns, numLabels]

####################################

Thomas Hervieu: main.c (KNN) - can be found in KNN folder

The code is run with 4 arguments as state in the homework: testing input file, training input file (kmeans output),
							   KNN output file, double K (nearest-neighbor)
I use eclipse, so to compile simply ctr+b and click "run" to execute the program.

Output file has format: [dim1, dim2, ..., dim n, label]
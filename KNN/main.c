#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>

//function for allocating memory
double **malloc_matrix(double n1, double n2) {
    double **mat = NULL;  // pointer to the matrix

    //Checking for invalid inputs
    if (n1 <= 0 || n2 <= 0) {
    	printf("Invalid Inputs!");
    	return mat;
    }

    //creating array of pointers
    mat = (double**) malloc(sizeof(double*) * n1);

    //allocating memory for row of each pointer in pointer array
    for (int i =0; i < n1; i++) {
    	mat[i]= (double*) malloc(sizeof(double) * n2);
    }

    return mat;
}

//function that takes in an array of Euclidean distances and returns the indices
//of the 4 smallest distances
double* arr_min(double *numArr, double arrLen, double kMin) {
    double *minArr = NULL;
    minArr = (double*) malloc(sizeof(double) * kMin);
    //setting the initial array to -1s because 0s mess this up
    for (int w = 0; w < kMin; w++) {
    	minArr[w] = -1;
    }
	int i,j,k;
	for (j = 0; j < kMin; j++) {
		double entryArr[2];
		//went into office hours and only this worked
		entryArr[1] = 999999999999;

		for (i = 0; i < arrLen; i++) {
			int label = 0;
			for (k = 0; k < kMin; k++) {
				if (i == minArr[k]) {
					label = 1;
				}
			}
			if (label == 1) {
				continue; //skip over index already added to minArr
			}

			if (numArr[i] < entryArr[1]) {
				entryArr[0] = (double) i;
				entryArr[1] = numArr[i];
			}
		}
		minArr[j] = entryArr[0];
	}
	return minArr;
}

//finds the most frequently-appearing number in an array
double mode(double *arr, double len) {
   int max = 0, mCount = 0, i, j;
   for (i = 0; i < len; ++i) {
      int counter = 0;
      for (j = 0; j < len; ++j) {
         if (arr[j] == arr[i])
         ++counter;
      }
      if (counter > mCount) {
         mCount = counter;
         max = arr[i];
      }
   }
   return max;
}

//iterates through the array of indices and creates an array of their labels.
//Then, spits out the most frequently-appearing label in the array.
double assignLabel(double *indArr, double **trainer, double col, double kMin) {
    double *labelArr = NULL;
    labelArr = (double*) malloc(sizeof(double) * kMin);
    int i;

    for (i = 0; i < kMin; i++) {
    	labelArr[i] = trainer[(int)indArr[i]][(int)(col-1)];
    }

    return mode(labelArr, kMin);
}

//main method
int main(int argc, char* argv[]) {
	//initializing argument variables
	FILE *testingFile;
	FILE *TrainerFile;
	FILE *output;
	double kMin;

	testingFile = fopen(argv[1], "r");
	TrainerFile = fopen(argv[2], "r");
	kMin = (double) atoi(argv[4]);

	//checking for null files
	if (testingFile == NULL || TrainerFile == NULL) {
		printf("Error: File is null");
		exit(1);
	}

	int numDataTesting, dimTesting, numDataTrainer, dimTrainer, numLabelsTrainer;

	//column headers of input files
	fscanf(testingFile, "%d", &numDataTesting);
	fscanf(testingFile, "%d", &dimTesting);
	fscanf(TrainerFile, "%d", &numDataTrainer);
	fscanf(TrainerFile, "%d", &dimTrainer);
	fscanf(TrainerFile, "%d", &numLabelsTrainer);

	//checking that the 2 input files have the same dimensions - label columns in TrainingFile
	if (dimTesting != (dimTrainer - 1)) {
		printf("Error: Input files contain different dimensions");
		exit(1);
	}

	//initializing matrices
	double** dataTesting = malloc_matrix(numDataTesting, dimTesting);
	double** dataTrainer = malloc_matrix(numDataTrainer, dimTrainer);

	//fill Testing matrix with data from file
	for (int i = 0; i < numDataTesting; i++) {
		for (int j = 0; j < dimTesting; j++) {
			double entry;
			fscanf(testingFile, "%lf", &entry);
			dataTesting[i][j] = entry;
		}
	}

	//fill Training matri with data from file
	for (int i = 0; i < numDataTrainer; i++) {
		for (int j = 0; j < dimTrainer; j++) {
			double entry;
			fscanf(TrainerFile, "%lf", &entry);
			dataTrainer[i][j] = entry;
		}
	}

	//iterate throw every row of testing file and assign a label for each based on KNN algorithm
	double readArr[numDataTesting];
	for (int i = 0; i < numDataTesting; i++) {
		double *indexArr = NULL;
	    double *distArr = NULL;
	    double label = 0;
	    distArr = (double*) malloc(sizeof(double) * numDataTrainer);

	    //calculating euclidean distance
		for (int j = 0; j < numDataTrainer; j++) {
			double sum = 0;
			for (int k = 0; k < dimTesting; k++) {
				sum += pow(dataTrainer[j][k] - dataTesting[i][k], 2);
			}
			sum = sqrt(sum);
			distArr[j] = sum;
		}
		//finding indices of 4 minimum distances' points
		indexArr = arr_min(distArr, numDataTrainer, kMin);
		 //finding the 'winning' label
		label = assignLabel(indexArr, dataTrainer, dimTrainer, kMin);
		//assign label to array
		readArr[i] = label;
		free(distArr);
		free(indexArr);
	}

	//write the data to output file
	output = fopen(argv[3], "w+");
	fprintf(output, "%d %d %d\n", (int) numDataTesting, (int) dimTrainer, numLabelsTrainer);
	for (int i = 0; i < numDataTesting; i++) {
		for (int j = 0; j < dimTesting; j++) {
			fprintf(output, "%lf ", dataTesting[i][j]);
		}
		fprintf(output, "%d\n", (int) readArr[i]);
	}
	fclose(output);

	//free up memory for both matrices
	for (int i = 0; i < numDataTrainer; i++) {
		free(dataTrainer[i]);
	}
	free(dataTrainer);

	for (int i = 0; i < numDataTesting; i++) {
		free(dataTesting[i]);
	}
	free(dataTesting);

}

K-nearest neighbors (KNN) is a simple approach to classify new samples, and label them based on a labeled data set, e.g., one
produced by K-means. Specifically, KNN takes as input a labeled data set containing non-target
data points, and target data points that we wish to label. KNN first finds the k non-target data
points that are the closest to the target data item, and assigns a label to the target corresponding to
the majority among these k nearest non-target items. It is common to choose k to be odd to reduce
or eliminate the possibility of ties. Because KNN relies on a data set with known labels (also called
the training data set), it is referred to as a supervised learning algorithm.
To complete this part of the assignment, write a C program that implements KNN. It should take
the following command line parameters:

1. The name of the input file containing the non-target (training) set data produced by the Kmeans
program.

2. The name of a second input file containing the data to be classified.

3. The name of the output file where results produced by KNN are placed.

4. The value of k used by KNN (not to be confused with the parameter used by K-means)

The output should indicate the label/cluster assigned to each target input sample.
Data Set Format
Assume the input data file for the K-means program and the target data for the KNN program has
the following format:

num_items num_attrs

item1_attr1 item1_attr2 ... item1_attrm

item2_attr1 item2_attr2 ... item2_attrm
...

itemn_attr1 itemn_attr2 ... itemn_attrm

The first line contains the number of data items num_items and the number of attributes
num_attrs. The following num_items lines contain the data items, with each line containing
num_attrs attribute values.


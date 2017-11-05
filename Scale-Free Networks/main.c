#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//REMEMBER TO FREE SPACE

//defines Node object
struct Node {
    int indexV;
    struct Node* next;
};
// defines a node list object
struct NodeList {
    struct Node *head; //points to the first element in the list
};
//defines a graph object
struct Graph {
    int V; //order of the graph
    struct NodeList* array; //array of pointers to nodelist
};


//function to add a node to the adjacency list (connected vertices)
struct Node* createAdjacentNode(int indexV) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    //setting the parameters of the newly created node
    newNode->next = NULL;
    newNode->indexV = indexV;
    return newNode;
}

// creates a graph
struct Graph* createGraph(int V) {
	//allocate memory for graph
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V; //set size of graph

    // Create the array to access every node list
    graph->array = (struct NodeList*) malloc(V * sizeof(struct NodeList));

     // Initialize all node lists as null
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}


//checks to see if an element is in an array
int inArr(int value, int *arr, int size){
    for (int i = 0; i<size; i++) {
        if (arr[i] == value)
            return 1;
    }
    //returns an integer 1 if the element is in the array, 0 otherwise
    return 0;
}

// function used to print out the graph
void toString(struct Graph* graph) {
    for (int i = 0; i < graph->V; ++i) {
        struct Node* pointer = graph->array[i].head;
        printf("\n Node List of Vertex: %d\n", i);
        int counter = 0;
        while (pointer) {
            printf("-> %d", pointer->indexV);
            pointer = pointer->next;
            counter++;
        }
//        printf("\n Degree of vertex %d: %d\n", i, counter);

    }
}

// Adds an edge between two vertices
void createEdge(struct Graph* graph, int vertA, int indexV) {

	//add the link to the source node
    struct Node* newNode = createAdjacentNode(indexV);
    newNode->next = graph->array[vertA].head;
    graph->array[vertA].head = newNode;

    // add the link to the destination node
    newNode = createAdjacentNode(vertA);
    newNode->next = graph->array[indexV].head;
    graph->array[indexV].head = newNode;
}

//function that picks a node based off of preferential attachment
int PickNode (int *D, int N, int DTotal) {
	//uses a cumulative sum to establish ranges of varying sizes in an array
	int cumulativeSumArr[N];
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			cumulativeSumArr[i] = D[i];
		} else {
			cumulativeSumArr[i] = cumulativeSumArr[i-1] + D[i];
		}
	}
//	for (int i = 0; i < N; i++) {
//		printf("%d ", cumulativeSumArr[i]);
//	}
//	printf("\n");
	int index = (rand()/(1.0 + RAND_MAX)) * DTotal;
//	printf("%d ", index);
	int nodePicked;

	//using a random function to randomly choose a number
	//wider ranges ave a higher chance of getting picked
	for (int i = 0; i < N; i++) {
//		printf("%d", i);
		if (index <= cumulativeSumArr[i]) {
//			printf("  %d  ", cumulativeSumArr[i]);
			nodePicked = i;
			break;
		}
	}
//	printf("%d ", nodePicked);
//	printf("\n");
	return nodePicked;
}

//removes a node from the graph and edges connecting to other node lists
void removeVertexEdges(struct Graph* graph, int vertA, int V) {
	graph->array[vertA].head = NULL;

    for (int i = 0; i < graph->V; ++i) {
        struct Node* pointer = graph->array[i].head;
        if (pointer == NULL) {
        	continue;
        }
        if (pointer->indexV == vertA) { //must first check the head node
			printf(" removing edge connecting to %d from vertex %d\n", pointer->indexV, i);
			graph->array[i].head = pointer->next;
        }
        while (pointer) { //uses a pointer to loop through list and remove desired nodes
        	if (pointer->next == NULL) {
        		break;
        	}
			if (pointer->next->indexV == vertA) {
				printf(" removing edge connecting to %d from vertex %d\n", pointer->next->indexV, i);
				pointer->next = pointer->next->next;
				break;
			}

            pointer = pointer->next;
        }


    }
}

//chooses a random node from the graph
//recursion is used so that a node that has been deleted (nullified is never chosen)
int pickRandomNode(struct Graph* graph, int V) {
	int index = (rand()/(1.0 + RAND_MAX)) * V;
	if (graph->array[index].head != NULL) {
		return index;
	} else {
		return pickRandomNode(graph, V);
	}
}


//Breadth First Search Procedure
int BFS(struct Graph* graph, int V, int *indexArr, int K) {
	int count = 0;
	for (int i = 0; i < V; i++) {
		if (indexArr[i] >= 0) {
			struct Node* pointer = graph->array[indexArr[i]].head;
			//nodes (indexes) already in the array are considered to be visited and are ignored
			//
			if (inArr(pointer->indexV, indexArr, V) == 0) {
				indexArr[++count] = pointer->indexV;
			}
			while (pointer) {
				if (pointer->next == NULL) {
					break;
				}
				if (inArr(pointer->next->indexV, indexArr, V)==0) {
						indexArr[++count] = pointer->next->indexV;				}
				pointer = pointer->next;
			}
		}
	}

//	// K is the # of nodes that are supposed to be left in the whole graph
//	//If # of nodes found == K, then graph is still connected, else it's not
//	// return 0 or 1 depending on if graph is connected
	if ((count + 1) == K) {
		printf("connected");
		return 0;
	} else {
		printf("disconnected");
		return 1;
	}
}

//main method
int main(int argc, char* argv[]) {
	//seed
	srand(time(NULL));

	//manually create the 5-connected graph since instructions let us
	for (int j = 0; j < 1; j++) {
		int V = (int) atoi(argv[1]);
		struct Graph* graph = createGraph(V);
		createEdge(graph, 0, 1);
		createEdge(graph, 0, 2);
		createEdge(graph, 0, 3);
		createEdge(graph, 0, 4);
		createEdge(graph, 1, 2);
		createEdge(graph, 1, 3);
		createEdge(graph, 1, 4);
		createEdge(graph, 2, 3);
		createEdge(graph, 2, 4);
		createEdge(graph, 3, 4);

		int *degreeArr = (int*) malloc(sizeof(int) * V);
		degreeArr[0] = 4;
		degreeArr[1] = 4;
		degreeArr[2] = 4;
		degreeArr[3] = 4;
		degreeArr[4] = 4;

		int degreeSum = 20;
		for (int i = 5; i < V; i++) {
			int nodePicked = PickNode(degreeArr, i, degreeSum);
			createEdge(graph, nodePicked, i); //adds an edge to a random vertex already in the graph
			degreeArr[i] = 1;
			degreeArr[nodePicked]++;
			degreeSum += 2; //one edge adds two degrees to the graph
		}

	    toString(graph);

		int isConnected = 0;
		int delNode;
		int count = 1;
		while (isConnected == 0) {
			delNode = pickRandomNode(graph, V);
			 printf("\n--------------------\n");
			removeVertexEdges(graph, delNode, V);
			 printf("\n--------------------\n");

			//needed to pass into BFS
			int *indexArr = NULL;
			indexArr = (int*) malloc(sizeof(int) * V);
			for (int i = 0; i < V; i++) {
				indexArr[i] = -5; //initialized as negative so nonzero and easy to differentiate
			}
			//identifies the source node
			indexArr[0] = pickRandomNode(graph, V);

			//calling BFS
			isConnected = BFS(graph, V, indexArr, V - count);
			count++;
			toString(graph);
			free(indexArr);
		}

		count--;
		//prints number of removals needed to cut graph
		printf("\n\nTotal Vertices Removed: %d", count);

		//free space
		for (int i = 0; i < V; i++) {
			free(graph->array[i].head);
		}
		free(graph);

	}

    return 0;
}

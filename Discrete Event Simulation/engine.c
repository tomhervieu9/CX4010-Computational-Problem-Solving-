//Standard IO, Standard C library, Math and Simulation Header
#include <stdio.h>
#include <stdlib.h>
#include "sim.h"
#include <math.h>
/*
Data Structures: Include BinaryHeap file
*/

typedef struct Event {
	double timestamp;		// event timestamp
    void *AppData;			// pointer to event parameters
	struct Event *Next;		// priority queue pointer
} Event;

// Simulation clock variable
double Now = 0.0;

// Future Event List
// Use an event structure as the header for the future event list (priority queue)
struct Event FEL ={-1.0, NULL, NULL};

/////////////////////////////////////////////////////////////////////////////////////////////
// Prototypes for functions used within the Simulation Engine
/////////////////////////////////////////////////////////////////////////////////////////////

// Function to print timestamps of events in event list
void PrintList (void);

// Function to remove smallest timestamped event
struct Event *Remove (void);

/////////////////////////////////////////////////////////////////////////////////////////////
// Simulation Engine Functions Internal to this module
/////////////////////////////////////////////////////////////////////////////////////////////

// Remove smallest timestamped event from FEL, return pointer to this event
// return NULL if FEL is empty
struct Event *Remove (void)
{
    struct Event *e;

    if (FEL.Next==NULL) return (NULL);
    e = FEL.Next;        // remove first event in list
    FEL.Next = e->Next;
    return (e);
}

// Print timestamps of all events in the event list (used for debugging)
void PrintList (void)
{
    struct Event *p;

    printf ("Event List: ");
    for (p=FEL.Next; p!=NULL; p=p->Next) {
        printf ("%f ", p->timestamp);
    }
    printf ("\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Simulation Engine functions visible to simulation application
/////////////////////////////////////////////////////////////////////////////////////////////

// Return current simulation time
double CurrentTime (void)
{
    return (Now);
}

// Schedule new event in FEL
// queue is implemented as a timestamp ordered linear list
void Schedule (double ts, void *data)
{
    struct Event *e, *p, *q;

    // create event data structure and fill it in
    if ((e = malloc (sizeof (struct Event))) == NULL) exit(1);
    e->timestamp = ts;
    e->AppData = data;

    // insert into priority queue
    // p is lead pointer, q is trailer
    for (q=&FEL, p=FEL.Next; p!=NULL; p=p->Next, q=q->Next) {
        if (p->timestamp >= e->timestamp) break;
    }
    // insert after q (before p)
    e->Next = q->Next;
    q->Next = e;
}

// Function to execute simulation up to a specified time (EndTime)
void RunSim (double EndTime)
{
    struct Event *e;

    printf ("Initial event list:\n");
    PrintList ();

    // Main scheduler loop
    while ((e=Remove()) != NULL) {
        Now = e->timestamp;
        if (Now > EndTime) break;
        EventHandler(e->AppData);
        free (e);    // it is up to the event handler to free memory for parameters
        PrintList ();
    }
}

// Uniformly distributed random value between 0 and 1
double urand(void) {
	double x = ((double) rand() / (double) RAND_MAX);
	return x;
}

double randexp(double mean) {
	double x = -1 * mean * (log(1.0 - urand()));
	return x;
}


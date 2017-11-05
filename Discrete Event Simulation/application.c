#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "sim.h"


//Defining each event structure
struct EventData {
    int EventType; //which event is occuring
    double arrivalTime; //time at which car arrives at bridge
//    double waitTime; //time the car waits at the bridge
    int direction; //which direction is car moving in: 1-north, 2-south
    int index; //position of the car in the group
};


//status Types, global variables
double waitingArr[500];
int counter;
int status;     // status of the bridge: 0-empty, 1-north, 2-south
int onBridgeGroup = 0;   //num of cars on bridge in group
int offBridgeGroup = 0;  // num cars not yet on bridge but in the group entering
int numInGroup = 0;    // number of the car in its passing group
int waitingGroup1 = 0; // number of cars waiting on the opposite side
int waitingGroup2 = 0; // number of cars in the second group
double NB_InterArrivalTime = 10.0; // average inter-arrival time for north
double SB_InterArrivalTime = 20.0; // average inter-arrival time for south


// Function Prototypes
void EventHandler (void *data);
void arrival (struct EventData *e); // Arrival at bridge
void start (struct EventData *e);   // starting to cross bridge
void finish (struct EventData *e);    // finish crossing the bridge
double uniRand(double min, double max); //uniform random function


// Random Function
double uniRand(double a, double b) {
    double waitT = ((double) rand()/RAND_MAX)*(b-a) + a;
    return waitT;
}


//Main Event Handler Process
void EventHandler (void *data) {
  struct EventData *d;
    // coerce type
    d = (struct EventData *) data;

    // call function depending on event assigned
    if (d->EventType == 1) {arrival(d);
    } else if (d->EventType == 2) {start(d);
    } else if (d->EventType == 3) {finish(d);
    } else {
      fprintf (stderr, "Illegal event found\n");
      exit(1);
    }
    free(d);
}

//EventHandler for Arrival
void arrival (struct EventData *e) {
  if (e->EventType != 1) {
    fprintf(stderr, "Unexpected event type\n");
    exit(1);
  }

  // schedules another Arrival event in the same for later
  struct EventData *d;
  double ts;
  if((d=malloc(sizeof(struct EventData)))==NULL) {
      fprintf(stderr, "malloc error\n");
      exit(1);
  }
  d->EventType = 1;
  d->direction = e->direction;
  if (d->direction == '1') {
      ts = CurrentTime() + randexp(NB_InterArrivalTime);
  } else if (d->direction == '2') {
      ts = CurrentTime() + randexp(SB_InterArrivalTime);
  } else {
      ts = CurrentTime();
  }
  d->arrivalTime = ts;
  d->index = ++numInGroup;
  Schedule(ts, d);
  printf("\nCar %d Arrival at Time t = %f\n", d->index, ts);

//bridge is empty at Arrival then schedule a time for when car starts crossing the bridge
  if (status == '0') {
      status = e->direction;
      offBridgeGroup++;
      struct EventData *d;
      double ts;
      if((d=malloc(sizeof(struct EventData)))==NULL) {
          fprintf(stderr, "malloc error\n");
          exit(1);
      }
      ts = CurrentTime();
      d->EventType = 2;
      d->direction = e->direction;
      d->arrivalTime = e->arrivalTime;
      d->index = e->index;
      Schedule(ts, d);
      printf("\nCar %d Start crossing at Time t = %f\n", d->index, ts);
  } else if (status == e->direction) {

// if there are no cars remaining off the bridge but cars on the bridge
      if (offBridgeGroup == 0 && onBridgeGroup > 0) {
          waitingGroup2++; //the car must wait
      } else if (offBridgeGroup > 0 && onBridgeGroup > 0) {
          offBridgeGroup++; //the car crosses with the currently crossing group

  // schedule an Entry event in the future
          struct EventData *d;
          double ts;
          ts = CurrentTime() + uniRand(2.5, 3.5); //adding random time shift
          if((d=malloc(sizeof(struct EventData)))==NULL) {
              fprintf(stderr, "malloc error\n");
              exit(1);
          } else { //setting the new parameters for the car
              d->EventType = 2;
              d->direction = e->direction;
              d->arrivalTime = e->arrivalTime;
              d->index = e->index;
              Schedule(ts, d);
              printf("\nCar %d Start crossing at Time t = %f\n", d->index, ts);
          }
      }
// if the status is the opposite of direction of the arriving car
  } else if (status != '0' && status != e->direction) {
      waitingGroup1++;
  }
  printf("\nProcessed arrival at time %f, status = %c, Group Size = %d\n\n", CurrentTime(), status, onBridgeGroup + offBridgeGroup);
}

//Start EventHandler//////////////////////////////////////////////////////////////
void start (struct EventData *e) {
    if (e->EventType != 2) {
        fprintf(stderr, "Unexpected event type \n");
        exit(1);
    }
    onBridgeGroup++; //car shifts to the other group sum
    offBridgeGroup--;

  // scheduling a finish crossing time for later
    struct EventData *d;
    double ts;
    if((d=malloc(sizeof(struct EventData)))==NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    ts = CurrentTime() + uniRand(40,45);
    waitingArr[counter++] = CurrentTime() - e->arrivalTime;
    d->EventType = 3;
    d->arrivalTime = e->arrivalTime;
    d->direction = e->direction;
    d->index = e->index;

    Schedule(ts, d);
    printf("\nFinish  scheduled for Time t = %f\n", ts);
    printf("\nProcessed Starting at time %f, status = %c, Group Size = %d\n\n", CurrentTime(), status, onBridgeGroup + offBridgeGroup);
}

//The finish handler events
void finish (struct EventData *e) {
    if ((e->EventType) != 3) {
        fprintf(stderr, "Unexpected event type \n");
        exit(1);
    }
    onBridgeGroup--; //1 car leaves the bridge in the group

    //if the system contains no cars currently
    if( (onBridgeGroup == 0) && (offBridgeGroup == 0) && (waitingGroup1 == 0) && (waitingGroup2 == 0)) {
        status = '0';                                // set the status to 0
        printf("The system is empty!!");
    } // if there are no cars in the current traveling group but there are car waiting on the other side
    else if ( (onBridgeGroup == 0) && (offBridgeGroup == 0) && (waitingGroup1 > 0)) {
        //switch the status of the bridge
        if (status == '1') {
            status = '2';
        } else if (status == '2') {
            status = '1';
        }
        // scheduling a start time for cars on the opposite side
        struct EventData *d;
        double ts;
        double initTime = CurrentTime();

        for (int i = 0; i < waitingGroup1; i++) {
            if((d=malloc(sizeof(struct EventData)))==NULL) {
                fprintf(stderr, "malloc error\n");
                exit(1);
            } else {
                d->EventType = 2;
                if (status == '2') {
                    d->direction = '1';

                } else if (status == '1') {
                    d->direction = '2';
                }
                ts = initTime + uniRand(2.5, 3.5);
                Schedule(ts, d);
                printf("\nEntry Scheduled at Time t = %f\n", ts);
                initTime = ts;
            }
        }
        //shifting the waiting groups since one 'cycle' has passed
        offBridgeGroup = waitingGroup1;
        waitingGroup1 = waitingGroup2;
        waitingGroup2 = 0;

// if there are cars on the same side waiting to cross
    } else if ( (onBridgeGroup == 0) && (offBridgeGroup == 0) && (waitingGroup1 == 0) && (waitingGroup2 > 0)) {
   // schedule Entry event for each car in second waiting group
        struct EventData *d;
        double ts;
        for (int i = 0; i < waitingGroup2; i++) {
            double initTime = CurrentTime();
            if((d=malloc(sizeof(struct EventData)))==NULL) {
                fprintf(stderr, "malloc error\n");
                exit(1);
            }
            d->EventType = 2;
            d->direction = status;
            ts = initTime + uniRand(2.5, 3.5);
            Schedule(ts, d);
            printf("\nStarting time scheduled for Time t = %f\n", ts);
            initTime = ts;
            offBridgeGroup = waitingGroup2;
            waitingGroup2 = 0;
        }
        printf("\nProcessed Exit at time %f, status = %c, Group Size = %d\n\n", CurrentTime(), status, (onBridgeGroup + offBridgeGroup));

    }

}


////////////////////MAIN////////////////////////////
int main (void) {
  //declaring initial events triggering north and south event chains
    struct EventData *d;
    struct EventData *e;

    //schedule north chain
    if ((d=malloc(sizeof(struct EventData))) == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    status = '0';
    d->EventType = 1;
    d->arrivalTime = 0.0;
    d->direction = '1';
    d->index = ++numInGroup;
    Schedule (0.0, d);
    printf("\nArrival Scheduled at Time t = %f\n", 0.0);

    //schedule south chain
    if ((e=malloc(sizeof(struct EventData))) == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    e->EventType = 1;
    e->direction = '2';
    e->arrivalTime = 5.0;
    e->index = ++numInGroup;
    Schedule (5.0, e);
    printf("\nArrival Scheduled at Time t = %f\n", 5.0);


    RunSim(300.0);

    for (int i = 0; i < 200; i++) {
        printf("%lf\n", waitingArr[i]);
    }

    double min, max;
    int c = 0;
    for (int i = 0; i < 200; i++) {
        if (waitingArr[i] > 1000 || waitingArr[i] < 0) {
            printf("error found");
            continue;
        }
        if (waitingArr[i] != 0) {
            c++;
        }
        if (i == 1) { //not including the first car that never has to wait
            min = waitingArr[i];
            max = waitingArr[i];
        }
        else if (waitingArr[i] < min && waitingArr[i] != 0) {
            min = waitingArr[i];
        } else if (waitingArr[i] > max) {
            max = waitingArr[i];
        }
    }

    double sum = 0;
    for (int i = 1; i < c+1; i++) {
        if (waitingArr[i] > 1000 || waitingArr[i] < 0) {
            printf("error found2\n");
            continue;
        }
        sum += waitingArr[i];
    }

    double average = sum / (double) c;
    printf("%lf\n", average); //computes average waiting time
    printf("%lf\n%lf", min, max); //computes minimum and maximum waiting times
}

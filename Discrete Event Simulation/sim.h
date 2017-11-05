//
//  Sample Discrete Event Simulation
//
//  Created by Richard Fujimoto on 9/24/17.
//  Copyright © 2017 Richard Fujimoto. All rights reserved.
//

//
// Application Independent Simulation Engine Interface
//
//
// Function defined in the simulation engine called by the simulation application
//

// Call this procedure to run the simulation indicating time to end simulation
void RunSim (double EndTime);

// Schedule an event with timestamp ts, event parameters *data
void Schedule (double ts, void *data);

// This function returns the current simulation time
double CurrentTime (void);

// Uniformly distributed random value between 0 and 1
double urand(void);

// Random value on exponential distribution with a given mean
double randexp(double mean);

//
// Function defined in the simulation application called by the simulation engine
//
//  Event handler function: called to process an event
void EventHandler (void *data);

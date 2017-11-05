You will work with one other student to develop a discrete event simulation program and use it to
analyze a system. Discrete event simulations are widely used in science and engineering
applications in areas such as manufacturing, supply chains, transportation, telecommunications,
particle physics, business operations, etc. Rather than using a time-stepped approach, the
simulation advances from one event to the next, where each event represents something
“interesting” occurring in the actual system, i.e., the physical system. For example, typical events
might be the arrival of a new customer in a simulation of a department store or a vehicle arriving
at an intersection in a traffic simulation. Each event contains a timestamp, a simulation time value
indicating when that event occurs in the physical system. The timestamp is analogous to the time
step number in a time-stepped simulation, however, events occur at irregular points in time, not at
regular, periodic time steps. As such, time is usually represented by a floating point number in a
discrete event simulation, and simulation time advances at irregular intervals as the computation
proceeds from one event to the next.

The simulation includes a number of state variables that represent the current stat of the system,
e.g., the number of customers waiting in line or the state of a traffic signal. The computation
consists of a sequence of event computations. Each event computation can (1) modify one or more
state variables, and/or (2) schedule one or more new events into the simulated future. For example,
when modeling air traffic at an airport, the computation for an event denoting that an aircraft has
just touched down on the runway might schedule a new event five minutes into the simulated
future to represent the aircraft arriving at the arrival gate and beginning to unload passengers.
The simulation program contains two main part:

• Simulation engine. This part of the program is independent of the simulation application,
i.e., the same simulation engine software could be used to simulate a transportation system
or a manufacturing application. It includes a data structure called the future event list (FEL)
that is a priority queue that contains the set of events that have been scheduled, but have
not yet been processed. The simulation engine holds the main event processing loop which
repeatedly (1) removes the smallest timestamped event from the FEL, and (2) calls a
function (defined in the simulation application, discussed next) to simulate that event. The
loop continues processing events until some termination condition is met, e.g., simulation
time reaches a certain value. The simulation maintains a clock variable indicating how far
the simulation has advanced in simulation time. It also includes a function called by the
simulation application to schedule a new event, i.e., to allocate memory for the event, fill
in various parameters, and insert the new event into the FEL. The main event processing
loop updates the clock variable in each iteration of the loop to the timestamp of the event
it just removed from the FEL.

• Simulation application. This part of the program contains code to model the physical
system. It includes a set of state variables that represent the current state of the system
being modeled. It also includes one or more functions or event handler procedures, one for
each type of event modeled by the simulation. The event handler procedures collectively
model the operation of the system being simulated. To develop the simulation application, 
one must define the state variables and the different types of events that are modeled, and
implement a function for each different event type. The simulation application also
includes a number of variables used to collect statistics concerning the simulation, e.g., the
average time an aircraft must wait to land at an airport.


You will work with your partner to jointly develop the simulation program. One individual is
responsible for the simulation application, and the other for the simulation engine. The interface
(application program interface, or API) between the two must be clearly defined and documented
in a header (.h) file. The simulation engine and application must reside in different files.
A sample discrete event simulation program is provided to help you develop your code. You may
reuse any part of this example program to complete this assignment.
The following describes the simulation application and engine in more detail. A variety of
parameters and specific values are defined below. Although your program will only use the values
specified below, your code should be written so any of these can be easily modified.


The Simulation Application
Your simulation will model the operation of a “one-lane bridge.” By this we mean there is a 2-lane
road carrying traffic in two directions (north and south) that crosses over a bridge. The bridge is
only wide enough to carry traffic in one direction at a time. If the bridge is carrying traffic in one
direction, say north, when a southbound vehicle arrives, that vehicle must wait until the direction
of traffic crossing the bridge changes.
The rules for the direction of traffic crossing the bridge are as follows:

1. At any time, the bridge is in one of three states: north, south, or empty. If the state is
north (south), there are one or more northbound (southbound) vehicles crossing the
bridge. If the bridge is in the empty state there are no vehicles using the bridge.

2. If a vehicle traveling in either direction arrives at the bridge and the bridge is in the empty
state, that vehicle may immediately enter and begin to cross the bridge, and the bridge state
is set to the direction that vehicle is traveling. Assume it takes C seconds to cross the 
where C is a random number uniformly distributed over the interval [40, 45] seconds.

3. If a northbound (southbound) vehicle arrives at the bridge and the bridge is in the south
(north) state, the vehicle must stop and wait to use the bridge. If there are other vehicles
already waiting to use the bridge, the vehicle must queue behind the other already waiting
vehicles. When the bridge direction changes to the north (south) state, the vehicles will
cross the bridge in the order in which they arrived. A collection of queued vehicles crossing
the bridge one after the other in the same direction is referred to as a group.

4. When a group of vehicles begin to drive across the bridge, the first vehicle in the group
will cross the bridge in a time uniformly distributed in the interval [40,45] seconds.
Subsequent vehicles in the group (if there are any) will each require the same amount of
time to cross the bridge as the lead vehicle. The vehicles in the group move on to the bridge
one at a time. Specifically, the second vehicle in the group will enter the bridge S2 seconds
after the first, the third vehicle enters the bridge S3 seconds after the second, etc., i.e., if the
first vehicle enters the bridge at time T, subsequent vehicles will enter at times T+S2,
T+S2+S3, T+S2+S3+S4, etc. Assume S is a random value drawn from a uniform
distribution over the interval [2.5,3.5] seconds. If a new vehicle arrives at the bridge
traveling in the same direction as the group while at least one member of the group is still
waiting to enter the bridge, that vehicle joins the group. If a vehicle arrives traveling in the
same direction as a group crossing the bridge, but the last vehicle in the group has already
entered the bridge, that vehicle must wait even though the state of the bridge is the same
as the direction the vehicle is traveling.

5. When the last vehicle of a group completes its crossing of the bridge, then (1) if there are
vehicles waiting to cross in the opposite direction, the state of the bridge changes to the
opposite direction and the queued vehicles form a new group that begins crossing the
bridge, or (2) if there are no vehicles waiting to cross in the opposite direction, but there
are now vehicles waiting to cross in the same direction as the group that just left the bridge,
then the waiting group immediately begins crossing the bridge, or (3) if neither case (1)
nor case (2) applies, the bridge enters the empty state.
Assume that the time between arrivals (the inter-arrival time) of northbound (southbound) vehicles
at the bridge is drawn from an exponentially distributed random variable with mean
NB_InterArrivalTime (SB_InterArrivalTime).

Your simulator should compute sufficient information to characterize the traffic moving in the
north direction (the model is symmetric, so southbound traffic should be similar). Specifically,
generate a histogram depicting the waiting time to use the bridge for northbound vehicles. The
waiting time is defined as the time from when the vehicle arrives at the bridge until the time its
group begins crossing the bridge. Your simulation should also compute the minimum, maximum,
and average waiting times. You may generate the histogram within the simulation itself, or your
simulation may write data into an output file that is later analyzed by software such as Excel.
Define three levels of southbound traffic, termed “light”, “medium,” and “heavy.” You need to
run some preliminary experiments to determine what are suitable traffic flow rates for each of
these three cases. Generate a graph plotting the average waiting time of northbound traffic as a
function of incoming northbound traffic flow rate (vehicles per hour) for each level of southbound
traffic, and plot these on a single graph (so there should be three curves, one for each rate of
southbound traffic). In addition, show the probability distribution of waiting times by generating
three histograms for northbound waiting time, with the southbound traffic set to “medium” and
northbound traffic set to light, medium and heavy (use the same settings you had derived earlier
for southbound traffic to define what light, medium, and heavy means). Explain your results in the
project report.

# TODO
  * Make the code a little more of a framework than robot code
    * Possibly make some things like PID more of a class than a namespace
    * Eliminate regular PROS project files, and enable use of cloning this repo into the project and using it directly
      1. Makefile changes probably
      2. Moving init functions of namespaces to a file that a user would write
      3. Deleting opcontrol.cpp, auto.cpp and init.cpp
  * Get more members...?
  * Create a wiki on how to use this (after the first one)
  * Put library code in *alpaca* namespace, with an *alpaca::init* function to take care of the usual c++ stuff and motor init, etc


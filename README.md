# MODELING AND SIMULATION OF A RC CIRCUIT
This repository contains a very simple circuit simulator. In fact, it is so simple, that all it can simulate is the output voltage of an RC circuit. The main purpose is to simply practice modelling and simulation of electrical systems.
At the time of writing, the usage is as follows:

1. Building the C++ code: insert the values of resistance, capacitance, etc in the file main.cpp. Then, compile the code and produce the executable with "g++ main.cpp electricModels.cpp -o main"
2. Running the executable: use "./main.exe" to run the executable, which will write the desired signals from the simulation to the file "output.json"
3. Viewing the results: use "python pyViewer.py" to view the results of the simulation with matplotlib.

The following DrawIO diagram illustrates the math used for the modeling and simulation. It
!["Pipeline" for the modeling and simulation approach used](ModelSimRC.drawio.svg)
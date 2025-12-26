# MODELING AND SIMULATION OF AN RC CIRCUIT
This repository contains a very simple circuit simulator. In fact, it is so simple, that all it can simulate is the output voltage of an RC circuit. The main purpose is to simply practice modelling and simulation of electrical systems.
At the time of writing, the usage is as follows:

1. **Building the C++ application:** insert the values of resistance, capacitance, etc in the file main.cpp. Then, compile the code and produce the executable with 
```
g++ main.cpp electricModels.cpp -o main
```
1. **Running the executable:** use the following command to run the executable, which will write the desired signals from the simulation to the file "output.json"
```
./main.exe
``` 

2. **Viewing the results:** now call python to view the results of the simulation with matplotlib.
```
python pyViewer.py
```

The following DrawIO diagram illustrates the math used for the modeling and simulation:
!["Pipeline" for the modeling and simulation approach used](ModelSimRC.drawio.svg)
COMP 3004 - A3 - F24
Carleton University
Ben Granger
101221725

Control: The class that bridges the gap between the ui (MainWindow) and the simulation.

MainWindow: The ui class, handles all ui updates.

Elevator: The elevator class, is responsible for moving passengers from floor to floor, has array of passengers in the elevator, and handles loading/unloading of passengers.

Floor: The floor class, is responsible for holding passengers while waiting for elevators, has array of passengers on the floor.

ECS: The ECS class, controls all elevators, holds the Floor pointers. Handles alarm codes.

Passenger: A container class for information regarding passengers.

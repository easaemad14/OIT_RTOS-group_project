################################################
CST347 Term Project Task Layout and Delegation
Bassinger, El Sirgany, Morales
################################################
################################################

taskMain (Charles Bassinger) :
	void makeElevator(uint8_t floor, bool up);
		//during startup, this function will create an elevator task
		//the elevator should have a floor where it resides, and a direction of travel (if its got a call)
	void interference();
		//this function will alert the elevator if some interference event occurs (like emergency stop)
	bool changeMaxSpeed(uint8_t speed);
		//tell the elevator to change its max speed value to the variable passed into the function)
	bool changeAcc(uint8_t acc);
		//tell elevator to change acceleration
	void emergencyStop();
		//tell elevator to execute emergency stop routine
		//SPECIAL NOTE:  Guys, this function seems redundant with the interference function.  I'm thining about dumping 'interference' - what do you think?
		
taskElevator (Steven Morales) :
	


functions / other non-tasks (Easa El Sirgany) :



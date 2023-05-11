#pragma config(Sensor, in2,    Potentiometer,  sensorPotentiometer)
#pragma config(Sensor, in3,    LightSensor,    sensorReflection)
#pragma config(Sensor, dgtl1,  estopBtn,       sensorTouch)
#pragma config(Sensor, dgtl9,  Red,            sensorNone)
#pragma config(Sensor, dgtl10, Green,          sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, handshakeIn,    sensorTouch)
#pragma config(Sensor, dgtl12, handshakeOut,   sensorLEDtoVCC)
#pragma config(Motor,  port2,           motor1,        tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
  Project Title: CIM 11 GIP
  Task Description: Start the handshaking process
*/

task estop()
{
    while(1==1) {
        if(SensorValue(estopBtn) == 1) {
            // Stop all running tasks
            stopAllTasks();
        }

        wait1Msec(10);
    }
}

task main()
{
    // Start the emergency stop task
	startTask(estop);

    // Variable setter
    int runCount;
    runCount = 0;

    // Set LEDs
    turnLEDOn(handshakeOut);
  	turnLEDOn(Red);
  	turnLEDOff(Green);

    // Run code if count is less than 4
	while(runCount < 4)
	{
		// Check start button
		if(SensorValue(handshakeIn) == 1)
		{
			turnLEDOn(Green);
			turnLEDOff(Red);
			wait(5);

            // Turn	motor to 90 degrees using potentiometer
			startMotor(motor1,60);
			untilPotentiometerGreaterThan(90,Potentiometer);
			stopMotor(motor1);

			wait(10);

            // Detect if beaker is still in place
			if(SensorValue[LightSensor] <= 20)
			{
				wait(2);

                // Turn motor to 180 degrees using potentiometer
				startMotor(motor1,60);
				untilPotentiometerGreaterThan(180,Potentiometer);
				stopMotor(motor1);

				wait(2);

                // Turn motor back to
				startMotor(motor1,-60);
				untilPotentiometerLessThan(0,Potentiometer);
                stopMotor(motor1);
				turnLEDOff(Green);
				turnLEDOn(Red);

				// Handshake to DoBot
				turnLEDOff(handshakeOut);
				wait(0.1);
				turnLEDOn(handshakeOut);

                // Handshake back to start.c
                turnLEDOff(handshakeOut);
                wait(0.05);
                turnLEDOn(handshakeOut);
			}

			// Iterate run count by one
            runCount = runCount + 1;
		}
    }
}

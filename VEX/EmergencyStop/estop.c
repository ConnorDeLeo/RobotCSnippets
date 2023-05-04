task estop() {
    // Check if E-Stop is pressed every 10ms
    while(true) {
        if(SensorValue(estopBtn) == 1) {
            // Stop all running tasks
            stopAllTasks();
        }

        wait1Msec(10);
    }
}

task main() {
    // Start estop task on startup
    startTask(estop);

    // Miscellaneous code
}
var movement_1 = motor.movementDecoder("2 2 3000\n3 0 2\n2000 0 2000\n2000 -1000 -2000");

var flag = false;
loops.forever(function () {
    loops.pause(1000);
    // motor.playMovement(movement_1);

    // motor.changeLocalStringLength(0, -1000);
    // motor.pushLocalMotorPVToRemoteInterpolate(2000);
    // motor.changeLocalStringLength(0, 0);
    // motor.pushLocalMotorPVToRemoteInterpolate(2000);

    jslib.printHeap("============================= heap size after one loop: ");
})

callbacks.onStartTouch(0, 150, function () {
	motor.playMovement(movement_1);
})

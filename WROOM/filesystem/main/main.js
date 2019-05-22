var movement_1 = motor.movementDecoder("2 2 3000\n3 0 2\n1000 603 2000\n1000 -2266 -2000");
for (var i = 0; i < 4; i++) {
    motor.playMovement(movement_1);
}

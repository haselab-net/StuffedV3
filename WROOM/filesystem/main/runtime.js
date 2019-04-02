var loops = require("sr_loops");
var jslib = require("jslib");
var motor = require("sr_motor")

jslib.printHeap("heap size after require: ");

loops.forever(function () {
    motor.changeLocalStringLength(0, 200)
    motor.pushLocalMotorPVToRemoteDirect()
    loops.pause(2000)
    motor.changeLocalStringLength(0, 100)
    motor.pushLocalMotorPVToRemoteDirect()
    loops.pause(2000)
})

loops.doForever();
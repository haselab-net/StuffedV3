var loops = require("sr_loops");
var jslib = require("jslib");
var softrobot = require("sr_softrobot");

jslib.printHeap("heap size after require: ");

console.log("1");

var instruction = {
    motorId: 0,
    pose: 100
};
softrobot.message_command.updateRemoteMotorState(instruction);

loops.forever(function () {
    loops.pause(100)
    loops.pause(100)
    loops.pause(100)
    loops.pause(100)
})

console.log("2");

loops.doForever();
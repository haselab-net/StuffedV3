var jslib = require("jslib");
var loops = require("sr_loops");
var console = require("console");

// ESP32.include("iot.js");
ESP32.include("sr_softrobot.js");
ESP32.include("sr_motor.js");
ESP32.include("sr_callbacks.js");

// register function
var global = new Function('return this;')();
function handleTimer() {
    if (_timers.timerEntries.length > 0 && new Date().getTime() >= _timers.timerEntries[0].fire ) {
        //log("Processing timer fired for id: " + _timers.timerEntries[0].id);
        var timerCallback = _timers.timerEntries[0].callback;
        if (_timers.timerEntries[0].interval > 0) {
            jslib.printHeap("before sort timers");
            _timers.timerEntries[0].fire = new Date().getTime() + _timers.timerEntries[0].interval;
            _timers.sort();
            jslib.printHeap("after sort timers");
        } else {
            _timers.timerEntries.splice(0, 1);
        }
        timerCallback();
        jslib.printHeap("after call timer callback");
    }
};
global.handleTimer = handleTimer;

jslib.printHeap("heap size after require: ");

// init board
softrobot.message_command.requireBoardInfo();

ESP32.include("/main/main.js");

// jslib.pushEventQueue(loops.doForever);

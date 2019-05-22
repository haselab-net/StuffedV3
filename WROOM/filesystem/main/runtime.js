var loops = require("sr_loops");
var jslib = require("jslib");
ESP32.include("sr_softrobot.js");
ESP32.include("sr_motor.js");

jslib.printHeap("heap size after require: ");

ESP32.include("main/main.js");

loops.doForever();

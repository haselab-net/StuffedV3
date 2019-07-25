var jslib = require("jslib");
jslib.printHeap("after jslib");
var loops = require("sr_loops");
jslib.printHeap("after sr_loops");
var console = require("console");
jslib.printHeap("after console");

// ESP32.include("iot.js");
ESP32.include("sr_softrobot.js");
jslib.printHeap("after sr_softrobot");
ESP32.include("sr_motor.js");
jslib.printHeap("after sr_motor");
var callbacks = require("sr_callbacks.js");
jslib.printHeap("after sr_callbacks");

jslib.printHeap("heap size after require: ");

// init board
softrobot.message_command.requireBoardInfo();

ESP32.include("/main/main.js");

jslib.printHeap("heap size after main.js: ");

jslib.pushEventQueue(loops.doForever);

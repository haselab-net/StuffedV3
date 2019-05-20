var loops = require("sr_loops");
var jslib = require("jslib");
var motor = require("sr_motor")

jslib.printHeap("heap size after require: ");

ESP32.include("main/main.js");

loops.doForever();

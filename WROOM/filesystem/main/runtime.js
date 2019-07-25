var jslib = require("jslib");

ESP32.include("/main/main.js");

jslib.printHeap("heap size after main.js: ");

jslib.pushEventQueue(loops.doForever);

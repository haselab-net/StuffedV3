var jslib = require("jslib");

var t1 = setInterval(function () {
    ESP32.print("1i ");
}, 3);
var t2 = setInterval(function () {
    ESP32.print("2i ");
}, 4);

var count3 = 0;
function timeout3() {
    ESP32.print("3o ");
    count3 ++;
    if (count3 == 50){
        cancelInterval(t1);
    }
    if (count3 < 100){
        setTimeout(timeout4, 5);
    }
}

var count4 = 0;
function timeout4() {
    ESP32.print("4o ");
    count4 ++;
    if (count4 == 50){
        cancelInterval(t2);
    }
    if (count4 < 100){
        setTimeout(timeout3, 6);
        ESP32.print("\n");
    }
}
setTimeout(timeout3, 1);
setTimeout(timeout4, 1);

/*
var loops = require("sr_loops");
var console = require("console");

// ESP32.include("iot.js");
ESP32.include("sr_softrobot.js");
//ESP32.include("sr_motor.js");
ESP32.include("sr_callbacks.js");

jslib.printHeap("heap size after require: ");

// init board
softrobot.message_command.requireBoardInfo();

ESP32.include("/main/main.js");

// jslib.pushEventQueue(loops.doForever);
*/

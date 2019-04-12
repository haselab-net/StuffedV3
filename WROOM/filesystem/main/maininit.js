var jslib = require("jslib");
jslib.print("maininit.js is executed\n");
var loops = require("sr_loops");
var softrobot = require("sr_softrobot");
var motor = require("sr_motor");

jslib.printHeap("heap size after require: ");

// softrobot.senArrayBuffer = jslib.sendCommand;
// jslib.registerCallback(function(buffer, buffersize){
//     var packet = softrobot.packet_command.Packet.fromBinary(buffer);
//     if(!packet) {
//         console.log("Failed to convert arraybuffer to packet");
//         return;
//     }
//     softrobot.message_command.messageHandler(packet);
//     console.log("command callback executed");
// })
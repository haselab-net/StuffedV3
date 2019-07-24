console.log("defaule main.js");

var movement_1 = motor.movementDecoder("4 1 6005\n3 0\n842 2276\n1158 397\n2011 2765\n1994 1246")
for (var i = 0; i < 3; i++) {
    motor.setMovement(motor.MovementOption.play, movement_1)
}

// iot.registerMQTTEvent("hello", function (value1, value2, value3) {
//     console.log("hello");
// })
// iot.registerMQTTEvent("hi", function (value1, value2, value3) {
//     console.log("hi");
// })
// callbacks.onStartTouch(1, 200, function () {
//     console.log("touch callback called")
//     iot.triggerIFTTTEvent(
//     "Mf0JcCX_5FLZiz6Svtpjn",
//     "sensor_touched",
//     "",
//     "",
//     ""
//     )
// })
// iot.startWaitingMQTTEvent("192.168.91.146", 5000)

// loops.pause(30000)
// loops.forever(function () {
//     console.log("------------------- before start ---------------------------")
//     iot.startWaitingMQTTEvent("192.168.0.12", 5000)
//     loops.pause(20000)
//     console.log("------------------- before stop ---------------------------")
//     iot.stopWaitingMQTTEvent()
//     loops.pause(10000)
// })

jslib.print("Initial default main.js is called.");

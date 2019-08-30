console.log("defaule main.js");

motor.setMovement(motor.MovementOption.play, motor.movementDecoder("default1\n4 1 4000\n3 0\n810 2211\n834 0\n797 2005\n810 63"))
motor.playAfter(motor.movementDecoder("default2\n4 1 4000\n3 1\n810 2211\n834 0\n797 2005\n810 63"), motor.movementDecoder("default1\n4 1 4000\n3 0\n810 2211\n834 0\n797 2005\n810 63"))

// var movement_1 = motor.movementDecoder("default1\n4 1 6005\n3 0\n842 2276\n1158 397\n2011 2765\n1994 1246")
// var movement_2 = motor.movementDecoder("default2\n4 1 6005\n3 1\n842 2276\n1158 397\n2011 2765\n1994 1246")
// loops.forever(function () {
//     motor.setMovement(motor.MovementOption.play, movement_1)
//     loops.pause(1000)
// })
// callbacks.onStartTouch(1, 200, function () {
//     console.log("on touch");
//     motor.setMovement(motor.MovementOption.play, movement_2)
// })

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

iot.startWaitingMQTTEventDefault();
// iot.startWaitingMQTTEvent("192.168.91.3", 5000)

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

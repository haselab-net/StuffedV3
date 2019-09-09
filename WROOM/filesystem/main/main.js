console.log("defaule main.js");

var Movement_1 = motor.movementDecoder("default1\n7 1 7000\n3 0\n1010 5000\n1035 0\n961 67\n982 165\n1002 284\n822 928\n1092 1783")
var Movement_2 = motor.movementDecoder("default1_0\n10 1 10000\n3 1\n1010 5000\n1035 0\n961 67\n982 165\n1002 284\n822 928\n1092 1783\n1322 2278\n752 2560\n1022 3787")
motor.setMovement(motor.MovementOption.play, Movement_1)

console.log("after set movement");
motor.playRelativeToTime(Movement_2, motor.TimeRelationship.after, Movement_1, 3000)
// motor.playAfter(motor.movementDecoder("default2\n4 1 4000\n3 1\n810 2211\n834 0\n797 2005\n810 63"), motor.movementDecoder("default1\n4 1 4000\n3 0\n810 2211\n834 0\n797 2005\n810 63"))

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

// iot.startWaitingMQTTEventDefault();
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

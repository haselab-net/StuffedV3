console.log("defaule main.js");

loops.forever(function () {
    if (motor.isMovementState(movement1, motor.MovementState.playing)) {
        console.log("playing")
    } else {
        console.log("not playing")
    }
    loops.pause(100)
})
var movement1 = motor.movementDecoder("default1\n4 1 4000\n3 0\n810 2211\n834 0\n797 2005\n810 63");
for (var i = 0; i < 4; i++) {
    motor.setMovement(motor.MovementOption.play, movement1)
}
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

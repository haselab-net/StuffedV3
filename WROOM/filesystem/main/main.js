// loops.pause(10000);
// iot.triggerIFTTTEvent("Mf0JcCX_5FLZiz6Svtpjn", "esp_event", "", "", "")

for (var i=0; i<3; i++) {
    console.log("loop: " + i);
    softrobot.message_command.movementAddKeyframe({
        movementId: 1,
        keyframeId: 0,
        motorCount: 1,
        motorId: [0],
        period: 2000,
        pose: [2000],
        refMovementId: 0,
        refKeyframeId: 0,
        refMotorId: 0,
        timeOffset: 0
    });
    softrobot.message_command.movementAddKeyframe({
        movementId: 1,
        keyframeId: 0,
        motorCount: 1,
        motorId: [0],
        period: 2000,
        pose: [-2000],
        refMovementId: 0,
        refKeyframeId: 0,
        refMotorId: 0,
        timeOffset: 0
    })
}

// iot.registerMQTTEvent("event", function (value1, value2, value3) {
//     console.log("event");
//     iot.triggerIFTTTEvent(
//     "Mf0JcCX_5FLZiz6Svtpjn",
//     "esp_event",
//     value1,
//     value2,
//     value3
//     );
// })
// iot.startWaitingMQTTEvent("131.112.182.91", 5000)

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

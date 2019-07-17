// loops.pause(10000);
// iot.triggerIFTTTEvent("Mf0JcCX_5FLZiz6Svtpjn", "esp_event", "", "", "")

function movementCallback(data) {
    if (data.movementCommandId == 1) {
        console.log("movement id: " + data.movementId);
        console.log("keyframe id: " + data.keyframeId);
        console.log("success: " + data.success);
        console.log("nOccupied 0: " + data.nOccupied[0]);
        console.log("nOccupied 1: " + data.nOccupied[1]);
        console.log("nOccupied 2: " + data.nOccupied[2]);
    }
}

softrobot.message_command.registerCallback("onReceiveCIUMovement", movementCallback);

for (var i=0; i<3; i++) {
    console.log("loop: " + i);
    softrobot.message_command.setMovement({
        movementCommandId: 1,
        movementId: 1,
        keyframeId: i*2,
        motorCount: 1,
        motorId: [0],
        period: 2000,
        pose: [2000],
        refMovementId: 0,
        refKeyframeId: 0,
        refMotorId: 0,
        timeOffset: 0
    });
    softrobot.message_command.setMovement({
        movementCommandId: 1,
        movementId: 1,
        keyframeId: i*2 + 1,
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

loops.pause(10000);

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

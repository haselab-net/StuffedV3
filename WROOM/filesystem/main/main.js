// loops.forever(function () {
//     motor.changeLocalStringLength(0, 200)
//     motor.pushLocalMotorPVToRemoteDirect()
//     loops.pause(2000)
//     motor.changeLocalStringLength(0, 100)
//     motor.pushLocalMotorPVToRemoteDirect()
//     loops.pause(2000)
// })

for(var i=0; i<10; i++) {
    motor.changeLocalStringLength(0, 1000)
    motor.pushLocalMotorPVToRemoteInterpolate(2000)
    motor.changeLocalStringLength(0, -1000)
    motor.pushLocalMotorPVToRemoteInterpolate(2000)
}
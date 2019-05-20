loops.forever(function () {
    motor.changeLocalStringLength(0, 2097)
    motor.pushLocalMotorPVToRemoteInterpolate(2056)
    loops.pause(1000)
    motor.changeLocalStringLength(0, -161)
    motor.pushLocalMotorPVToRemoteInterpolate(2056)
    loops.pause(1000)
})

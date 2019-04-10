loops.forever(function () {
    motor.changeLocalStringLength(0, 200)
    motor.pushLocalMotorPVToRemoteDirect()
    loops.pause(2000)
    motor.changeLocalStringLength(0, 100)
    motor.pushLocalMotorPVToRemoteDirect()
    loops.pause(2000)
})
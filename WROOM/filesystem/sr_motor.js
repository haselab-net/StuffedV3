var softrobot = require("sr_softrobot");

var motor;
(function (motor_1) {
    function changeRemoteMotorParameter(motor, parameterType, value) {
        var instruction = {
            motorId: motor
        };
        var array = Object.keys(softrobot.device.robotState.motor[0]);
        instruction[array[parameterType]] = value;
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorParameter = changeRemoteMotorParameter;
    function changeLocalStringLength(motor, value) {
        var instruction = {
            motorId: motor,
            pose: value
        };
        softrobot.message_command.updateLocalMotorState(instruction);
    }
    motor_1.changeLocalStringLength = changeLocalStringLength;
    function changeLocalStringVelocity(motor, velocity) {
        var instruction = {
            motorId: motor,
            velocity: velocity
        };
        softrobot.message_command.updateLocalMotorState(instruction);
    }
    motor_1.changeLocalStringVelocity = changeLocalStringVelocity;
    function pushLocalMotorPVToRemoteDirect() {
        softrobot.message_command.updateMotorPVDirect();
    }
    motor_1.pushLocalMotorPVToRemoteDirect = pushLocalMotorPVToRemoteDirect;
    function pushLocalMotorPVToRemoteInterpolate(period) {
        softrobot.message_command.updateMotorPVInterpolate(period);
    }
    motor_1.pushLocalMotorPVToRemoteInterpolate = pushLocalMotorPVToRemoteInterpolate;
})(motor || (motor = {}));

module.exports = motor;
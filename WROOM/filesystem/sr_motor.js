var softrobot = require("sr_softrobot");

var motor;
(function (motor_1) {
    function changeLocalStringLength(motor, length) {
        var instruction = {
            motorId: motor,
            pose: length
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
    function changeRemoteStringLength(motor, length) {
        var instruction = {
            motorId: motor,
            pose: length
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteStringLength = changeRemoteStringLength;
    function changeRemoteStringVelocity(motor, velocity) {
        var instruction = {
            motorId: motor,
            velocity: velocity
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteStringVelocity = changeRemoteStringVelocity;
    function changeRemoteMotorLengthMin(motor, lengthMin) {
        var instruction = {
            motorId: motor,
            lengthMin: lengthMin
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorLengthMin = changeRemoteMotorLengthMin;
    function changeRemoteMotorLengthMax(motor, lengthMax) {
        var instruction = {
            motorId: motor,
            lengthMax: lengthMax
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorLengthMax = changeRemoteMotorLengthMax;
    function changeRemoteMotorControlK(motor, controlK) {
        var instruction = {
            motorId: motor,
            controlK: controlK
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorControlK = changeRemoteMotorControlK;
    function changeRemoteMotorControlB(motor, controlB) {
        var instruction = {
            motorId: motor,
            controlB: controlB
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorControlB = changeRemoteMotorControlB;
    function changeRemoteMotorTorqueMin(motor, torqueMin) {
        var instruction = {
            motorId: motor,
            torqueMin: torqueMin
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorTorqueMin = changeRemoteMotorTorqueMin;
    function changeRemoteMotorTorqueMax(motor, torqueMax) {
        var instruction = {
            motorId: motor,
            torqueMax: torqueMax
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorTorqueMax = changeRemoteMotorTorqueMax;
})(motor || (motor = {}));

console.log("motor loaded");

module.exports = motor;
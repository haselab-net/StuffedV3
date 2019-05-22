// var softrobot = require("sr_softrobot");

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
        softrobot.message_command.updateRemoteDirect();
    }
    motor_1.pushLocalMotorPVToRemoteDirect = pushLocalMotorPVToRemoteDirect;
    function pushLocalMotorPVToRemoteInterpolateBase(period) {
        var keyframe = {
            pose: softrobot.device.robotState.getPropArray("pose", softrobot.device.robotState.motor),
            period: period
        };
        if (softrobot.movement.sendKeyframeQueue.enqueue(keyframe) == -1)
            return false;
        return true;
    }
    motor_1.pushLocalMotorPVToRemoteInterpolateBase = pushLocalMotorPVToRemoteInterpolateBase;
    function stopInterpolate() {
        softrobot.movement.sendKeyframeQueue.clear();
    }
    motor_1.stopInterpolate = stopInterpolate;
    function playMovement(movement) {
        for (var _i = 0, _a = movement.keyframes; _i < _a.length; _i++) {
            var keyframe = _a[_i];
            keyframe.pose.map(function (value, index) { return changeLocalStringLength(movement.motorIds[index], value); });
            pushLocalMotorPVToRemoteInterpolate(keyframe.time);
        }
    }
    motor_1.playMovement = playMovement;
    function pushLocalMotorPVToRemoteInterpolate(period) {
        while (!pushLocalMotorPVToRemoteInterpolateBase(period)) {
            loops.pause(500);
        }
    }
    motor_1.pushLocalMotorPVToRemoteInterpolate = pushLocalMotorPVToRemoteInterpolate;
})(motor || (motor = {}));

// module.exports = motor;
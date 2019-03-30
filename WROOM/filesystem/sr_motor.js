var motor;
(function (motor_1) {
    function changeLocalStringLengthAsync(motor, length) {
        var instruction = {
            motorId: motor,
            pose: length
        };
        softrobot.message_command.updateLocalMotorState(instruction);
    }
    motor_1.changeLocalStringLengthAsync = changeLocalStringLengthAsync;
    function changeLocalStringVelocityAsync(motor, velocity) {
        var instruction = {
            motorId: motor,
            velocity: velocity
        };
        softrobot.message_command.updateLocalMotorState(instruction);
    }
    motor_1.changeLocalStringVelocityAsync = changeLocalStringVelocityAsync;
    function pushLocalMotorPVToRemoteDirectAsync() {
        softrobot.message_command.updateMotorPVDirect();
    }
    motor_1.pushLocalMotorPVToRemoteDirectAsync = pushLocalMotorPVToRemoteDirectAsync;
    function pushLocalMotorPVToRemoteInterpolateAsync(period) {
        softrobot.message_command.updateMotorPVInterpolate(period);
    }
    motor_1.pushLocalMotorPVToRemoteInterpolateAsync = pushLocalMotorPVToRemoteInterpolateAsync;
    function changeRemoteStringLengthAsync(motor, length) {
        var instruction = {
            motorId: motor,
            pose: length
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteStringLengthAsync = changeRemoteStringLengthAsync;
    function changeRemoteStringVelocityAsync(motor, velocity) {
        var instruction = {
            motorId: motor,
            velocity: velocity
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteStringVelocityAsync = changeRemoteStringVelocityAsync;
    function changeRemoteMotorLengthMinAsync(motor, lengthMin) {
        var instruction = {
            motorId: motor,
            lengthMin: lengthMin
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorLengthMinAsync = changeRemoteMotorLengthMinAsync;
    function changeRemoteMotorLengthMaxAsync(motor, lengthMax) {
        var instruction = {
            motorId: motor,
            lengthMax: lengthMax
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorLengthMaxAsync = changeRemoteMotorLengthMaxAsync;
    function changeRemoteMotorControlKAsync(motor, controlK) {
        var instruction = {
            motorId: motor,
            controlK: controlK
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorControlKAsync = changeRemoteMotorControlKAsync;
    function changeRemoteMotorControlBAsync(motor, controlB) {
        var instruction = {
            motorId: motor,
            controlB: controlB
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorControlBAsync = changeRemoteMotorControlBAsync;
    function changeRemoteMotorTorqueMinAsync(motor, torqueMin) {
        var instruction = {
            motorId: motor,
            torqueMin: torqueMin
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorTorqueMinAsync = changeRemoteMotorTorqueMinAsync;
    function changeRemoteMotorTorqueMaxAsync(motor, torqueMax) {
        var instruction = {
            motorId: motor,
            torqueMax: torqueMax
        };
        softrobot.message_command.updateRemoteMotorState(instruction);
    }
    motor_1.changeRemoteMotorTorqueMaxAsync = changeRemoteMotorTorqueMaxAsync;
})(motor || (motor = {}));

module.export = motor;
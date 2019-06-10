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
    function movementDecoder(movementStr) {
        function splitToInt(str, seperator) {
            var nums_str = str.split(seperator);
            var nums = [];
            for (var i = 0; i < nums_str.length; i++) {
                if (nums_str[i]==='') continue;
                nums.push(Number(nums_str[i]));
            }
            return nums;
        }
        function partialKeyframeDecoder(str) {
            var nums = splitToInt(str, " ");
            return {
                period: nums[0],
                pose: nums.slice(1)
            };
        }
        if (movementStr === "")
            return {
                motorIds: [0],
                keyframes: [{
                        period: 1000,
                        pose: [0]
                    }]
            };
        var lines = movementStr.split("\n");
        var line_1 = splitToInt(lines[0], " ");
        var line_2 = splitToInt(lines[1], " ");
        var keyframes_lines = lines.slice(2, 2 + line_1[0]);
        var keyframes = [];
        var time = 0;
        for (var i = 0; i < keyframes_lines.length; i++) {
            keyframes.push(partialKeyframeDecoder(keyframes_lines[i]));
            time += keyframes[keyframes.length - 1].period;
        }
        function interpolate(x1, y1, x2, y2, x) {
            return (y2 - y1) / (x2 - x1) * (x - x1) + y1;
        }
        var keyframe_first = keyframes[0], keyframe_last = keyframes[keyframes.length - 1];
        if (time < line_1[2]) {
            var lastPose = [];
            for (var i = 0; i < line_1[1]; i++) {
                lastPose.push(interpolate(time - line_1[2], keyframe_last.pose[i], keyframe_first.period, keyframe_first.pose[i], 0));
            }
            keyframes.push({
                period: line_1[2] - time,
                pose: lastPose
            });
        }
        return {
            motorIds: line_2.slice(1),
            keyframes: keyframes
        };
    }
    motor_1.movementDecoder = movementDecoder;
    function playMovement(movement) {
        for (var _i = 0, _a = movement.keyframes; _i < _a.length; _i++) {
            var keyframe = _a[_i];
            for (var i = 0; i < keyframe.pose.length; i++) {
                changeLocalStringLength(movement.motorIds[i], keyframe.pose[i]);
            }
            pushLocalMotorPVToRemoteInterpolate(keyframe.period);
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
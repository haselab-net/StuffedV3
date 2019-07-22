var softrobot;
(function (softrobot) {
    var command;
    (function (command) {
        var CommandId;
        (function (CommandId) {
            CommandId[CommandId["CI_NONE"] = 0] = "CI_NONE";
            CommandId[CommandId["CI_BOARD_INFO"] = 1] = "CI_BOARD_INFO";
            CommandId[CommandId["CI_SET_CMDLEN"] = 2] = "CI_SET_CMDLEN";
            CommandId[CommandId["CI_ALL"] = 3] = "CI_ALL";
            CommandId[CommandId["CI_SENSOR"] = 4] = "CI_SENSOR";
            CommandId[CommandId["CI_DIRECT"] = 5] = "CI_DIRECT";
            CommandId[CommandId["CI_CURRENT"] = 6] = "CI_CURRENT";
            CommandId[CommandId["CI_INTERPOLATE"] = 7] = "CI_INTERPOLATE";
            CommandId[CommandId["CI_FORCE_CONTROL"] = 8] = "CI_FORCE_CONTROL";
            CommandId[CommandId["CI_SETPARAM"] = 9] = "CI_SETPARAM";
            CommandId[CommandId["CI_RESET_SENSOR"] = 10] = "CI_RESET_SENSOR";
            CommandId[CommandId["CI_NCOMMAND"] = 11] = "CI_NCOMMAND";
            CommandId[CommandId["CIU_TEXT"] = 11] = "CIU_TEXT";
            CommandId[CommandId["CIU_SET_IPADDRESS"] = 12] = "CIU_SET_IPADDRESS";
            CommandId[CommandId["CIU_GET_IPADDRESS"] = 13] = "CIU_GET_IPADDRESS";
            CommandId[CommandId["CIU_GET_SUBBOARD_INFO"] = 14] = "CIU_GET_SUBBOARD_INFO";
            CommandId[CommandId["CIU_MOVEMENT"] = 15] = "CIU_MOVEMENT";
            CommandId[CommandId["CIU_NCOMMAND"] = 15] = "CIU_NCOMMAND";
            CommandId[CommandId["CIU_NONE"] = -1] = "CIU_NONE";
        })(CommandId = command.CommandId || (command.CommandId = {}));
        ;
        var SetParamType;
        (function (SetParamType) {
            SetParamType[SetParamType["PT_PD"] = 0] = "PT_PD";
            SetParamType[SetParamType["PT_CURRENT"] = 1] = "PT_CURRENT";
            SetParamType[SetParamType["PT_TORQUE_LIMIT"] = 2] = "PT_TORQUE_LIMIT";
            SetParamType[SetParamType["PT_BOARD_ID"] = 3] = "PT_BOARD_ID";
        })(SetParamType = command.SetParamType || (command.SetParamType = {}));
        ;
        var ResetSensorFlags;
        (function (ResetSensorFlags) {
            ResetSensorFlags[ResetSensorFlags["RSF_NONE"] = 0] = "RSF_NONE";
            ResetSensorFlags[ResetSensorFlags["RSF_MOTOR"] = 1] = "RSF_MOTOR";
            ResetSensorFlags[ResetSensorFlags["RSF_FORCE"] = 2] = "RSF_FORCE";
        })(ResetSensorFlags = command.ResetSensorFlags || (command.ResetSensorFlags = {}));
        var PacketId;
        (function (PacketId) {
            PacketId[PacketId["PI_NONE"] = 0] = "PI_NONE";
            PacketId[PacketId["PI_JSFILE"] = 1] = "PI_JSFILE";
            PacketId[PacketId["PI_COMMAND"] = 2] = "PI_COMMAND";
            PacketId[PacketId["PI_SETTINGS"] = 3] = "PI_SETTINGS";
        })(PacketId = command.PacketId || (command.PacketId = {}));
        var SettingId;
        (function (SettingId) {
            SettingId[SettingId["SI_NONE"] = 0] = "SI_NONE";
            SettingId[SettingId["SI_DEVELOPMENT_MODE"] = 1] = "SI_DEVELOPMENT_MODE";
        })(SettingId = command.SettingId || (command.SettingId = {}));
        var CommandIdMovement;
        (function (CommandIdMovement) {
            CommandIdMovement[CommandIdMovement["CI_M_NONE"] = 0] = "CI_M_NONE";
            CommandIdMovement[CommandIdMovement["CI_M_ADD_KEYFRAME"] = 1] = "CI_M_ADD_KEYFRAME";
            CommandIdMovement[CommandIdMovement["CI_M_PAUSE_MOV"] = 2] = "CI_M_PAUSE_MOV";
            CommandIdMovement[CommandIdMovement["CI_M_RESUME_MOV"] = 3] = "CI_M_RESUME_MOV";
            CommandIdMovement[CommandIdMovement["CI_M_PAUSE_INTERPOLATE"] = 4] = "CI_M_PAUSE_INTERPOLATE";
            CommandIdMovement[CommandIdMovement["CI_M_RESUME_INTERPOLATE"] = 5] = "CI_M_RESUME_INTERPOLATE";
            CommandIdMovement[CommandIdMovement["CI_M_CLEAR_MOV"] = 6] = "CI_M_CLEAR_MOV";
            CommandIdMovement[CommandIdMovement["CI_M_CLEAR_PAUSED"] = 7] = "CI_M_CLEAR_PAUSED";
            CommandIdMovement[CommandIdMovement["CI_M_CLEAR_ALL"] = 8] = "CI_M_CLEAR_ALL";
            CommandIdMovement[CommandIdMovement["CI_M_QUERY"] = 9] = "CI_M_QUERY";
            CommandIdMovement[CommandIdMovement["CI_M_COUNT"] = 9] = "CI_M_COUNT";
        })(CommandIdMovement = command.CommandIdMovement || (command.CommandIdMovement = {}));
    })(command = softrobot.command || (softrobot.command = {}));
})(softrobot || (softrobot = {}));
(function (softrobot) {
    var device;
    (function (device) {
        var RobotInfo = (function () {
            function RobotInfo() {
                this.initialize();
            }
            RobotInfo.prototype.initialize = function () {
                this.systemId = 0;
                this.nTarget = 12;
                this.nMotor = 3;
                this.nCurrent = 0;
                this.nForces = 0;
                this.nTouch = 1;
                this.macAddress = new ArrayBuffer(6);
            };
            return RobotInfo;
        }());
        device.RobotInfo = RobotInfo;
        device.robotInfo = new RobotInfo();
        var MotorState = (function () {
            function MotorState() {
                this.initialize();
            }
            MotorState.prototype.initialize = function () {
                this.pose = 0;
                this.velocity = 0;
                this.lengthMin = -5000;
                this.lengthMax = 5000;
                this.controlK = 4096;
                this.controlB = 2048;
                this.controlA = 0;
                this.torqueMin = -1024;
                this.torqueMax = 1024;
            };
            return MotorState;
        }());
        device.MotorState = MotorState;
        var MovementState = (function () {
            function MovementState() {
                this.initialize();
            }
            MovementState.prototype.initialize = function () {
                this.nOccupied = new Array(device.robotInfo.nMotor);
                for (var index = 0; index < this.nOccupied.length; index++) {
                    this.nOccupied[index] = 0;
                }
                this.pausedMovements = [];
            };
            MovementState.prototype.isPaused = function (movementId) {
                for (var i = 0; i < this.pausedMovements.length; i++) {
                    if (this.pausedMovements[i] == movementId)
                        return i;
                }
                return -1;
            };
            MovementState.prototype.pause = function (movementId) {
                if (this.isPaused(movementId) < 0)
                    this.pausedMovements.push(movementId);
            };
            MovementState.prototype.resume = function (movementId) {
                var id = this.isPaused(movementId);
                if (id >= 0)
                    this.pausedMovements.splice(id, 1);
            };
            return MovementState;
        }());
        device.MovementState = MovementState;
        var RobotState = (function () {
            function RobotState() {
                this.initialize();
            }
            RobotState.prototype.initialize = function () {
                this.motor = new Array(device.robotInfo.nMotor);
                for (var index = 0; index < this.motor.length; index++) {
                    this.motor[index] = new MotorState();
                }
                this.current = new Array(device.robotInfo.nCurrent);
                for (var index = 0; index < this.current.length; index++) {
                    this.current[index] = 0;
                }
                this.force = new Array(device.robotInfo.nForces);
                for (var index = 0; index < this.force.length; index++) {
                    this.force[index] = 0;
                }
                this.touch = new Array(device.robotInfo.nTouch);
                for (var index = 0; index < this.touch.length; index++) {
                    this.touch[index] = 0;
                }
                this.nInterpolateTotal = 12;
                this.interpolateTargetCountOfWrite = -1;
                this.interpolateTargetCountOfReadMin = 0;
                this.interpolateTargetCountOfReadMax = 0;
                this.interpolateTickMin = 0;
                this.interpolateTickMax = 0;
                this.nInterpolateRemain = 0;
                this.nInterpolateVacancy = 12;
                this.movementState = new MovementState();
            };
            RobotState.prototype.getPropArray = function (name, array) {
                if (!(name in array[0])) {
                    console.log("ERROR: No property named " + name + "in array");
                    return null;
                }
                var res = new Array();
                for (var i = 0; i < array.length; i++) {
                    res.push(array[i][name]);
                }
                return res;
            };
            RobotState.prototype.setPropArray = function (name, pArray, oArray) {
                if (pArray.length != oArray.length) {
                    console.log("Error: Not equivalent length array");
                    return;
                }
                if (!(name in oArray[0])) {
                    console.log("ERROR: No property named " + name + "in array");
                    return;
                }
                var res = oArray;
                for (var index = 0; index < res.length; index++) {
                    res[index][name] = pArray[index];
                }
            };
            return RobotState;
        }());
        device.RobotState = RobotState;
        device.robotState = new RobotState();
        function checkRobotState() {
            function resizeArray(array, size) {
                if (array.length <= size) {
                    var a = new Array(size - array.length);
                    for (var key in a) {
                        if (array.length == 0)
                            a[key] = 0;
                        else
                            a[key] = array[0];
                    }
                    array.concat(a);
                }
                else
                    array.slice(0, size);
                return array;
            }
            function resizeMotorStateArray(array, size) {
                if (array.length <= size) {
                    var a = new Array(size - array.length);
                    for (var key in a) {
                        a[key] = new MotorState();
                    }
                    array.concat(a);
                }
                else
                    array.slice(0, size);
                return array;
            }
            device.robotState.nInterpolateTotal = device.robotInfo.nTarget;
            if (device.robotState.motor.length != device.robotInfo.nMotor)
                device.robotState.motor = resizeMotorStateArray(device.robotState.motor, device.robotInfo.nMotor);
            if (device.robotState.current.length != device.robotInfo.nCurrent)
                device.robotState.current = resizeArray(device.robotState.current, device.robotInfo.nCurrent);
            if (device.robotState.force.length != device.robotInfo.nForces)
                device.robotState.force = resizeArray(device.robotState.force, device.robotInfo.nForces);
            if (device.robotState.touch.length != device.robotInfo.nTouch)
                device.robotState.touch = resizeArray(device.robotState.touch, device.robotInfo.nTouch);
                if (device.robotState.movementState.nOccupied.length != device.robotInfo.nMotor)
                device.robotState.movementState.nOccupied = resizeArray(device.robotState.movementState.nOccupied, device.robotInfo.nMotor);
        }
        device.checkRobotState = checkRobotState;
    })(device = softrobot.device || (softrobot.device = {}));
})(softrobot || (softrobot = {}));

// sr_command
(function(softrobot) {
    softrobot.message_command = require("sr_command");
    var tmp = softrobot.message_command.setMotorDirect;
    softrobot.message_command.setMotorDirect = function (data) {
        // softrobot.movement.sendKeyframeQueue.clear();
        softrobot.device.robotState.interpolateTargetCountOfWrite = -1;
        softrobot.device.robotState.nInterpolateVacancy = softrobot.device.robotState.nInterpolateTotal;
        softrobot.device.robotState.nInterpolateRemain = 0;
    }
})(softrobot || (softrobot = {}));

(function (softrobot) {
    var message_command;
    (function (message_command) {
        var callbacks;
        (function (callbacks) {
            callbacks.touchThresholdArray = [];
            callbacks.callTouchCallback = undefined;
            callbacks.touchQueryer = undefined;
            callbacks.touchQueryerInterval = 500;
            callbacks.onRcvTouchMessage = function (oldValue, newValue) {
                if (!callbacks.callTouchCallback)
                    return;
                for (var i = 0; i < callbacks.touchThresholdArray.length; i++) {
                    var threshold = callbacks.touchThresholdArray[i];
                    if (threshold.sensorId >= oldValue.length) {
                        console.log("No touch sensor with id " + threshold.sensorId);
                        continue;
                    }
                    var oldV = oldValue[threshold.sensorId], newV = newValue[threshold.sensorId];
                    var lowV = oldV > newV ? newV : oldV, highV = oldV > newV ? oldV : newV;
                    if (lowV >= threshold.threshold || highV < threshold.threshold)
                        continue;
                    if ((newV > oldV) !== threshold.exceed)
                        continue;
                    console.log("with rcv touch message: ", oldValue, newValue, ", touch threshold is called: ", callbacks.touchThresholdArray[i]);
                    callbacks.callTouchCallback(threshold, []);
                }
            };
        })(callbacks = message_command.callbacks || (message_command.callbacks = {}));
    })(message_command = softrobot.message_command || (softrobot.message_command = {}));
})(softrobot || (softrobot = {}));

(function (softrobot) {
    var message_command;
    (function (message_command) {
        function onReceiveCIBoardinfo(data) {
            softrobot.device.robotInfo = data;
            softrobot.device.checkRobotState();
            for (var i = 0; i < message_command.onRcvCIBoardInfoMessage.length; i++) {
                message_command.onRcvCIBoardInfoMessage[i]();
            }
        }
        message_command.onReceiveCIBoardinfo = onReceiveCIBoardinfo;
        function onReceiveCISensor(data) {
            message_command.callbacks.onRcvTouchMessage(softrobot.device.robotState.touch, data.touch);
            // softrobot.device.robotState.setPropArray("pose", data.pose, softrobot.device.robotState.motor);
            softrobot.device.robotState.current = data.current;
            softrobot.device.robotState.force = data.force;
            softrobot.device.robotState.touch = data.touch;
            for (var i = 0; i < message_command.onRcvCISensorMessage.length; i++) {
                message_command.onRcvCISensorMessage[i]();
            }
        }
        message_command.onReceiveCISensor = onReceiveCISensor;
        function onReceiveCIDirect(data) {
        }
        message_command.onReceiveCIDirect = onReceiveCIDirect;
        function onReceiveCIInterpolate(data) {
            function calculateInterpolateState() {
                var rmin = softrobot.device.robotState.interpolateTargetCountOfReadMin;
                var rmax = softrobot.device.robotState.interpolateTargetCountOfReadMax;
                var tmin = softrobot.device.robotState.interpolateTickMin;
                var tmax = softrobot.device.robotState.interpolateTickMax;
                var wc = softrobot.device.robotState.interpolateTargetCountOfWrite;
                softrobot.device.robotState.nInterpolateRemain = wc >= rmax ? wc - rmax + 1 : wc - rmax + 1 + 256;
                var readDiff = rmax >= rmin ? rmax - rmin : rmax - rmin + 256;
                softrobot.device.robotState.nInterpolateVacancy = softrobot.device.robotState.nInterpolateTotal - softrobot.device.robotState.nInterpolateRemain - readDiff;
            }
            // softrobot.device.robotState.setPropArray("pose", data.pose, softrobot.device.robotState.motor);
            softrobot.device.robotState.interpolateTargetCountOfReadMin = data.targetCountReadMin;
            softrobot.device.robotState.interpolateTargetCountOfReadMax = data.targetCountReadMax;
            softrobot.device.robotState.interpolateTickMin = data.tickMin;
            softrobot.device.robotState.interpolateTickMax = data.tickMax;
            calculateInterpolateState();
            if (softrobot.device.robotState.nInterpolateVacancy > softrobot.device.robotState.nInterpolateTotal - 2 || softrobot.device.robotState.nInterpolateVacancy < 0) {
                softrobot.device.robotState.interpolateTargetCountOfWrite = (softrobot.device.robotState.interpolateTargetCountOfReadMax + 1) % 256;
                calculateInterpolateState();
            }
            for (var i = 0; i < message_command.onRcvCIInterpolateMessage.length; i++) {
                message_command.onRcvCIInterpolateMessage[i]();
            }
        }
        message_command.onReceiveCIInterpolate = onReceiveCIInterpolate;
        function onReceiveCISetparam() {
            return;
        }
        message_command.onReceiveCISetparam = onReceiveCISetparam;
        function onReceiveCIResetsensor() {
            for (var i = 0; i < message_command.onRcvCIResetSensorMessage.length; i++) {
                message_command.onRcvCIResetSensorMessage[i]();
            }
        }
        message_command.onReceiveCIResetsensor = onReceiveCIResetsensor;
        function onReceiveCIUMovement(data) {
            switch (data.movementCommandId) {
                case softrobot.command.CommandIdMovement.CI_M_ADD_KEYFRAME:
                case softrobot.command.CommandIdMovement.CI_M_QUERY:
                    softrobot.device.robotState.movementState.nOccupied = data.nOccupied;
                    break;
                default:
                    break;
            }
            for (var i = 0; i < message_command.onRcvCIUMovementMessage.length; i++) {
                message_command.onRcvCIUMovementMessage[i](data);
            }
        }
        message_command.onReceiveCIUMovement = onReceiveCIUMovement;
        message_command.onRcvCIBoardInfoMessage = [];
        message_command.onRcvCISensorMessage = [];
        message_command.onRcvCIDirectMessage = [];
        message_command.onRcvCIInterpolateMessage = [];
        message_command.onRcvCIResetSensorMessage = [];
        message_command.onRcvCIUMovementMessage = [];
        function setMotorState(to, from) {
            var id = from.motorId;
            if (id >= to.motor.length)
                return;
            if (softrobot.util.haveProp(from.pose))
                to.motor[id].pose = softrobot.util.limitNum(from.pose, to.motor[id].lengthMin, to.motor[id].lengthMax);
            if (softrobot.util.haveProp(from.velocity))
                to.motor[id].velocity = from.velocity;
            if (softrobot.util.haveProp(from.lengthMin))
                to.motor[id].lengthMin = from.lengthMin;
            if (softrobot.util.haveProp(from.lengthMax))
                to.motor[id].lengthMax = from.lengthMax;
            if (softrobot.util.haveProp(from.controlK))
                to.motor[id].controlK = from.controlK;
            if (softrobot.util.haveProp(from.controlB))
                to.motor[id].controlB = from.controlB;
            if (softrobot.util.haveProp(from.controlA))
                to.motor[id].controlA = from.controlA;
            if (softrobot.util.haveProp(from.torqueMin))
                to.motor[id].torqueMin = from.torqueMin;
            if (softrobot.util.haveProp(from.torqueMax))
                to.motor[id].torqueMax = from.torqueMax;
            to.motor[id].pose = softrobot.util.limitNum(to.motor[id].pose, to.motor[id].lengthMin, to.motor[id].lengthMax);
        }
        message_command.setMotorState = setMotorState;
        function updateRemoteMotorState(inst) {
            if (inst.motorId >= softrobot.device.robotInfo.nMotor) {
                console.log("motorId larger than motor number");
                return;
            }
            if (softrobot.util.haveProp(inst.pose) || softrobot.util.haveProp(inst.velocity)) {
                if (softrobot.util.haveProp(inst.pose))
                    softrobot.device.robotState.motor[inst.motorId].pose = softrobot.util.limitNum(inst.pose, softrobot.device.robotState.motor[inst.motorId].lengthMin, softrobot.device.robotState.motor[inst.motorId].lengthMax);
                if (softrobot.util.haveProp(inst.velocity))
                    softrobot.device.robotState.motor[inst.motorId].velocity = inst.velocity;
                var pose = softrobot.device.robotState.getPropArray("pose", softrobot.device.robotState.motor);
                var velocity = softrobot.device.robotState.getPropArray("velocity", softrobot.device.robotState.motor);
                // softrobot.movement.sendKeyframeQueue.clear();
                message_command.setMotorDirect({
                    pose: pose,
                    velocity: velocity
                });
            }
            if (softrobot.util.haveProp(inst.lengthMin) || softrobot.util.haveProp(inst.lengthMax)) {
                if (softrobot.util.haveProp(inst.lengthMin))
                    softrobot.device.robotState.motor[inst.motorId].lengthMin = inst.lengthMin;
                if (softrobot.util.haveProp(inst.lengthMax))
                    softrobot.device.robotState.motor[inst.motorId].lengthMax = inst.lengthMax;
            }
            if (softrobot.util.haveProp(inst.controlK) || softrobot.util.haveProp(inst.controlB)) {
                if (softrobot.util.haveProp(inst.controlK))
                    softrobot.device.robotState.motor[inst.motorId].controlK = inst.controlK;
                if (softrobot.util.haveProp(inst.controlB))
                    softrobot.device.robotState.motor[inst.motorId].controlB = inst.controlB;
                var controlK = softrobot.device.robotState.getPropArray("controlK", softrobot.device.robotState.motor);
                var controlB = softrobot.device.robotState.getPropArray("controlB", softrobot.device.robotState.motor);
                message_command.setMotorParam({
                    paramType: softrobot.command.SetParamType.PT_PD,
                    params1: controlK,
                    params2: controlB
                });
            }
            if (softrobot.util.haveProp(inst.controlA)) {
                if (softrobot.util.haveProp(inst.controlA))
                    softrobot.device.robotState.motor[inst.motorId].controlA = inst.controlA;
                var controlA = softrobot.device.robotState.getPropArray("controlA", softrobot.device.robotState.motor);
                message_command.setMotorParam({
                    paramType: softrobot.command.SetParamType.PT_CURRENT,
                    params1: controlA,
                    params2: undefined
                });
            }
            if (softrobot.util.haveProp(inst.torqueMin) || softrobot.util.haveProp(inst.torqueMax)) {
                if (softrobot.util.haveProp(inst.torqueMin))
                    softrobot.device.robotState.motor[inst.motorId].torqueMin = inst.torqueMin;
                if (softrobot.util.haveProp(inst.torqueMax))
                    softrobot.device.robotState.motor[inst.motorId].torqueMax = inst.torqueMax;
                var torqueMin = softrobot.device.robotState.getPropArray("torqueMin", softrobot.device.robotState.motor);
                var torqueMax = softrobot.device.robotState.getPropArray("torqueMax", softrobot.device.robotState.motor);
                message_command.setMotorParam({
                    paramType: softrobot.command.SetParamType.PT_TORQUE_LIMIT,
                    params1: torqueMin,
                    params2: torqueMax
                });
            }
        }
        message_command.updateRemoteMotorState = updateRemoteMotorState;
        function updateLocalMotorState(inst) {
            if (inst.motorId >= softrobot.device.robotInfo.nMotor) {
                console.log("motorId larger than motor number");
                return;
            }
            setMotorState(softrobot.device.robotState, inst);
        }
        message_command.updateLocalMotorState = updateLocalMotorState;
        function updateRemoteDirect() {
            // softrobot.movement.sendKeyframeQueue.clear();
            message_command.setMotorDirect({
                pose: softrobot.device.robotState.getPropArray("pose", softrobot.device.robotState.motor),
                velocity: softrobot.device.robotState.getPropArray("velocity", softrobot.device.robotState.motor)
            });
        }
        message_command.updateRemoteDirect = updateRemoteDirect;
    })(message_command = softrobot.message_command || (softrobot.message_command = {}));
})(softrobot || (softrobot = {}));

// register callbacks
(function(softrobot) {
    (function (message_command) {
        message_command.registerCallback("onReceiveCIBoardinfo", message_command.onReceiveCIBoardinfo);
        message_command.registerCallback("onReceiveCISensor", message_command.onReceiveCISensor);
        message_command.registerCallback("onReceiveCIDirect", message_command.onReceiveCIDirect);
        message_command.registerCallback("onReceiveCIInterpolate", message_command.onReceiveCIInterpolate);
        message_command.registerCallback("onReceiveCISetparam", message_command.onReceiveCISetparam);
        message_command.registerCallback("onReceiveCIResetsensor", message_command.onReceiveCIResetsensor);
        message_command.registerCallback("onReceiveCIUMovement", message_command.onReceiveCIUMovement);
    })(message_command = softrobot.message_command || (softrobot.message_command = {}));
})(softrobot || (softrobot = {}));

(function (softrobot) {
    var movement;
    (function (movement) {
        var MovementSender = (function () {
            function MovementSender() {
                this.waitResponse = false;
                softrobot.message_command.onRcvCIUMovementMessage.push(this.onRcvCIUMovementMessage.bind(this));
                this.queryTimer = setTimeout(this.queryNOccupied.bind(this), MovementSender.OCCUPATION_QUERY_INTERVAL_MS);
            }
            MovementSender.prototype.queryNOccupied = function () {
                softrobot.message_command.setMovement({
                    movementCommandId: softrobot.command.CommandIdMovement.CI_M_QUERY
                });
                this.queryTimer = setTimeout(this.queryNOccupied.bind(this), MovementSender.OCCUPATION_QUERY_INTERVAL_MS);
            };
            MovementSender.prototype.onRcvCIUMovementMessage = function (data) {
                this.waitResponse = false;
                if (data.movementCommandId == softrobot.command.CommandIdMovement.CI_M_ADD_KEYFRAME || softrobot.command.CommandIdMovement.CI_M_QUERY) {
                    cancelTimeout(this.queryTimer);
                    this.queryTimer = setTimeout(this.queryNOccupied.bind(this), MovementSender.OCCUPATION_QUERY_INTERVAL_MS);
                }
            };
            MovementSender.prototype.canAddKeyframe = function (data) {
                if (this.waitResponse)
                    return false;
                for (var i = 0; i < data.motorCount; i++) {
                    if (softrobot.device.robotState.movementState.nOccupied[data.motorId[i]] >= MovementSender.MAX_NOCCUPIED)
                        return false;
                }
                if (softrobot.device.robotState.movementState.isPaused(data.movementId) >= 0)
                    return false;
                return true;
            };
            MovementSender.prototype.send = function (data) {
                switch (data.movementCommandId) {
                    case softrobot.command.CommandIdMovement.CI_M_ADD_KEYFRAME:
                        if (!this.canAddKeyframe(data))
                            return false;
                        this.waitResponse = true;
                        break;
                    case softrobot.command.CommandIdMovement.CI_M_PAUSE_MOV:
                        softrobot.device.robotState.movementState.pause(data.movementId);
                        break;
                    case softrobot.command.CommandIdMovement.CI_M_RESUME_MOV:
                        softrobot.device.robotState.movementState.resume(data.movementId);
                        break;
                    default:
                        break;
                }
                softrobot.message_command.setMovement(data);
                return true;
            };
            MovementSender.MAX_NOCCUPIED = 5;
            MovementSender.OCCUPATION_QUERY_INTERVAL_MS = 1000;
            return MovementSender;
        }());
        movement.MovementSender = MovementSender;
        var lastMovementId = 0;
        function getNewMovementId() {
            lastMovementId = lastMovementId + 1;
            if (lastMovementId > 255)
                lastMovementId = 1;
            return lastMovementId;
        }
        movement.getNewMovementId = getNewMovementId;
    })(movement = softrobot.movement || (softrobot.movement = {}));
})(softrobot || (softrobot = {}));
(function (softrobot) {
    var util;
    (function (util) {
        function haveProp(obj) {
            return !!obj || obj == 0;
        }
        util.haveProp = haveProp;
        function limitNum(num, min, max) {
            var res = num;
            res > max ? (res = max) : (res = res);
            res < min ? (res = min) : (res = res);
            return res;
        }
        util.limitNum = limitNum;
        function ab2str(buf) {
            return String.fromCharCode.apply(null, new Uint16Array(buf));
        }
        util.ab2str = ab2str;
        function str2ab(str) {
            var buf = new ArrayBuffer(str.length * 2);
            var bufView = new Uint16Array(buf);
            for (var i = 0, strLen = str.length; i < strLen; i++) {
                bufView[i] = str.charCodeAt(i);
            }
            return buf;
        }
        util.str2ab = str2ab;
        function str2abAscii(str) {
            var buf = new ArrayBuffer(str.length);
            var bufView = new Uint8Array(buf);
            for (var i = 0, strLen = str.length; i < strLen; i++) {
                bufView[i] = str.charCodeAt(i) >= 128 ? 63 : str.charCodeAt(i);
            }
            return buf;
        }
        util.str2abAscii = str2abAscii;
        function arrayEncoder(array, func, delimiter) {
            var res = "";
            if (array.length < 0)
                return res;
            res += func(array[0]);
            for (var i = 1; i < array.length; i++) {
                res += delimiter + func(array[i]);
            }
            return res;
        }
        util.arrayEncoder = arrayEncoder;
        function arrayDecoder(str, func, delimiter) {
            var res = [];
            var strArray = str.split(delimiter);
            for (var _i = 0, strArray_1 = strArray; _i < strArray_1.length; _i++) {
                var str_1 = strArray_1[_i];
                res.push(func(str_1));
            }
            return res;
        }
        util.arrayDecoder = arrayDecoder;
        function interpolate(x1, y1, x2, y2, x) {
            return (y2 - y1) / (x2 - x1) * (x - x1) + y1;
        }
        util.interpolate = interpolate;
    })(util = softrobot.util || (softrobot.util = {}));
})(softrobot || (softrobot = {}));

// module.exports = softrobot;
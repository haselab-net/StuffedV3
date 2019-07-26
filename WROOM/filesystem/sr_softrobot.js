var softrobot;
(function (softrobot) {
    var command;
    (function (command) {
        var SetParamType;
        (function (SetParamType) {
            SetParamType[SetParamType["PT_PD"] = 0] = "PT_PD";
            SetParamType[SetParamType["PT_CURRENT"] = 1] = "PT_CURRENT";
            SetParamType[SetParamType["PT_TORQUE_LIMIT"] = 2] = "PT_TORQUE_LIMIT";
            SetParamType[SetParamType["PT_BOARD_ID"] = 3] = "PT_BOARD_ID";
        })(SetParamType = command.SetParamType || (command.SetParamType = {}));
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
            if (device.robotState.motor.length != device.robotInfo.nMotor)
                device.robotState.motor = resizeMotorStateArray(device.robotState.motor, device.robotInfo.nMotor);
            if (device.robotState.current.length != device.robotInfo.nCurrent)
                device.robotState.current = resizeArray(device.robotState.current, device.robotInfo.nCurrent);
            if (device.robotState.force.length != device.robotInfo.nForces)
                device.robotState.force = resizeArray(device.robotState.force, device.robotInfo.nForces);
            if (device.robotState.movementState.nOccupied.length != device.robotInfo.nMotor)
            device.robotState.movementState.nOccupied = resizeArray(device.robotState.movementState.nOccupied, device.robotInfo.nMotor);
        }
        device.checkRobotState = checkRobotState;
    })(device = softrobot.device || (softrobot.device = {}));
})(softrobot || (softrobot = {}));

// sr_command
(function(softrobot) {
    softrobot.message_command = require("sr_command");
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
        message_command.onRcvCIUMovementMessage = [];
    })(message_command = softrobot.message_command || (softrobot.message_command = {}));
})(softrobot || (softrobot = {}));

// register callbacks
(function(softrobot) {
    (function (message_command) {
        message_command.registerCallback("onReceiveCIBoardinfo", message_command.onReceiveCIBoardinfo);
        message_command.registerCallback("onReceiveCIDirect", message_command.onReceiveCIDirect);
        message_command.registerCallback("onReceiveCIUMovement", message_command.onReceiveCIUMovement);
    })(message_command = softrobot.message_command || (softrobot.message_command = {}));
})(softrobot || (softrobot = {}));

(function (softrobot) {
    var movement;
    (function (movement) {
        var movementSender = require("sr_movement");
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

// module.exports = softrobot;
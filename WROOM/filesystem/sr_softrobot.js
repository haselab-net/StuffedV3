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
            CommandId[CommandId["CIU_NCOMMAND"] = 14] = "CIU_NCOMMAND";
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
                this.nTarget = 1;
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
                        a[key] = array[0];
                    }
                    array.concat(a);
                }
                else
                    array.slice(0, size);
                return array;
            }
            if (device.robotState.motor.length != device.robotInfo.nMotor)
                device.robotState.motor = resizeArray(device.robotState.motor, device.robotInfo.nMotor);
            if (device.robotState.current.length != device.robotInfo.nCurrent)
                device.robotState.current = resizeArray(device.robotState.current, device.robotInfo.nCurrent);
            if (device.robotState.force.length != device.robotInfo.nForces)
                device.robotState.force = resizeArray(device.robotState.force, device.robotInfo.nForces);
            if (device.robotState.touch.length != device.robotInfo.nTouch)
                device.robotState.touch = resizeArray(device.robotState.touch, device.robotInfo.nTouch);
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
        function onReceiveCISensor(data) {
            softrobot.device.robotState.setPropArray("pose", data.pose, softrobot.device.robotState.motor);
            softrobot.device.robotState.current = data.current;
            softrobot.device.robotState.force = data.force;
            for (var i = 0; i < message_command.onRcvCISensorMessage.length; i++) {
                message_command.onRcvCISensorMessage[i]();
            }
        }
        message_command.onReceiveCISensor = onReceiveCISensor;
        function onReceiveCIDirect(data) {
            softrobot.device.robotState.setPropArray("pose", data.pose, softrobot.device.robotState.motor);
            softrobot.device.robotState.setPropArray("velocity", data.velocity, softrobot.device.robotState.motor);
        }
        message_command.onReceiveCIDirect = onReceiveCIDirect;
        function onReceiveCIInterpolate(data) {
            softrobot.device.robotState.setPropArray("pose", data.pose, softrobot.device.robotState.motor);
            var rmin = softrobot.device.robotState.interpolateTargetCountOfReadMin = data.targetCountReadMin;
            var rmax = softrobot.device.robotState.interpolateTargetCountOfReadMax = data.targetCountReadMax;
            var tmin = softrobot.device.robotState.interpolateTickMin = data.tickMin;
            var tmax = softrobot.device.robotState.interpolateTickMax = data.tickMax;
            if (softrobot.device.robotState.interpolateTargetCountOfWrite < 0)
                softrobot.device.robotState.interpolateTargetCountOfWrite = (rmax + 1) % 256;
            var wc = softrobot.device.robotState.interpolateTargetCountOfWrite;
            softrobot.device.robotState.nInterpolateRemain = wc >= rmax ? wc - rmax : wc - rmax + 256;
            var readDiff = rmax >= rmin ? rmax - rmin : rmax - rmin + 256;
            softrobot.device.robotState.nInterpolateVacancy = softrobot.device.robotState.nInterpolateTotal - softrobot.device.robotState.nInterpolateRemain - (readDiff + 1);
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
        message_command.onRcvCIBoardInfoMessage = [];
        message_command.onRcvCISensorMessage = [];
        message_command.onRcvCIDirectMessage = [];
        message_command.onRcvCIInterpolateMessage = [];
        message_command.onRcvCIResetSensorMessage = [];
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
                softrobot.movement.sendKeyframeQueue.clear();
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
            softrobot.movement.sendKeyframeQueue.clear();
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
    })(message_command = softrobot.message_command || (softrobot.message_command = {}));
})(softrobot || (softrobot = {}));

(function (softrobot) {
    var movement;
    (function (movement) {
        var SendKeyframeQueue = (function () {
            function SendKeyframeQueue(stuckChecker, sender, receiver) {
                if (sender === void 0) { sender = softrobot.message_command.setMotorInterpolate; }
                if (receiver === void 0) { receiver = softrobot.message_command.onRcvCIInterpolateMessage; }
                this.sender = sender;
                this.queue = [];
                this.blockQuery = false;
                this.remoteVacancy = 0;
                this.lastTimeWriteCount = 0;
                receiver.push(this.onInterpolateMessage.bind(this));
                if (stuckChecker) {
                    this.lastTimeWriteCount = softrobot.device.robotState.interpolateTargetCountOfWrite;
                    setInterval(this.check, SendKeyframeQueue.STUCK_CHECKER_INTERVAL);
                }
            }
            SendKeyframeQueue.prototype.check = function () {
                if (this.queue.length > 0 && softrobot.device.robotState.interpolateTargetCountOfWrite == this.lastTimeWriteCount) {
                    this.queryVacancy();
                }
                else {
                    this.lastTimeWriteCount = softrobot.device.robotState.interpolateTargetCountOfWrite;
                }
            };
            SendKeyframeQueue.prototype.enqueue = function (keyframe) {
                if (this.queue.length == SendKeyframeQueue.MAX_SIZE)
                    return -1;
                var len = this.queue.push(keyframe);
                this.queryVacancy();
                return len;
            };
            SendKeyframeQueue.prototype.dequeue = function () {
                if (this.queue.length == 0)
                    return undefined;
                else
                    return this.queue.splice(0, 1)[0];
            };
            SendKeyframeQueue.prototype.clear = function () {
                this.queue = [];
            };
            SendKeyframeQueue.prototype.send = function (keyframe) {
                softrobot.device.robotState.interpolateTargetCountOfWrite += 1;
                softrobot.device.robotState.interpolateTargetCountOfWrite %= 256;
                var dataObj = {
                    pose: keyframe.pose,
                    period: keyframe.period,
                    targetCountWrite: softrobot.device.robotState.interpolateTargetCountOfWrite
                };
                this.sender(dataObj);
                return true;
            };
            SendKeyframeQueue.prototype.queryVacancy = function () {
                var _this = this;
                if (this.blockQuery)
                    return;
                var queryObj = {
                    pose: new Array(softrobot.device.robotInfo.nMotor),
                    period: 0,
                    targetCountWrite: 0
                };
                this.sender(queryObj);
                this.blockQuery = true;
                setTimeout(function () { _this.blockQuery = false; }, SendKeyframeQueue.BLOCK_QUERY_TIME);
            };
            SendKeyframeQueue.prototype.onInterpolateMessage = function () {
                this.remoteVacancy = softrobot.device.robotState.nInterpolateVacancy;
                console.log("interpolateTargetCountOfWrite: ", softrobot.robotState.interpolateTargetCountOfWrite)
                console.log("interpolateTargetCountOfReadMin: ", softrobot.robotState.interpolateTargetCountOfReadMin)
                console.log("interpolateTargetCountOfReadMax: ", softrobot.robotState.interpolateTargetCountOfReadMax)
                console.log("vacancy: ", this.remoteVacancy);
                if (this.remoteVacancy >= softrobot.device.robotState.nInterpolateTotal - SendKeyframeQueue.REMOTE_MAX_SIZE && this.queue.length > 0) {
                    var keyframe = this.dequeue();
                    this.send(keyframe);
                }
                else if (this.queue.length > 0) {
                    this.wait();
                }
            };
            SendKeyframeQueue.prototype.wait = function () {
                var _this = this;
                setTimeout(function () { _this.queryVacancy(); }, 50);
            };
            SendKeyframeQueue.MAX_SIZE = 20;
            SendKeyframeQueue.REMOTE_MAX_SIZE = 6;
            SendKeyframeQueue.STUCK_CHECKER_INTERVAL = 2000;
            SendKeyframeQueue.BLOCK_QUERY_TIME = 1000;
            return SendKeyframeQueue;
        }());
        movement.SendKeyframeQueue = SendKeyframeQueue;
        movement.sendKeyframeQueue = new SendKeyframeQueue(false);
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
            res > max ? res = max : res = res;
            res < min ? res = min : res = res;
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
    })(util = softrobot.util || (softrobot.util = {}));
})(softrobot || (softrobot = {}));

module.exports = softrobot; 
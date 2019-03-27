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
            CommandId[CommandId["CI_INTERPOLATE"] = 6] = "CI_INTERPOLATE";
            CommandId[CommandId["CI_FORCE_CONTROL"] = 7] = "CI_FORCE_CONTROL";
            CommandId[CommandId["CI_PDPARAM"] = 8] = "CI_PDPARAM";
            CommandId[CommandId["CI_TORQUE_LIMIT"] = 9] = "CI_TORQUE_LIMIT";
            CommandId[CommandId["CI_RESET_SENSOR"] = 10] = "CI_RESET_SENSOR";
            CommandId[CommandId["CI_NCOMMAND"] = 11] = "CI_NCOMMAND";
            CommandId[CommandId["CIU_TEXT"] = 11] = "CIU_TEXT";
            CommandId[CommandId["CIU_SET_IPADDRESS"] = 12] = "CIU_SET_IPADDRESS";
            CommandId[CommandId["CIU_GET_IPADDRESS"] = 13] = "CIU_GET_IPADDRESS";
            CommandId[CommandId["CIU_NCOMMAND"] = 14] = "CIU_NCOMMAND";
            CommandId[CommandId["CIU_NONE"] = -1] = "CIU_NONE"; //  no command is in receiving state.
        })(CommandId = command.CommandId || (command.CommandId = {}));
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
        })(PacketId = command.PacketId || (command.PacketId = {}));
    })(command = softrobot.command || (softrobot.command = {}));
})(softrobot || (softrobot = {}));
/**
 * Store the information of softrobot
 */
var softrobot;
(function (softrobot) {
    var device;
    (function (device) {
        /////////////////////////////////////////////////////////////////
        /////////////////////////    State    ///////////////////////////
        /////////////////////////////////////////////////////////////////
        /**
         * information of robot hardware
         * @description (can not be changed on web side)
         */
        var RobotInfo = /** @class */ (function () {
            function RobotInfo() {
                this.initialize();
            }
            /**
             * initialize parameters with default value
             */
            RobotInfo.prototype.initialize = function () {
                this.systemId = 0;
                this.nTarget = 1;
                this.nMotor = 3;
                this.nCurrent = 0;
                this.nForces = 0;
                this.macAddress = new ArrayBuffer(6);
            };
            return RobotInfo;
        }());
        device.RobotInfo = RobotInfo;
        device.robotInfo = new RobotInfo();
        /**
         * state/parameter of a single motor
         */
        var MotorState = /** @class */ (function () {
            function MotorState() {
                this.initialize();
            }
            /**
             * initialize parameters with default value
             */
            MotorState.prototype.initialize = function () {
                this.pose = 0;
                this.velocity = 0;
                this.lengthMin = -5000;
                this.lengthMax = 5000;
                this.controlK = 4096;
                this.controlB = 2048;
                this.torqueMin = -1024;
                this.torqueMax = 1024;
            };
            return MotorState;
        }());
        device.MotorState = MotorState;
        /**
         * state/parameter of robot
         */
        var RobotState = /** @class */ (function () {
            function RobotState() {
                this.initialize();
            }
            /**
             * initialize parameters with default value
             */
            RobotState.prototype.initialize = function () {
                this.motor = new Array(device.robotInfo.nMotor);
                for (var index = 0; index < this.motor.length; index++) {
                    this.motor[index] = new MotorState();
                }
                this.current = new Array(device.robotInfo.nCurrent);
                for (var index = 0; index < this.motor.length; index++) {
                    this.current[index] = 0;
                }
                this.force = new Array(device.robotInfo.nForces);
                for (var index = 0; index < this.motor.length; index++) {
                    this.force[index] = 0;
                }
                this.nInterpolateTotal = 3;
                this.interpolateTargetCountOfWrite = 0;
                this.interpolateTargetCountOfRead = 0;
                this.interpolateTickMin = 0;
                this.interpolateTickMax = 0;
                this.nInterpolateRemain = 0;
                this.nInterpolateVacancy = 3;
            };
            /**
             * combine props of an object array to an prop array
             * @description assume object have property p, this function convert object[] into p[]
             * @param name one property (type T) name of object
             * @param array array of object
             */
            RobotState.prototype.getPropArray = function (name, array) {
                if (!(name in array[0])) {
                    console.log("ERROR: No property named " + name + "in array");
                    return null;
                }
                var res = new Array();
                array.forEach(function (element) {
                    res.push(element[name]);
                });
                return res;
            };
            /**
             * set props of an object array to an prop array
             * @param name name of the property
             * @param pArray property value array
             * @param oArray object array
             */
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
        /**
         * check the length of pose/velocity/current/force array in robot state is the same as corresponding value in robot info
         * @description if current array length is less than target length, the insufficient part of array will be initialized with array[0]
         */
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
        }
        device.checkRobotState = checkRobotState;
    })(device = softrobot.device || (softrobot.device = {}));
})(softrobot || (softrobot = {}));
/**
 * Provide API for send/receive command message to/from softrobot
 * @author gzl
 */
var softrobot;
(function (softrobot) {
    var message_command;
    (function (message_command) {
        /////////////////////////////////////////////////////////////////
        /////////////////////////    Callback    ////////////////////////
        /////////////////////////////////////////////////////////////////
        message_command.onRcvCIBoardInfoMessage = function () { };
        message_command.onRcvCISensorMessage = function () { };
        /////////////////////////////////////////////////////////////////
        /////////////////////////    Receive    /////////////////////////
        /////////////////////////////////////////////////////////////////
        function messageHandler(packet) {
            switch (packet.command) {
                case softrobot.command.CommandId.CI_BOARD_INFO:
                    {
                        softrobot.device.robotInfo = packet.data.data;
                        softrobot.device.checkRobotState();
                        message_command.onRcvCIBoardInfoMessage();
                        break;
                    }
                case softrobot.command.CommandId.CI_SENSOR:
                    {
                        var data = packet.data.data;
                        if (data.pose.length != softrobot.device.robotInfo.nMotor) { // number of motors does not match
                            requireBoardInfo();
                            break;
                        }
                        softrobot.device.robotState.setPropArray("pose", data.pose, softrobot.device.robotState.motor);
                        softrobot.device.robotState.current = data.current;
                        softrobot.device.robotState.force = data.force;
                        message_command.onRcvCISensorMessage();
                        break;
                    }
                case softrobot.command.CommandId.CI_DIRECT:
                    {
                        var data = packet.data.data;
                        if (data.pose.length != softrobot.device.robotInfo.nMotor) { // number of motors does not match
                            requireBoardInfo();
                            break;
                        }
                        softrobot.device.robotState.setPropArray("pose", data.pose, softrobot.device.robotState.motor);
                        softrobot.device.robotState.setPropArray("velocity", data.velocity, softrobot.device.robotState.motor);
                        break;
                    }
                case softrobot.command.CommandId.CI_FORCE_CONTROL:
                    {
                        var data = packet.data.data;
                        if (data.pose.length != softrobot.device.robotInfo.nMotor) { // number of motors does not match
                            requireBoardInfo();
                            break;
                        }
                        softrobot.device.robotState.setPropArray("pose", data.pose, softrobot.device.robotState.motor);
                        softrobot.device.robotState.interpolateTargetCountOfRead = data.targetCountRead;
                        softrobot.device.robotState.interpolateTickMin = data.tickMin;
                        softrobot.device.robotState.interpolateTickMax = data.tickMax;
                        softrobot.device.robotState.interpolateTargetCountOfRead = data.nRemain;
                        softrobot.device.robotState.nInterpolateVacancy = data.nVacancy;
                        break;
                    }
                default:
                    {
                        console.log("softrobot.message::messageHandler: unrecognized command");
                        break;
                    }
            }
        }
        message_command.messageHandler = messageHandler;
        /////////////////////////////////////////////////////////////////
        /////////////////////////    Send    ////////////////////////////
        /////////////////////////////////////////////////////////////////
        message_command.sendMessage = function (packet) { };
        /**
         * update motor state 'to' with instruction in 'from'
         * @param to robot state in which motor state will be altered later
         * @param from motor instruction which to be used to change motor state
         */
        function setMotorState(to, from) {
            var id = from.motorId;
            if (id >= to.motor.length)
                return;
            if (softrobot.util.haveProp(from.pose))
                to.motor[id].pose = from.pose;
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
            if (softrobot.util.haveProp(from.torqueMin))
                to.motor[id].torqueMin = from.torqueMin;
            if (softrobot.util.haveProp(from.torqueMax))
                to.motor[id].torqueMax = from.torqueMax;
            to.motor[id].pose = softrobot.util.limitNum(to.motor[id].pose, to.motor[id].lengthMin, to.motor[id].lengthMax);
        }
        message_command.setMotorState = setMotorState;
        /**
         * set local motor state and update it to remote hardware
         * @param inst motor instruction
         */
        function updateRemoteMotorState(inst) {
            if (inst.motorId >= softrobot.device.robotInfo.nMotor) {
                console.log("motorId larger than motor number");
                return;
            }
            console.log("update remote motor state");
            console.log(inst);
            if (softrobot.util.haveProp(inst.pose) || softrobot.util.haveProp(inst.velocity)) {
                if (softrobot.util.haveProp(inst.pose))
                    softrobot.device.robotState.motor[inst.motorId].pose = softrobot.util.limitNum(inst.pose, softrobot.device.robotState.motor[inst.motorId].lengthMin, softrobot.device.robotState.motor[inst.motorId].lengthMax);
                if (softrobot.util.haveProp(inst.velocity))
                    softrobot.device.robotState.motor[inst.motorId].velocity = inst.velocity;
                var pose = softrobot.device.robotState.getPropArray("pose", softrobot.device.robotState.motor);
                var velocity = softrobot.device.robotState.getPropArray("velocity", softrobot.device.robotState.motor);
                var p = new softrobot.packet_command.Packet(softrobot.command.CommandId.CI_DIRECT, new softrobot.packet_command.PacketPoseDirectData({
                    pose: pose,
                    velocity: velocity
                }));
                message_command.sendMessage(p);
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
                var p = new softrobot.packet_command.Packet(softrobot.command.CommandId.CI_PDPARAM, new softrobot.packet_command.PacketPdParamData({
                    controlK: controlK,
                    controlB: controlB
                }));
                message_command.sendMessage(p);
            }
            if (softrobot.util.haveProp(inst.torqueMin) || softrobot.util.haveProp(inst.torqueMax)) {
                if (softrobot.util.haveProp(inst.torqueMin))
                    softrobot.device.robotState.motor[inst.motorId].torqueMin = inst.torqueMin;
                if (softrobot.util.haveProp(inst.torqueMax))
                    softrobot.device.robotState.motor[inst.motorId].torqueMax = inst.torqueMax;
                var torqueMin = softrobot.device.robotState.getPropArray("torqueMin", softrobot.device.robotState.motor);
                var torqueMax = softrobot.device.robotState.getPropArray("torqueMax", softrobot.device.robotState.motor);
                var p = new softrobot.packet_command.Packet(softrobot.command.CommandId.CI_TORQUE_LIMIT, new softrobot.packet_command.PacketTorqueLimitData({
                    torqueMin: torqueMin,
                    torqueMax: torqueMax
                }));
                message_command.sendMessage(p);
            }
        }
        message_command.updateRemoteMotorState = updateRemoteMotorState;
        /**
         * only set local motor state
         * @param inst motor instruction
         */
        function updateLocalMotorState(inst) {
            if (inst.motorId >= softrobot.device.robotInfo.nMotor) {
                console.log("motorId larger than motor number");
                return;
            }
            console.log("update local motor state");
            console.log(inst);
            if (softrobot.util.haveProp(inst.pose) || softrobot.util.haveProp(inst.velocity)) {
                if (softrobot.util.haveProp(inst.pose))
                    softrobot.device.robotState.motor[inst.motorId].pose = softrobot.util.limitNum(inst.pose, softrobot.device.robotState.motor[inst.motorId].lengthMin, softrobot.device.robotState.motor[inst.motorId].lengthMax);
                if (softrobot.util.haveProp(inst.velocity))
                    softrobot.device.robotState.motor[inst.motorId].velocity = inst.velocity;
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
            }
            if (softrobot.util.haveProp(inst.torqueMin) || softrobot.util.haveProp(inst.torqueMax)) {
                if (softrobot.util.haveProp(inst.torqueMin))
                    softrobot.device.robotState.motor[inst.motorId].torqueMin = inst.torqueMin;
                if (softrobot.util.haveProp(inst.torqueMax))
                    softrobot.device.robotState.motor[inst.motorId].torqueMax = inst.torqueMax;
            }
        }
        message_command.updateLocalMotorState = updateLocalMotorState;
        /**
         * update remote motor pose and velocity (direct mode) by local robot state
         */
        function updateMotorPVDirect() {
            var pose = softrobot.device.robotState.getPropArray("pose", softrobot.device.robotState.motor);
            var velocity = softrobot.device.robotState.getPropArray("velocity", softrobot.device.robotState.motor);
            console.log("update remote direct");
            console.log({
                pose: pose,
                velocity: velocity
            });
            var p = new softrobot.packet_command.Packet(softrobot.command.CommandId.CI_DIRECT, new softrobot.packet_command.PacketPoseDirectData({
                pose: pose,
                velocity: velocity
            }));
            message_command.sendMessage(p);
        }
        message_command.updateMotorPVDirect = updateMotorPVDirect;
        /**
         * update remote motor pose and velocity (interpolate mode) by local robot state
         * @param period period to interpolate
         */
        function updateMotorPVInterpolate(period) {
            var pose = softrobot.device.robotState.getPropArray("pose", softrobot.device.robotState.motor);
            console.log("update remote interpolate");
            console.log({
                pose: pose,
                period: period
            });
            var p = new softrobot.packet_command.Packet(softrobot.command.CommandId.CI_INTERPOLATE, new softrobot.packet_command.PacketPoseInterpolateData({
                pose: pose,
                period: period,
                targetCount: softrobot.device.robotState.interpolateTargetCountOfWrite
            }));
            message_command.sendMessage(p);
            if (period != 0)
                softrobot.device.robotState.interpolateTargetCountOfWrite++;
        }
        message_command.updateMotorPVInterpolate = updateMotorPVInterpolate;
        /**
         * require for board info
         */
        function requireBoardInfo() {
            var p = new softrobot.packet_command.Packet(softrobot.command.CommandId.CI_BOARD_INFO, new softrobot.packet_command.PacketBoardInfoData({}));
            message_command.sendMessage(p);
        }
        message_command.requireBoardInfo = requireBoardInfo;
        /**
         * require for sensor info
         */
        function requireSensorInfo() {
            var p = new softrobot.packet_command.Packet(softrobot.command.CommandId.CI_SENSOR, new softrobot.packet_command.PacketSensorInfoData({}));
            message_command.sendMessage(p);
        }
        message_command.requireSensorInfo = requireSensorInfo;
    })(message_command = softrobot.message_command || (softrobot.message_command = {}));
})(softrobot || (softrobot = {}));
/**
 * Provide interface of command packet for websocket communication between web and softrobot
 * @author gzl
 */
var softrobot;
(function (softrobot) {
    var packet_command;
    (function (packet_command) {
        /////////////////////////////////////////////////////////////////
        /////////////////////////    Packet    //////////////////////////
        /////////////////////////////////////////////////////////////////
        /**
         * generate count for packet
         * @deprecated
         */
        var PacketCount = /** @class */ (function () {
            function PacketCount() {
            }
            PacketCount.getId = function () {
                var tmp = PacketCount.next_id++;
                if (PacketCount.next_id > PacketCount.max_id)
                    PacketCount.next_id = 0;
                return tmp;
            };
            PacketCount.next_id = 0;
            PacketCount.max_id = 3000; // must smaller than MAX_SHORT
            return PacketCount;
        }());
        packet_command.PacketCount = PacketCount;
        /**
         * content of a websocket packet
         */
        var Packet = /** @class */ (function () {
            function Packet(com, da, len) {
                this.command = com;
                this.data = da;
                len ? this.length = len : this.length = this.getPacketLength();
                if (this.length > Packet.MAXLEN) {
                    console.log("softrobot.message.Pakcet::constructor: length of packet exceeds MAXLEN");
                }
            }
            Packet.prototype.getPacketLength = function () {
                return Packet.HEADERLEN + this.data.getDataLength();
            };
            /**
             * convert this packet object to binary buffer
             * @returns ArrayBuffer | null (if convert to binary failed)
             */
            Packet.prototype.toBinary = function () {
                if (!this.toBinaryCheck())
                    return null;
                // fill header
                var buf = new ArrayBuffer(this.length);
                var dataview = new Int16Array(buf);
                dataview[0] = this.length;
                dataview[1] = this.command;
                // fill data
                var dataPV = new Int16Array(buf, Packet.HEADERLEN);
                var dataBi = this.data.toBinary();
                if (!dataBi)
                    return null;
                var dataDV = new Int16Array(dataBi);
                dataPV.set(dataDV);
                return buf;
            };
            Packet.prototype.toBinaryCheck = function () {
                return true;
            };
            /**
             * convert binary buffer to packet object
             * @returns Packet | null (if convert to Packet failed)
             */
            Packet.fromBinary = function (bin) {
                // get header
                var dataview = new Int16Array(bin);
                var len = dataview[0];
                if (len > this.MAXLEN)
                    return null;
                var com = dataview[1];
                // get data
                var comStr = softrobot.command.CommandId[com];
                var dataArray = bin.slice(Packet.HEADERLEN, len);
                var da = null;
                switch (com) {
                    case softrobot.command.CommandId.CI_BOARD_INFO:
                        {
                            da = PacketBoardInfoData.fromBinary(dataArray);
                            break;
                        }
                    case softrobot.command.CommandId.CI_SENSOR:
                        {
                            da = PacketSensorInfoData.fromBinary(dataArray);
                            break;
                        }
                    case softrobot.command.CommandId.CI_DIRECT:
                        {
                            da = PacketPoseDirectData.fromBinary(dataArray);
                            break;
                        }
                    case softrobot.command.CommandId.CI_FORCE_CONTROL:
                        {
                            da = PacketPoseForceControlData.fromBinary(dataArray);
                            break;
                        }
                    default:
                        {
                            return null;
                        }
                }
                if (!da)
                    return null;
                var res = new Packet(com, da, len);
                return res;
            };
            Packet.MAXLEN = 1500;
            Packet.HEADERLEN = 4;
            return Packet;
        }());
        packet_command.Packet = Packet;
        // 1 CI_BOARD_INFO
        var PacketBoardInfoData = /** @class */ (function () {
            function PacketBoardInfoData(da) {
                this.data = da;
            }
            PacketBoardInfoData.prototype.getDataLength = function () {
                return 0;
            };
            PacketBoardInfoData.prototype.toBinary = function () {
                return new ArrayBuffer(0);
            };
            PacketBoardInfoData.fromBinary = function (bin) {
                if (bin.byteLength != 16)
                    return null;
                var dataView = new Int16Array(bin);
                var data = new softrobot.device.RobotInfo();
                data.systemId = dataView[0];
                data.nTarget = dataView[1];
                data.nMotor = dataView[2];
                data.nCurrent = dataView[3];
                data.nForces = dataView[4];
                data.macAddress = bin.slice(10, 16);
                var res = new PacketBoardInfoData(data);
                return res;
            };
            return PacketBoardInfoData;
        }());
        packet_command.PacketBoardInfoData = PacketBoardInfoData;
        var PacketSensorInfoData = /** @class */ (function () {
            function PacketSensorInfoData(data) {
                this.data = data;
            }
            PacketSensorInfoData.prototype.getDataLength = function () {
                return 0;
            };
            PacketSensorInfoData.prototype.toBinary = function () {
                return new ArrayBuffer(0);
            };
            PacketSensorInfoData.fromBinary = function (bin) {
                var dataView = new Int16Array(bin);
                var data;
                if (dataView.length != softrobot.device.robotInfo.nMotor + softrobot.device.robotInfo.nCurrent + softrobot.device.robotInfo.nForces) {
                    console.log("softrobot.message.PacketSensorInfoData::fromBinary: length of data does not match nMotor");
                    return null;
                }
                data.pose = new Array(softrobot.device.robotInfo.nMotor);
                data.current = new Array(softrobot.device.robotInfo.nCurrent);
                data.force = new Array(softrobot.device.robotInfo.nForces);
                var p = 0;
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    data.pose[i] = dataView[p++];
                }
                for (var i = 0; i < softrobot.device.robotInfo.nCurrent; i++) {
                    data.current[i] = dataView[p++];
                }
                for (var i = 0; i < softrobot.device.robotInfo.nForces; i++) {
                    data.force[i] = dataView[p++];
                }
                var res = new PacketSensorInfoData(data);
                return res;
            };
            return PacketSensorInfoData;
        }());
        packet_command.PacketSensorInfoData = PacketSensorInfoData;
        var PacketPoseDirectData = /** @class */ (function () {
            function PacketPoseDirectData(da) {
                this.data = da;
            }
            PacketPoseDirectData.prototype.getDataLength = function () {
                return softrobot.device.robotInfo.nMotor * 2 * 2;
            };
            PacketPoseDirectData.prototype.toBinary = function () {
                var res = new ArrayBuffer(this.getDataLength());
                var dataView = new Int16Array(res);
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    dataView[i] = this.data.pose[i];
                }
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    dataView[i + softrobot.device.robotInfo.nMotor] = this.data.velocity[i];
                }
                return res;
            };
            PacketPoseDirectData.fromBinary = function (bin) {
                var dataView = new Int16Array(bin);
                var data = { pose: [], velocity: [] };
                if (dataView.byteLength != softrobot.device.robotInfo.nMotor * 2 * 2) {
                    console.log("softrobot.message.PacketPoseDirectData::fromBinary: length of data does not match nMotor");
                    return null;
                }
                var p = 0;
                data.pose = new Array(softrobot.device.robotInfo.nMotor);
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    data.pose[i] = dataView[p];
                    p++;
                }
                data.velocity = new Array(softrobot.device.robotInfo.nMotor);
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    data.velocity[i] = dataView[p];
                    p++;
                }
                var res = new PacketPoseDirectData(data);
                return res;
            };
            return PacketPoseDirectData;
        }());
        packet_command.PacketPoseDirectData = PacketPoseDirectData;
        var PacketPoseInterpolateData = /** @class */ (function () {
            function PacketPoseInterpolateData(da) {
                this.data = da;
            }
            PacketPoseInterpolateData.prototype.getDataLength = function () {
                return softrobot.device.robotInfo.nMotor * 2 + 2 * 2;
            };
            PacketPoseInterpolateData.prototype.toBinary = function () {
                var res = new ArrayBuffer(this.getDataLength());
                var dataView = new Int16Array(res);
                var i = 0;
                for (i; i < softrobot.device.robotInfo.nMotor; i++) {
                    dataView[i] = this.data.pose[i];
                }
                dataView[i++] = this.data.period;
                dataView[i++] = this.data.targetCount;
                return res;
            };
            PacketPoseInterpolateData.fromBinary = function (bin) {
                return null;
            };
            return PacketPoseInterpolateData;
        }());
        packet_command.PacketPoseInterpolateData = PacketPoseInterpolateData;
        var PacketPoseForceControlData = /** @class */ (function () {
            function PacketPoseForceControlData(da) {
                this.data = da;
            }
            PacketPoseForceControlData.prototype.getDataLength = function () {
                return softrobot.device.robotInfo.nMotor * 2 + 2 * 2 + softrobot.device.robotInfo.nForces * 3 * 2;
            };
            PacketPoseForceControlData.prototype.toBinary = function () {
                var res = new ArrayBuffer(this.getDataLength());
                var dataView = new Int16Array(res);
                var p = 0;
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    dataView[p++] = this.data.pose[i];
                }
                dataView[p++] = this.data.period;
                dataView[p++] = this.data.targetCountWrite;
                for (var i = 0; i < softrobot.device.robotInfo.nForces; i++) {
                    for (var j = 0; j < 3; j++) {
                        dataView[p++] = this.data.jacob[i][j];
                    }
                }
                return res;
            };
            PacketPoseForceControlData.fromBinary = function (bin) {
                var dataView = new Int16Array(bin);
                var data;
                var p = 0;
                if (dataView.byteLength != softrobot.device.robotInfo.nMotor * 2 * 2 + 5 * 2) {
                    console.log("softrobot.message.PacketPoseForceControlData::fromBinary: length of data does not match nMotor");
                    return null;
                }
                data.pose = new Array(softrobot.device.robotInfo.nMotor);
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    data.pose[i] = dataView[p++];
                }
                data.targetCountRead = dataView[p++];
                data.tickMin = dataView[p++];
                data.tickMax = dataView[p++];
                data.nRemain = dataView[p++];
                data.nVacancy = dataView[p++];
                var res = new PacketPoseForceControlData(data);
                return res;
            };
            return PacketPoseForceControlData;
        }());
        packet_command.PacketPoseForceControlData = PacketPoseForceControlData;
        var PacketPdParamData = /** @class */ (function () {
            function PacketPdParamData(da) {
                this.data = da;
            }
            PacketPdParamData.prototype.getDataLength = function () {
                return softrobot.device.robotInfo.nMotor * 2 * 2;
            };
            PacketPdParamData.prototype.toBinary = function () {
                var res = new ArrayBuffer(this.getDataLength());
                console.log(res.byteLength);
                var dataView = new Int16Array(res);
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    dataView[i] = this.data.controlK[i];
                }
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    dataView[i + softrobot.device.robotInfo.nMotor] = this.data.controlB[i];
                }
                return res;
            };
            PacketPdParamData.fromBinary = function (bin) {
                return null;
            };
            return PacketPdParamData;
        }());
        packet_command.PacketPdParamData = PacketPdParamData;
        var PacketTorqueLimitData = /** @class */ (function () {
            function PacketTorqueLimitData(da) {
                this.data = da;
            }
            PacketTorqueLimitData.prototype.getDataLength = function () {
                return softrobot.device.robotInfo.nMotor * 2 * 2;
            };
            PacketTorqueLimitData.prototype.toBinary = function () {
                var res = new ArrayBuffer(this.getDataLength());
                var dataView = new Int16Array(res);
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    dataView[i] = this.data.torqueMin[i];
                }
                for (var i = 0; i < softrobot.device.robotInfo.nMotor; i++) {
                    dataView[i + softrobot.device.robotInfo.nMotor] = this.data.torqueMax[i];
                }
                return res;
            };
            PacketTorqueLimitData.fromBinary = function (bin) {
                return null;
            };
            return PacketTorqueLimitData;
        }());
        packet_command.PacketTorqueLimitData = PacketTorqueLimitData;
    })(packet_command = softrobot.packet_command || (softrobot.packet_command = {}));
})(softrobot || (softrobot = {}));
var softrobot;
(function (softrobot) {
    var util;
    (function (util) {
        // judge wether obj exists (not undefined and not null)
        function haveProp(obj) {
            return !!obj || obj == 0;
        }
        util.haveProp = haveProp;
        // limit num between min and max
        function limitNum(num, min, max) {
            var res = num;
            res > max ? res = max : res = res;
            res < min ? res = min : res = res;
            return res;
        }
        util.limitNum = limitNum;
        // convert array buffer to string
        function ab2str(buf) {
            return String.fromCharCode.apply(null, new Uint16Array(buf));
        }
        util.ab2str = ab2str;
        // convert string to array buffer
        function str2ab(str) {
            var buf = new ArrayBuffer(str.length * 2); // 2 bytes for each char
            var bufView = new Uint16Array(buf);
            for (var i = 0, strLen = str.length; i < strLen; i++) {
                bufView[i] = str.charCodeAt(i);
            }
            return buf;
        }
        util.str2ab = str2ab;
    })(util = softrobot.util || (softrobot.util = {}));
})(softrobot || (softrobot = {}));
var moduleSRCommand = ESP32.getNativeFunction("ModuleSRCommand");
if (moduleSRCommand === null) {
	log("Unable to find ModuleSRCommand");
	module.exports = null;
	exit;
}

var internalSRCommand = {};
moduleSRCommand(internalSRCommand);

var _ret = {
    requireBoardInfo: function () {
        internalSRCommand.requireBoardInfo();
    },
    requireSensorInfo: function () {
        internalSRCommand.requireSensorInfo();
    },
    resetSensor: function (data) {
        internalSRCommand.resetSensor(data);
    },
    updateLocalMotorState: function (inst) {
        internalSRCommand.updateLocalMotorState(inst);
    },
    updateRemoteMotorState: function (inst) {
        internalSRCommand.updateRemoteMotorState(inst);
    },
    updateRemoteDirect: function () {
        internalSRCommand.updateRemoteDirect();
    },
    registerCallback: function (name, func) {
        internalSRCommand.registerCallback(name, func);
    }
}

module.exports = _ret;
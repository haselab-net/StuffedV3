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
    setMotorDirect: function (data) {
        console.log("Set motor direct");
        internalSRCommand.setMotorDirect(data);
    },
    setMotorInterpolate: function (data) {
        console.log("Set motor interpolate");
        internalSRCommand.setMotorInterpolate(data);
    },
    setMotorParam: function (data) {
        internalSRCommand.setMotorParam(data);
    },
    resetSensor: function (data) {
        internalSRCommand.resetSensor(data);
    },
    registerCallback: function (name, func) {
        internalSRCommand.registerCallback(name, func);
    }
}

module.exports = _ret;
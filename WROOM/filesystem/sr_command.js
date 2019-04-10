var moduleSRCommand = ESP32.getNativeFunction("ModuleSRCommand");
if (moduleSRCommand === null) {
	log("Unable to find ModuleSRCommand");
	module.exports = null;
	return;
}

var internalSRCommand = {};
moduleSRCommand(internalSRCommand);

var _ret = {
    requireBoardInfo: function (data) {

    },
    requireSensorInfo: function (data) {

    },
    setMotorDirect: function (data) {
        console.log("set motor direct called");
        internalSRCommand.setMotorDirect(data);
    },
    setMotorInterpolate: function (data) {

    },
    setMotorParam: function (data) {

    },
    resetSensor: function (data) {

    }
}

module.exports = _ret;
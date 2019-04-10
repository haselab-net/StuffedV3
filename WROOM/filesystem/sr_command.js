var moduleSRCommand = ESP32.getNativeFunction("ModuleSRCommand");
if (moduleSRCommand === null) {
	log("Unable to find ModuleSRCommand");
	module.exports = null;
	return;
}

var internalSRCommand = {};
moduleSRCommand(internalSRCommand);

var _ret = {
    requireBoardInfo: function () {

    },
    requireSensorInfo: function () {

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

    },
    registerCallback: function (name, func) {
        console.log("register function: "+name);
        internalSRCommand.registerCallback(name, func);
    }
}

module.exports = _ret;
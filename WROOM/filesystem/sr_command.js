var moduleSRCommand = ESP32.getNativeFunction("ModuleSRCommand");
if (moduleSRCommand === null) {
	log("Unable to find ModuleSRCommand");
	module.exports = null;
	return;
}

var internalSRCommand = {};
moduleSRCommand(internalSRCommand);

var _ret = {
    setMotorDirect: function (data) {
        console.log("set motor direct called");
        internalSRCommand.setMotorDirect(data);
    }
}

module.exports = _ret;
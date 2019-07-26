var moduleSRMovement = ESP32.getNativeFunction("ModuleSRMovement");
if (moduleSRMovement === null) {
	log("Unable to find ModuleSRMovement");
	module.exports = null;
	exit;
}

var internalSRMovement = {};
moduleSRMovement(moduleSRMovement);

var _ret = {
    send: function (movData) {
        internalSRMovement.send(movData);
    }
}

module.exports = _ret;
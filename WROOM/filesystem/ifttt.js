/**
 * IFTTT module
 */

var moduleIFTTT = ESP32.getNativeFunction("ModuleIFTTT");
if (moduleIFTTT === null) {
	log("Unable to find ModuleIFTTT");
	module.exports = null;
	exit;
}

var internalIFTTT = {};
moduleIFTTT(internalIFTTT);

var _ret = {
    triggerEvent: function (key, event, value1, value2, value3) {
        internalIFTTT.triggerEvent(key, event, value1, value2, value3);
    },
    registerEvent: function (event, func) {
        internalIFTTT.registerEvent(event, func);
    },
    startWaitingEvent: function (remoteAddress, remotePort) {
        internalIFTTT.startWaitingEvent(remoteAddress, remotePort);
    },
    stopWaitingEvent: function () {
        internalIFTTT.stopWaitingEvent();
    }
}

module.exports = _ret
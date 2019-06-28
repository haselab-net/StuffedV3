/**
 * IFTTT module
 */

var moduleIoT = ESP32.getNativeFunction("ModuleIoT");
if (moduleIoT === null) {
	log("Unable to find ModuleIoT");
	module.exports = null;
	exit;
}

var internalIoT = {};
moduleIoT(internalIoT);

var _ret = {
    triggerIFTTTEvent: function (key, event, value1, value2, value3) {
        internalIoT.triggerIFTTTEvent(key, event, value1, value2, value3);
    },
    registerMQTTEvent: function (event, func) {
        internalIoT.registerMQTTEvent(event, func);
    },
    startWaitingMQTTEvent: function (remoteAddress, remotePort) {
        internalIoT.startWaitingMQTTEvent(remoteAddress, remotePort);
    },
    stopWaitingMQTTEvent: function () {
        internalIoT.stopWaitingMQTTEvent();
    }
}

module.exports = _ret
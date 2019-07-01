/**
 * IFTTT module
 */
var moduleIoT = ESP32.getNativeFunction("ModuleIoT");
if (moduleIoT === null) {
	log("Unable to find ModuleIoT");
}

var internalIoT = {};
moduleIoT(internalIoT);

var iot = {
    mqttCallbacks: {},

    // IFTTT
    triggerIFTTTEvent: function (key, event, value1, value2, value3) {
        internalIoT.triggerIFTTTEvent(key, event, value1, value2, value3);
    },

    // MQTT
    registerMQTTEvent: function (event, func) {
        console.log("register MQTT event: " + event);
        iot.mqttCallbacks[event] = func;
    },
    unregisterMQTTEvent: function(event) {
        if (iot.mqttCallbacks[event]) iot.mqttCallbacks[event] = undefined;
    },
    startWaitingMQTTEvent: function (remoteAddress, remotePort) {
        internalIoT.startWaitingMQTTEvent(remoteAddress, remotePort);
    },
    stopWaitingMQTTEvent: function () {
        internalIoT.stopWaitingMQTTEvent();
    },

    // register on start
    triggerMQTTEvent: function (event, value1, value2, value3) {
        console.log("receive MQTT event: " + event);
        if (iot.mqttCallbacks[event]) iot.mqttCallbacks[event](value1, value2, value3);
    },
    registerMQTTCallback: function (func) {
        internalIoT.registerMQTTCallback(func)
    }
}

iot.registerMQTTCallback(iot.triggerMQTTEvent);
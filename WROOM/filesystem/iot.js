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

    // Webhook
    triggerIFTTTEvent: function (key, event, value1, value2, value3) {
        const url = "http://maker.ifttt.com/trigger/" + event + "/with/key/" + key;
        const data = JSON.stringify({
            value1: value1,
            value2: value2,
            value3: value3
        });
        internalIoT.httpPost(url, data);
    },
    triggerNuibotEvent: function (nuibotId, event) {
        internalIoT.httpGet("http://haselab.net:5001/trigger/" + event + "/with/key/" + nuibotId);
    },
    triggerWebhook: function (params, url) {
        internalIoT.httpGet(url + "?" + params);
    },

    // MQTT
    registerMQTTEvent: function (event, func) {
        console.log("register MQTT event: " + event);
        iot.mqttCallbacks[event] = func;
    },
    unregisterMQTTEvent: function(event) {
        if (iot.mqttCallbacks[event]) iot.mqttCallbacks[event] = undefined;
    },
    startWaitingMQTTEventDefault: function() {
        internalIoT.startWaitingMQTTEventDefault();
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
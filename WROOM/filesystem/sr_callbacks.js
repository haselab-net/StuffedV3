
var ModuleCallbacks = ESP32.getNativeFunction("ModuleCallbacks");
if (ModuleCallbacks === null) {
	log("Unable to find ModuleCallbacks");
	exit;
}

var internalCallbacks = {};
ModuleCallbacks(internalCallbacks);

if (!softrobot.message_command.callbacks.touchQueryer) {
    softrobot.message_command.callbacks.touchQueryer = setInterval(function () {
        softrobot.message_command.requireSensorInfo();
    }, softrobot.message_command.callbacks.touchQueryerInterval);
}

var callbacks = {
    bindTouchCallback: function(touchSensorId, threshold, exceeds, callback) {
        internalCallbacks.bindTouchCallback(touchSensorId, threshold, exceeds, callback);
    },

    onStartTouch: function(touchSensorId, threshold, callback) {
        callbacks.bindTouchCallback(touchSensorId, threshold, false, callback);
    },

    onEndTouch: function(touchSensorId, threshold, callback) {
        callbacks.bindTouchCallback(touchSensorId, threshold, true, callback);
    }
}
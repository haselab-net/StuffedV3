var ModuleCallbacks = ESP32.getNativeFunction("ModuleCallbacks");
if (ModuleCallbacks === null) {
    log("Unable to find ModuleCallbacks");
	exit;
}

var internalCallbacks = {};
ModuleCallbacks(internalCallbacks);

// init queryer
var touchQueryerInterval = 200;
var touchQueryer = setInterval(function () {
    softrobot.message_command.requireSensorInfo();
}, touchQueryerInterval);

var callbacks = {
    onStartTouch: function(touchSensorId, threshold, callback) {
        internalCallbacks.bindTouchCallback(touchSensorId, threshold, false, callback);
    },

    onEndTouch: function(touchSensorId, threshold, callback) {
        internalCallbacks.bindTouchCallback(touchSensorId, threshold, true, callback);
    }
}

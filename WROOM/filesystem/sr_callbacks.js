
var ModuleCallbacks = ESP32.getNativeFunction("ModuleCallbacks");
if (ModuleCallbacks === null) {
    log("Unable to find ModuleCallbacks");
    module.exports = null;
	exit;
}

var internalCallbacks = {};
ModuleCallbacks(internalCallbacks);

// init queryer
var touchQueryerInterval = 500;
var touchQueryer = setInterval(function () {
    softrobot.message_command.requireSensorInfo();
}, softrobot.message_command.callbacks.touchQueryerInterval);;

var callbacks = {
    onStartTouch: function(touchSensorId, threshold, callback) {
        internalCallbacks.bindTouchCallback(touchSensorId, threshold, false, callback);
    },

    onEndTouch: function(touchSensorId, threshold, callback) {
        internalCallbacks.bindTouchCallback(touchSensorId, threshold, true, callback);
    }
}

module.exports = callbacks;
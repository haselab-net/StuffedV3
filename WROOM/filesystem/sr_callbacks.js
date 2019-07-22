// var softrobot = require("sr_softrobot");
var jslib = require("jslib");

var callbacks;
(function (callbacks) {
    var CallbacksMap = (function () {
        function CallbacksMap(keyGenerator) {
            this.funcs = {};
            this.keyGenerator = keyGenerator;
        }
        CallbacksMap.prototype.add = function (callback, keyOptions) {
            var key = this.keyGenerator(keyOptions);
            this.funcs[key] = callback;
            return key;
        };
        CallbacksMap.prototype.callFunc = function (keyOptions, args) {
            var key = this.keyGenerator(keyOptions);
            this.funcs[key]();
        };
        return CallbacksMap;
    }());
    callbacks.CallbacksMap = CallbacksMap;
    softrobot.message_command.callbacks.touchThresholdArray = [];
    if (!softrobot.message_command.callbacks.touchQueryer) {
        softrobot.message_command.callbacks.touchQueryer = setInterval(function () {
            jslib.printHeap("before require sensor info");
            softrobot.message_command.requireSensorInfo();
            jslib.printHeap("after require sensor info");
        }, softrobot.message_command.callbacks.touchQueryerInterval);
    }
    var touchSensorCallbacks = new CallbacksMap(function (keyOptions) {
        return keyOptions.sensorId * 2 + keyOptions.threshold * 100 + (keyOptions.exceed ? 1 : 0);
    });
    softrobot.message_command.callbacks.callTouchCallback = touchSensorCallbacks.callFunc.bind(touchSensorCallbacks);
    function bindTouchCallback(touchSensorId, threshold, exceeds, callback) {
        var option = {
            sensorId: touchSensorId,
            threshold: threshold,
            exceed: exceeds
        };
        var key = touchSensorCallbacks.add(callback, option);
        softrobot.message_command.callbacks.touchThresholdArray.push(option);
    }
    callbacks.bindTouchCallback = bindTouchCallback;
    function onStartTouch(touchSensorId, threshold, callback) {
        bindTouchCallback(touchSensorId, threshold, false, callback);
    }
    callbacks.onStartTouch = onStartTouch;
    function onEndTouch(touchSensorId, threshold, callback) {
        bindTouchCallback(touchSensorId, threshold, true, callback);
    }
    callbacks.onEndTouch = onEndTouch;
})(callbacks || (callbacks = {}));

// module.exports = callbacks;
/**
 * JSLib module
 */

 var jf = require("jsfile")
 var sr = require("softrobot")

var moduleJSLib = ESP32.getNativeFunction("ModuleJSLib");
if (moduleJSLib === null) {
	log("Unable to find ModuleJSLib");
	module.exports = null;
	return;
}

var internalJSLib = {};
moduleJSLib(internalJSLib);

var _ret = {
    loops: _loops
}

var _core = {
    blockPause: function(ms) {
        internalJSLib.block_pause(ms);
    },

    registerCallback: function(func) {
        internalJSLib.register_callback(func);
    },

    sendCommand: function(arrayBuffer) {
        internalJSLib.send_command(arrayBuffer);
    },

    handleEvent: function() {
        internalJSLib.handleEvent();
    }
}

var _loops = {
    pause: function (ms) {
        if(ms<=0) return;

        var start_time = (new Date).getMilliseconds();
        while((new Date).getMilliseconds()-start_time<ms) {
            _core.handleEvent();
        }
    },

    forever: function (func) {
        while(1) {
            func();
            _core.handleEvent();
        }
    }
}

module.exports = _ret;
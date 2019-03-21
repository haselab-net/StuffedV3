/**
 * JSLib module
 */

 var jf = import("jsfile")
 var sr = import("softrobot")

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
    } 
}

var _loops = {
    pause: function (ms) {
        if(ms<=0) return;

        var start_time = (new Date).getMilliseconds();
        while((new Date).getMilliseconds()-start_time<ms) {
            jf.handleEvent();
        }
    },

    forever: function (func) {
        while(1) {
            func();
            jf.handleEvent();
        }
    }
}

module.exports = _ret;
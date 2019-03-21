/**
 * JSFile module
 */

var moduleJSFile = ESP32.getNativeFunction("ModuleJSFile");
if (moduleJSFile === null) {
	log("Unable to find ModuleJSFile");
	module.exports = null;
	return;
}

var internalJSFile = {};
moduleJSFile(internalJSFile);

var _ret = {
    stopFile: function () {
        internalJSFile.stop_file();
    },

    runFile: function (fileName) {
        internalJSFile.run_file(fileName);
    },

    handleEvent: function() {
        internalJSFile.handle_event();
    }
}

module.exports = _ret;
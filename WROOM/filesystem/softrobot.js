/*
 * Softrobot module.
 */

var moduleSoftrobot = ESP32.getNativeFunction("ModuleSoftrobot");
if (moduleSoftrobot === null) {
	log("Unable to find ModuleSoftrobot");
	module.exports = null;
	return;
}

var internalSoftrobot = {};
moduleSoftrobot(internalSoftrobot);

var _ret = {

    handlePacket: function(buffer) {                // buffer is an ArrayBuffer object
        internalSoftrobot.handle_packet(buffer);
    },

    registerCallback: function(callback) {          // callback is a function with one parameter: ArrayBuffer
        internalSoftrobot.register_callback(callback);
    }
}
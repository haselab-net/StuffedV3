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
    },

    logCommand: function(buffer) {                  // log the content of command packet
        var int16Array;
        if(buffer instanceof ArrayBuffer) int16Array = new Int16Array(buffer)
        else if (buffer instanceof Int16Array) int16Array = buffer;
        else return;
        log("- length: " + int16Array[0]);
        log("- commandId: " + int16Array[1]);
        var num_array = [];
        for(var i=0; i<int16Array[0]/2-2; i++) {
            num_array.push(int16Array[2+i]);
        }
        log("- numArray: " + num_array);
    },

    ab2str: function(arrayBuffer) {
        return String.fromCharCode.apply(null, new Uint16Array(arrayBuffer))
    },

    wsConnection: null
}

module.exports = _ret;
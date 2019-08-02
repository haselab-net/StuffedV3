/* globals Duktape, log, DUKF, require */
// init only once when first initialize heap

StringUtils = {
	endsWith: function(subjectString, searchString, position) {
      if (typeof position !== 'number' || !isFinite(position) || Math.floor(position) !== position || position > subjectString.length) {
        position = subjectString.length;
      }
      position -= searchString.length;
      var lastIndex = subjectString.lastIndexOf(searchString, position);
      return lastIndex !== -1 && lastIndex === position;		
	},
	startsWith: function(subjectString, searchString, position) {
		position = position || 0;
		return subjectString.substr(position, searchString.length) === searchString;
	}
};

Duktape.modSearch = function(id, require, exports, module) {
	DUKF.gc();
	log("Module: require(\"" + id + "\") loading \"" + id + "\"");
	var name = id;
	if (!StringUtils.endsWith(id, ".js")) {
		name += ".js";
	}
	/*
	if (!id.endsWith(".js")) {
		name += ".js";
	}
	*/
	module.filename = name;
	var dir = ESP32.NetVFSDir;
	if(dir && name.slice(0,dir.length+1) == dir + '/')
		return ESP32.loadFile('/' + name);
	return DUKF.loadFile(name);
	//var data = DUKF.loadFile(name);
	//log(data);
	//return data;
}; // Duktape.modSearch

/*
var _timers = {
	setTimer: function(callback, interval, isInterval) {
		var id = ESP32.registerTimerCallback(callback, interval, isInterval);
		if (id == 0){
			log("Failed to add a new timer for " + callback);
		}else{
			log("Added a new timer " + id + " interval " + interval + " for " + callback);
		}
		return id;
	},
	cancelTimer: function(id) {	//	success = true  fail = false
		var rv = ESP32.cancelTimerCallback(id);
		if (rv){
			log("Failed to cancel a timer " + id);
		}else{
			log("cancel a timer " + id);
		}
		return rv;
	} // cancelTimer
};
*/
function cancelInterval(id) {
	ESP32.cancelTimerCallback(id);
}

function cancelTimeout(id) {
	ESP32.cancelTimerCallback(id);
}

function setInterval(callback, interval) {
	return ESP32.registerTimerCallback(callback, interval, true);
}

function setTimeout(callback, interval) {
	return ESP32.registerTimerCallback(callback, interval, false);
}

var jslib = require("jslib");
jslib.printHeap("<< after jslib");
var loops = require("sr_loops");
jslib.printHeap("<< after sr_loops");
var console = require("console");
jslib.printHeap("<< after console");

ESP32.include("iot.js");
jslib.printHeap("<< after iot");
ESP32.include("sr_softrobot.js");
jslib.printHeap("<< after sr_softrobot");
ESP32.include("sr_motor.js");
jslib.printHeap("<< after sr_motor");
ESP32.include("sr_callbacks.js");
jslib.printHeap("<< after sr_callbacks");

jslib.printHeap("heap size after require: ");

// init board
softrobot.message_command.requireBoardInfo();

/* globals Duktape, log, DUKF, require */
/* exported _sockets, cancelInterval, cancelTimeout, setInterval, setTimeout, _loop */

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
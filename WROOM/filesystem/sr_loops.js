var jslib = require("jslib");

var _ret = {
    pause: function (ms) {
        if(ms<=0) return;

        console.log("pause for " + ms + " ms");

        var start_time = Date.now();
        while(Date.now()-start_time<ms) {
            jslib.handleEvent();
        }
    },

    forever: function (func) {
        while(1) {
            func();
            jslib.handleEvent();
        }
    }
}

module.exports = _ret;
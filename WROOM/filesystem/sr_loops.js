var jslib = require("jslib");

var loops = {
    pause: function (ms) {
        if(ms<=0) return;

        console.log("pause for " + ms + " ms");

        var start_time = Date.now();
        while(Date.now()-start_time<ms) {
            jslib.handleEvent();
        }
    },

    forever: function (func) {
        loops._foreverFunc = func;
    },

    _foreverFunc: function() {
        console.log("default forever");
        jslib.blockPause(1000);
    },

    doForever: function () {
        while(1) {
            loops._foreverFunc();
            jslib.handleEvent();
        }
    }
}

module.exports = loops;
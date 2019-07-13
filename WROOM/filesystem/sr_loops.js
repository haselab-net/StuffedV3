var jslib = require("jslib");

var loops = {
    pause: function (ms) {
        if(ms<=0) return;
        console.log("pause for " + ms + " ms");
        jslib.blockPause(ms);
    },

    forever: function (func) {
        loops._foreverFunc = func;
        loops.doForever = function () {
            while(1) {
                loops._foreverFunc();
                loops.pause(1000);
            }
        }
    },

    _foreverFunc: function() {
        console.log("default forever");
        jslib.blockPause(10000);
    },

    doForever: function () {
        while(1) {
            loops._foreverFunc();
            loops.pause(1000);
        }
    }
}

module.exports = loops;

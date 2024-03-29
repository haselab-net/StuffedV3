jslib.printHeap("sr_loop.js:1");
var jslib = require("jslib");
jslib.printHeap("sr_loop.js:3");

var loops = {
    pause: function (ms) {
        if(ms<=0) return;
        jslib.printHeap("pause for " + ms + " ms");
        jslib.blockPause(ms);
    },

    forever: function (func) {
        loops._foreverFunc = func;
    },

    _foreverFunc: function() {
        jslib.printHeap("default forever");
        jslib.blockPause(1000);
    },

    doForever: function () {
        loops._foreverFunc();
        jslib.pushEventQueue(loops.doForever);
    }
}

module.exports = loops;
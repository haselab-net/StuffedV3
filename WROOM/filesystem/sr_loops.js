var jslib = require("jslib");

var loops = {
    pause: function (ms) {
        if(ms<=0) return;

        console.log("pause for " + ms + " ms");

        var start_time = Date.now();
        while(Date.now()-start_time<ms) {
            // handle event
            var busy = jslib.handleEvent();

            // End of check timers.
            if (_timers.timerEntries.length > 0 && new Date().getTime() >= _timers.timerEntries[0].fire ) {
                //log("Processing timer fired for id: " + _timers.timerEntries[0].id);
                var timerCallback = _timers.timerEntries[0].callback;
                if (_timers.timerEntries[0].interval > 0) {
                    _timers.timerEntries[0].fire = new Date().getTime() + _timers.timerEntries[0].interval;
                    _timers.sort();
                } else {
                    _timers.timerEntries.splice(0, 1);
                }
                timerCallback();
                busy = true;
            }
            if (!busy){
                if (_timers.timerEntries.length > 0 && new Date().getTime() < _timers.timerEntries[0].fire - 10) {
                    jslib.blockPause(10);
                }
            }
        }
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

var loops = require("sr_loops");

console.log("1");

loops.forever(function () {
    loops.pause(100)
    loops.pause(100)
    loops.pause(100)
    loops.pause(100)
})

console.log("2");

loops.doForever();
console.log("test called.");
var c = console;
c.log("c.log from test.js");
module.exports=c;

console.log("this = " + JSON.stringify(this));
console.log("module = " + JSON.stringify(module));
console.log("module.exports = " + JSON.stringify(module.exports));
function getGlobal() {
    return new Function('return this')();
}
console.log("global = " + JSON.stringify(getGlobal()));

// for (var i=0; i<1; i++) {
//     ifttt.triggerEvent("Mf0JcCX_5FLZiz6Svtpjn", "esp_event", "", "", "");
//     jslib.blockPause(1000);
// }

iot.registerMQTTEvent("hello", function (value1, value2, value3) {
    console.log("Hello called")
    console.log(value1)
    console.log(value2)
    console.log(value3)
})
iot.startWaitingMQTTEvent("192.168.2.51", 5000)

jslib.print("Initial default main.js is called.");

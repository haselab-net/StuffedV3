(function(){
    var rootPath = "/spiffs";

    var programPath = [
        "/main/maininit.js",
        "/main/main.js",
        "/main/mainend.js",
    ];

    var script = DUKF.loadFile(programPath[1]);

    if(script) console.log(script);

    //if(script) eval(script);
})();


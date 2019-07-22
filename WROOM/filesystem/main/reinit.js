// reinit global variables
// called every time restart duktape task

// NOTE please clear the event queue before call this file

////////////////////////////////////// reset data set by user //////////////////////////
// reset forever to default function
loops.doForever = function () {
    console.log("default forever");
    jslib.blockPause(1000);
};

// clear registered touch sensor callbacks
softrobot.message_command.callbacks.touchThresholdArray = [];
touchSensorCallbacks.funcs = {};

// softrobot.movement.sendKeyframeQueue.clear();

// iot.stopWaitingMQTTEvent();

////////////////////////////////////// reset hardware //////////////////////////

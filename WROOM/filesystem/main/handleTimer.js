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
}
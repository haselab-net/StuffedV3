#pragma once

#include <vector>

class MonitorCommandBase{
public:
    MonitorCommandBase();
    virtual void Func()=0;
    virtual const char* Desc()=0;
};

class Monitor{
public:
    static Monitor theMonitor;
    std::vector<MonitorCommandBase*> commands;
    void AddCommand(MonitorCommandBase*);
    void Run();
    void ShowList();
};

void monitor();

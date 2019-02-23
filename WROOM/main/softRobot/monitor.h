#pragma once
class MonitorCommandBase{
public:
    MonitorCommandBase();
    virtual void Func()=0;
    virtual const char* Desc()=0;
};

class Monitor{
public:
    static Monitor theMonitor;
    tiny::vector<MonitorCommandBase*> commands;
    void AddCommand(MonitorCommandBase*);
    void Run();
    void ShowList();
};

void monitor();

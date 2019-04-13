#pragma once

#include <vector>

class MonitorCommandBase{
public:
    static const char* Tag();
    MonitorCommandBase();
    virtual void Func()=0;
    virtual const char* Desc()=0;
};

class Monitor{
public:
    static Monitor theMonitor;
    std::vector<MonitorCommandBase*> commands;
    //  call before Init();
    void AddCommand(MonitorCommandBase*);
    void ShowList();

    //  call from main
    void Init();
    void Run();
};


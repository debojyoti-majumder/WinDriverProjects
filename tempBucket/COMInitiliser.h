#pragma once

#include <iostream>
#include <windows.h>

using namespace std;

class COMInitiliser {
private:
    static COMInitiliser *instance;
    static LONG refCount;

    // Private constructor so that no objects can be created.
    COMInitiliser();
    ~COMInitiliser();

public:
    static COMInitiliser *getInstance();
    void relase();
};

#pragma once

#include "pch.h"

#include <vector>
#include <string>
#include <functional>
#include <map>

using namespace std;

class CommandLineParser
{
    private:
        vector<wstring> _commandLineParameters;
        
    public:
        CommandLineParser(int argc, LPTSTR argv[]);
        void AddOption();
        void Parse();
        ~CommandLineParser();
};
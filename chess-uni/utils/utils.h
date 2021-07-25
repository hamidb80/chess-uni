#pragma once
#include<string>
using namespace std;
using namespace System;

string toStdString(String^ s) {
    using namespace Runtime::InteropServices;
    const char* chars =
        (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
 
    return chars;
}

template <class T>
T selfGet(T s) {
    return s;
}

public ref struct MyFileInfo {
    String^ name;
    String^ path;
};
#pragma once

#include <string>

using namespace std;
using namespace System;

int freakin_random_number(int from = 0, int to=10000) {
    Random^ rnd = gcnew Random();
    return rnd->Next(from, to);
}

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
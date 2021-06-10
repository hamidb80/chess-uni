#pragma once

#include <string>
#include <map>
using namespace std;


class EventHandler {
#define EventFunc(NAME) void(NAME)(string data) 

private:
	map<string, EventFunc(*, string)> eventEntries;

public:
	void add(string eventName, EventFunc(fn)) {
		eventEntries.insert(
			pair<string, void(*)(string data)>(eventName, fn)
		);
	}
	void trigger(string eventName, string data) {
		map<string, EventFunc(*)>::iterator it = eventEntries.find("");

		if (it != eventEntries.end())
			it->second(data);
		else
			throw ("event '" + eventName + "' not found");
	}
};
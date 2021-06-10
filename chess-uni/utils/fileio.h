#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

inline string readFile(string path)
{
	string res;
	ifstream inf(path, ios::binary);

	if (!inf.is_open())
		throw "err";

	char byte = 0;
	while (inf.get(byte))
		res += byte;

	inf.close();
	return res;
}

inline void writeFile(string path, string content)
{
	auto outf = ofstream(path, ios::binary);

	if (!outf.is_open())
		throw "err";

	for (int i = 0; i < content.length(); i++)
		outf << content[i];

	outf.close();
}
inline void copyFile(string sourcePath, string targetPath)
{
	writeFile(targetPath, readFile(sourcePath));
}

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <Windows.h>

#ifndef LOGGER_H
#define LOGGER_H

using namespace std;

class Logger
{
private:
	char logType;
	ofstream outFile;
	string fileName;
	string folderName;
	SYSTEMTIME time;
	int _logNum = 1;

	void writeToFile(string MsgType, string Msg);

public:
	void createFile(char LType, string FolName);
	void _err(string Msg);
	void _sLog(string Msg);
	void _info(string Msg);
};

#endif // !LOGGER_H
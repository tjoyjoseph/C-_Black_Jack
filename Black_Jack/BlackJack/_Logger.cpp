#include "Logger.h"

///Writes the text in the parameters to the specified file
void Logger::writeToFile(string MsgType, string Msg)
{
	clog << MsgType << "      " << Msg << endl;
	GetLocalTime(&time); ///For including time
	ostringstream cTime;
	cTime << time.wHour << "." << time.wMinute << "." << time.wSecond << "." << time.wMilliseconds;
	outFile.open(folderName + "\\" + fileName + ".txt", ofstream::app);
	outFile << _logNum<<"\t|   "<<cTime.str() << "\t|   " << MsgType << "  |   " << Msg << endl;
	outFile.close();
	_logNum++;
}

///Sets up the folder and the file for logging
void Logger::createFile(char LType, string FolName)
{
	///Only sets up folder and file if logging is turned on
	if ((LType == 'd') || (LType == 'e') || (LType == 'a') || (LType == 'i'))
	{
		folderName = FolName;
		string path = folderName;
		wstring stemp = wstring(path.begin(), path.end());
		LPCWSTR sw = stemp.c_str();
		if (CreateDirectory(sw, NULL))
		{
#ifdef _DEBUG
			clog << "Folder has been created." << endl;
#endif 
		}
		else if (ERROR_ALREADY_EXISTS == GetLastError())
		{
#ifdef _DEBUG
			clog << "ERROR: This folder already exists" << endl;
#endif
		}
		GetLocalTime(&time);
		ostringstream cTime;
		cTime << time.wHour << "." << time.wMinute << "." << time.wSecond;
		fileName = cTime.str() + "_" + folderName;
		outFile.open( folderName + "\\" + fileName + ".txt");
		outFile << "Index\t\tTime\t\t  Log Type\tComments " << endl;
		outFile.close();

		logType = LType;
	}
	///Displays logging mode for testing purposes
	switch (logType)
	{
	case 'a':
#ifdef _DEBUG
		clog << "ALL LOGGING MODE ACTIVATED " << endl;
#endif
		break;
	case 'd':
#ifdef _DEBUG
		clog << "DEBUGGING MODE ACTIVATED" << endl;
#endif
		break;
	case 'i':
#ifdef _DEBUG
		clog << "INFO MODE ACTIVATED" << endl;
#endif
		break;
	case 'e':
#ifdef _DEBUG
		clog << "ERROR MODE ACTIVATED" << endl;
#endif
		break;
	default:
#ifdef _DEBUG
		clog << "NO LOGGING MODE ACTIVATED" << endl;
#endif
	}
}

//For logging errors
void Logger::_err(string Msg)
{
	if ((logType == 'e') || (logType == 'a'))
		writeToFile("ERROR", Msg);
}

///For logging debugging information
void Logger::_sLog(string Msg)
{
	if ((logType == 'd') || (logType == 'a'))
		writeToFile("DEBUG", Msg);
}

///for logging additional information
void Logger::_info(string Msg)
{
	if ((logType == 'i') || (logType == 'a'))
		writeToFile("INFO ", Msg);
}
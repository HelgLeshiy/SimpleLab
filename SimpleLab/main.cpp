#include "app.h"
#include <fstream>
#include <ctime>

char format[] = "[%d/%m/%y %T]";

std::string getDataTimeStr()
{
	time_t seconds = time(nullptr);
	tm timeinfo;
	localtime_s(&timeinfo, &seconds);
	char buffer[80];
	strftime(buffer, 80, format, &timeinfo);

	return buffer;
}

int main( int argc, char **argv )
{
	int rc;
	std::ofstream logStream("log.txt", std::ios::app);
	
	logStream << getDataTimeStr() << " Starting app...\n";
	try
	{
		app theApp;
		rc = theApp.execute();
	}
	catch (std::exception& ex)
	{
		logStream << getDataTimeStr() << " Error: " << ex.what() << "\n";
		rc = 1;
	}
	logStream << getDataTimeStr() << " Exiting app with code " << rc << "\n\n";
	return rc;
}
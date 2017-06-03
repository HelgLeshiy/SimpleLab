#include "app.h"

int main( int argc, char **argv )
{
	int rc;
	try
	{
		app theApp;
		rc = theApp.execute();
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what();
		rc = 1;
	}

	return rc;
}
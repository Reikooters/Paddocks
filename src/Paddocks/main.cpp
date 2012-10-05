/*************************************************************************
 Paddocks
 by Shane "Reiko" Swenson - October 2012.

 Computer version of the pen and paper game, 'Paddocks' also known as
 'Dots and Boxes'.
	
 https://github.com/Reikooters/Paddocks
**************************************************************************
 main.cpp
**************************************************************************
 Contains the entry point of the program.
**************************************************************************/
#include "Application.h"

int main (int argc, char **argv)
{
	std::auto_ptr<Application> app(new Application());

	int result = app->go();

	return result;
}

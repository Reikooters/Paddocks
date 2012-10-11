/*************************************************************************
 * Paddocks
 * by Shane "Reiko" Swenson - October 2012.
 * 
 * Computer version of the pen and paper game, 'Paddocks' also known as
 * 'Dots and Boxes'.
 * 	
 * https://github.com/Reikooters/Paddocks
 *************************************************************************
 * ConfigIni.cpp
 *************************************************************************
 * This file contains the definitions for the functions declared in the
 * ConfigIni class. See ConfigIni.cpp for details on this class.
 *************************************************************************/
#include "ConfigIni.h"


/*************************************************************************
 * ConfigIni::ConfigIni
 *************************************************************************
 * Constructor. The filename given should be the name of the config file.
 * For example, "config.ini".
 *************************************************************************/
ConfigIni::ConfigIni(Ogre::String &filename)
{
	configFile.load(filename);
}


/*************************************************************************
 * ConfigIni::getConfig
 *************************************************************************
 * Returns a copy of the Ogre::ConfigFile.
 *************************************************************************/
inline ConfigIni::Configurations ConfigIni::getConfig()
{
	return configurations;
}

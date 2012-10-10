/*************************************************************************
 * Paddocks
 * by Shane "Reiko" Swenson - October 2012.
 * 
 * Computer version of the pen and paper game, 'Paddocks' also known as
 * 'Dots and Boxes'.
 * 	
 * https://github.com/Reikooters/Paddocks
 *************************************************************************
 * ConfigIni.h
 *************************************************************************/

/*************************************************************************
 * class ConfigIni
 *************************************************************************
 * This class contains functions related to config.ini operations. Such
 * as changing values, validating them and so on. It uses an
 * Ogre::ConfigFile for reading in the .ini file, which makes some of the
 * work easier.
 *************************************************************************/
class ConfigIni
{
	Ogre::String filename;
	Ogre::ConfigFile configFile;

	// Configurations
	bool fullscreen;
	Ogre::String fsaa;
	Ogre::String width;
	Ogre::String height;
	int shadows;

	// Functions
	void validate();

public:
	ConfigIni(Ogre::String &filename);
	Ogre::ConfigFile getConfig();

	// Writes the config back to the file.
	void save();
};

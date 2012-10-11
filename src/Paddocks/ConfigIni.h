#pragma once
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
	
	// Struct which stores configuration settings.
	struct Configurations
	{
		bool fullscreen;
		int fsaa;
		int width;
		int height;
		int shadows;
	} configurations;

	// Enumator containing the types of settings.
	enum Setting
	{
		SETTING_FSAA,
		SETTING_FULLSCREEN,
		SETTING_SHADOWS,
		SETTING_WIDTH,
		SETTING_HEIGHT,

		SETTINGS_TOTAL // must always be last
	};

	/* Takes the data from the Ogre::ConfigFile and puts it into the
	 * 'confurations' struct. */
	void grabConfigsFromConfigFile();

	// Sets configuration settings back to default.
	void resetConfigsToDefault();

public:
	// Constructor
	ConfigIni(Ogre::String &filename);

	// Returns the configuration settings.
	Configurations getConfigs();

	// Change a setting
	void setSetting(Setting setting, Ogre::String &newValue);

	// Writes the config back to the file.
	void save();
};

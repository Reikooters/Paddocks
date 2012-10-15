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
public:
	// Struct which stores configuration settings.
	struct Configurations
	{
		bool fullscreen;
		int fsaa;
		int shadows;
		Ogre::Vector2 resolution;

		Configurations()
			: fullscreen(CONFIG_DEFAULT_FULLSCREEN), fsaa(CONFIG_DEFAULT_FSAA),
			shadows(CONFIG_DEFAULT_SHADOWS),
			resolution(CONFIG_DEFAULT_WIDTH, CONFIG_DEFAULT_HEIGHT)
		{ }
	};

	// Enumator containing the types of settings.
	enum Setting
	{
		SETTING_FULLSCREEN,
		SETTING_FSAA,
		SETTING_SHADOWS,
		SETTING_RESOLUTION,

		SETTINGS_TOTAL // must always be last
	};

private:
	Ogre::String filename;
	Ogre::ConfigFile configFile;
	Configurations configurations;

	/* Takes the data from the Ogre::ConfigFile and puts it into the
	 * 'confurations' struct. */
	void grabConfigsFromConfigFile();

	// Sets configuration settings back to default.
	void resetConfigsToDefault();

public:
	// Constructor
	ConfigIni(const Ogre::String &filename);

	// Returns the configuration settings.
	Configurations getConfigs() const;

	/* Change a setting.
	 * If the given value is invalid for the setting, the setting will
	 * be reset to default. */
	void setSetting(const Setting setting, const Ogre::String &newValue);

	// Writes the config back to the file.
	void save() const;
};


/*************************************************************************
 * ConfigIni::getConfig()
 *************************************************************************
 * Returns the configuration settings.
 *************************************************************************/
inline ConfigIni::Configurations ConfigIni::getConfigs() const
{
	return configurations;
}

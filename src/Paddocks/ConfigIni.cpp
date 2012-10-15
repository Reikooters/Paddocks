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
 * ConfigIni::ConfigIni()
 *************************************************************************
 * Constructor. The filename given should be the name of the config file.
 * For example, "config.ini".
 *************************************************************************/
ConfigIni::ConfigIni(const Ogre::String &filename)
	: filename(filename)
{
	/* First, we will check to see whether the file can be opened.
	 * ie. file exists, have permission, etc. */
	std::ifstream file(filename);

	// If file can be opened
	if (file.is_open())
	{
		// If file is readable
		if (file.good())
		{
			// Close the file
			file.close();

			// If file exists, load the file.
			configFile.load(filename);
		}
		// If file is not readable
		else
		{
			// Close the file
			file.close();

			/* If file can be opened but is unreadable, we will just
			 * use the default settings. */
			resetConfigsToDefault();
		}
	}
	// If file cannot be opened
	else
	{
		/* If no configuration file exists, we will just use the
		 * default settings. */
		resetConfigsToDefault();
	}

	// Put the settings into the 'configurations' struct.
	grabConfigsFromConfigFile();

	// Overwrite the file with valid configuration settings.
	save();
}


/*************************************************************************
 * ConfigIni::resetConfigsToDefault()
 *************************************************************************
 * Resets configurations to default.
 *************************************************************************/
inline void ConfigIni::resetConfigsToDefault()
{
	// Defaults can be changed in CompileSettings.h
	configurations.fsaa =			CONFIG_DEFAULT_FSAA;
	configurations.shadows =		CONFIG_DEFAULT_SHADOWS;
	configurations.fullscreen =		CONFIG_DEFAULT_FULLSCREEN;
	configurations.resolution =		Ogre::Vector2(CONFIG_DEFAULT_WIDTH, CONFIG_DEFAULT_HEIGHT);
}


/*************************************************************************
 * ConfigIni::resetConfigsToDefault()
 *************************************************************************
 * Grabs the configurations from the Ogre::ConfigFile, validates them,
 * and then puts them into the configurations struct. Invalid values will
 * be set to defaults.
 *************************************************************************/
void ConfigIni::grabConfigsFromConfigFile()
{
	/* First, we will make a list of all the settings we want to take
	 * from the file, which we will iterate through and pull each one
	 * out. */

	/* Typedef for a pair of two Ogre::Strings. */
	typedef std::pair<Ogre::String, Ogre::String> twoStrings;

	/* We will store this list in a std::vector of pairs of strings.
	 * The first string will be the setting name, the second string
	 * will be the value retrieved from the config file. */
	std::vector<twoStrings> settings;
	settings.reserve(SETTINGS_TOTAL);

	/* Add the list of settings we are looking for to the vector.
	 * These must be added in the order they appear in the Setting
	 * enumerator (ConfigIni.h). After this though, there is no strict
	 * order. */
	settings.push_back( twoStrings("fullscreen", "") );
	settings.push_back( twoStrings("fsaa", "") );
	settings.push_back( twoStrings("shadows", "") );
	settings.push_back( twoStrings("resolution", "") );

	/* Pull all the values out and put them into the vector's second
	 * strings. */
	for (std::vector<twoStrings>::iterator it = settings.begin(); it != settings.end(); ++it)
		it->second = configFile.getSetting(it->first);

	/* Parse each setting. Setting will be set to default if it cannot
	 * be parsed correctly. eg. if a true/false value is set to 'blah',
	 * then the setting will be set to default and the value retrieved
	 * from the file will be ignored. */
	setSetting(SETTING_FULLSCREEN, settings[SETTING_FULLSCREEN].second);
	setSetting(SETTING_FSAA, settings[SETTING_FSAA].second);
	setSetting(SETTING_SHADOWS, settings[SETTING_SHADOWS].second);
	setSetting(SETTING_RESOLUTION, settings[SETTING_RESOLUTION].second);

	/* Now we check that each setting is valid. For example, lets say a
	 * setting that uses an integer value has valid values of 0, 1 or 2.
	 * If the value obtained from the file was 91234, then the default
	 * value should be used instead. True/false values don't need to be
	 * checked, as enough validation would have been done for them above
	 * already, since there are exactly two possible values always. */

}


/*************************************************************************
 * ConfigIni::save()
 *************************************************************************
 * Overwrites the loaded config file with the settings that are currently
 * in memory.
 *************************************************************************/
void ConfigIni::save() const
{
	// Open file for writing.
	std::ofstream file(filename);

	/* If file can be written, we write the file, else we just do
	 * nothing. */
	if (file.is_open())
	{
		// Full Screen
		file << "fullscreen=";
		if (configurations.fullscreen)
			file << "true";
		else
			file << "false";
		file << std::endl;

		// Anti-aliasing
		file << "fsaa=" << configurations.fsaa << std::endl;

		// Shadows
		file << "shadows=" << configurations.shadows << std::endl;
		
		// Resolution
		file << "resolution=" << configurations.resolution.x << " " <<
			configurations.resolution.y << std::endl;

		// Done writing, so close the file.
		file.close();
	}
}

/*************************************************************************
 * ConfigIni::setSetting()
 *************************************************************************
 * Public function for changing the stored settings. If the new value
 * for the given setting is invalid, the setting will be returned to its
 * default value.
 *
 * For each setting:
 *
 * Step 1:
 * Parse each setting. Setting will be set to default if it cannot
 * be parsed correctly. eg. if a true/false value is set to 'blah',
 * then the setting will be set to default and the value retrieved
 * from the file will be ignored.
 *
 * Step 2:
 * Check that each setting is valid. For example, lets say a setting that
 * uses an integer value has valid values of 0, 1 or 2. If the value
 * obtained from the file was 91234, then the default value should be
 * used instead. True/false values don't need to be checked, as enough
 * validation would have been done for them above already, since there
 * are exactly two possible values always.
 *
 * Note: save() should be called afterward to write the changes back
 * to the file.
 *************************************************************************/
void ConfigIni::setSetting(const Setting setting, const Ogre::String &newValue)
{
	if (setting >= 0 && setting < SETTINGS_TOTAL)
	{
		switch (setting)
		{
		// Full Screen
		case SETTING_FULLSCREEN:
			configurations.fullscreen = Ogre::StringConverter::parseBool(newValue, CONFIG_DEFAULT_FULLSCREEN);
			break;

		// Anti-aliasing
		case SETTING_FSAA:
			configurations.fsaa = Ogre::StringConverter::parseInt(newValue, CONFIG_DEFAULT_FSAA);

			// Validate
			switch (configurations.fsaa)
			{
			case 0:
			case 2:
			case 4:
			case 8:
				break;
			default:
				configurations.fsaa = CONFIG_DEFAULT_FSAA;
			}
			break;

		// Shadows
		case SETTING_SHADOWS:
			configurations.shadows = Ogre::StringConverter::parseInt(newValue, CONFIG_DEFAULT_SHADOWS);

			// Validate
			switch (configurations.shadows)
			{
			case 0:
			case 1:
			case 2:
				break;
			default:
				configurations.shadows = CONFIG_DEFAULT_SHADOWS;
			}
			break;

		// Resolution
		case SETTING_RESOLUTION:
			configurations.resolution = Ogre::StringConverter::parseVector2(newValue, Ogre::Vector2(CONFIG_DEFAULT_WIDTH, CONFIG_DEFAULT_HEIGHT));

			// TODO: Resolution validation.
			break;
		}
	}
}

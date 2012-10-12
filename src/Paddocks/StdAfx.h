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
 * StdAfx.h
 *************************************************************************
 * This file is part of the pre-compiled header. It includes headers that
 * we want accessible from all other files in the project. This file is
 * forcibly included into every other file through the project settings.
 *************************************************************************/
// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning (disable : 4251)

// Ogre headers needed
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreRenderSystem.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreUTFString.h>
 
// Windows specific headers
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	#define WIN32_LEAN_AND_MEAN
	#include "windows.h"

	// MSVC specific headers
	#if _MSC_VER
		// direct.h used for chrdir()
		#include <direct.h>

		// Visual Leak Detector
		#include <vld.h>
	#endif
#endif

// Non-MSVC stuff
#ifndef _MSC_VER
	// unistd.h used for chdir() on other compilers/platforms
	#include <unistd.h>
#endif

// Standard c++ headers
#include <cstdlib>
#include <memory>
#include <exception>

// Paddocks headers
#include "CompileSettings.h"

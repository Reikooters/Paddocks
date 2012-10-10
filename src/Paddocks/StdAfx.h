// stdafx.h
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
 
// any other header can be included, as usual
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <vld.h>
#endif

#include <cstdlib>
#include <memory>
#include <exception>

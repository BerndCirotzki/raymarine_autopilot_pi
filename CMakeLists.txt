##---------------------------------------------------------------------------
## Author:      Dipl. Ing. Bernd Cirotzki
## Copyright:
##---------------------------------------------------------------------------

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(autopilot_pi)

SET(PACKAGE_NAME autopilot_pi)
SET(VERBOSE_NAME autopilot)
SET(TITLE_NAME autopilot)
SET(CPACK_PACKAGE_CONTACT "Bernd Cirotzki")

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")

#SET(CMAKE_BUILD_TYPE Debug)
SET( wxWidgets_USE_DEBUG OFF)
SET( wxWidgets_USE_UNICODE ON)
SET( wxWidgets_USE_UNIVERSAL OFF)
SET( wxWidgets_USE_STATIC OFF)

INCLUDE("cmake/PluginConfigure.cmake")

SET(SRC_autopilot
        src/autopilot_pi.h
        src/autopilot_pi.cpp
        src/icons.h
        src/icons.cpp
	    src/autopilotgui.h
	    src/autopilotgui.cpp
	    src/autopilotgui_impl.cpp
	    src/autopilotgui_impl.h
	    src/ocpn_plugin.h
	)


ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_autopilot})

ADD_DEFINITIONS(-DTIXML_USE_STL)

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")

cmake_minimum_required(VERSION 3.13)

project( WarrenCustomLibs LANGUAGES CXX)

set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmakeModules)

set( BuiltSharedLibsDir "builtShared" )
set( BuiltStaticLibsDir "builtArchives" )

if(WIN32)
	set( SDL2_DIR "" )
	set( wxWidgets_ROOT_DIR "" )
    set( wxWidgets_INCLUDE_DIRS "" )
    set( wxWidgets_LIB_DIR "" )
endif(WIN32)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

set( wxWidgets_CONFIGURATION mswu )
find_package( wxWidgets COMPONENTS core base REQUIRED )

add_subdirectory(libraries/genericLib)
add_subdirectory(libraries/spriteMoveLib)
add_subdirectory(libraries/sdl2_wrapper)
add_subdirectory(libraries/sdlLogoDisplay)
add_subdirectory(libraries/soundSystem)
add_subdirectory(libraries/wxPrefPath)

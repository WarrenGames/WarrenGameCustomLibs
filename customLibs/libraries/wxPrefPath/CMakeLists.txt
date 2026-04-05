cmake_minimum_required(VERSION 3.13)

project( wxPrefPath LANGUAGES CXX )

file( GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "sources/*.h" )

file( GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "sources/*.cpp" )

add_library(	
	${PROJECT_NAME} 
	STATIC 
	${SOURCES} 
	${HEADERS} 
	${INC_DIRS}
)

source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${HEADERS} ${SOURCES}
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE ${SDL2_INCLUDE_DIRS}
	PRIVATE sources
	PRIVATE ../genericLib/sources
)

target_link_libraries(	
	${PROJECT_NAME} 
	PRIVATE ${SDL2_LIBRARIES} 
	PUBLIC ${wxWidgets_LIBRARIES}
)

install( DIRECTORY sources/ DESTINATION includes/wxPrefPath FILES_MATCHING PATTERN "*.h" )

install(
	TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${BuiltSharedLibsDir}
	ARCHIVE DESTINATION ${BuiltStaticLibsDir}
)

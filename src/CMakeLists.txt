include(AMXConfig)
include(AddSAMPPlugin)

set(PLUGIN_SOURCES ${SAMPSDK_DIR}/amxplugin.cpp)

add_subdirectory(manipulation)
add_subdirectory(natives)
add_subdirectory(utility)

list(APPEND PLUGIN_SOURCES
	cell.cpp
	chunk-streamer.cpp
	core.cpp
	data.cpp
	grid.cpp
	identifier.cpp
	item.cpp
	main.cpp
	player.cpp
	precompiled.cpp
	streamer.cpp
)

if(WIN32)
	list(APPEND PLUGIN_SOURCES
		${PROJECT_SOURCE_DIR}/streamer.rc
	)
endif()

add_samp_plugin(${PROJECT_NAME} ${PLUGIN_SOURCES})

if(WIN32)
	add_definitions(-DBOOST_ALL_NO_LIB -DNOMINMAX)
else()
	set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY COMPILE_FLAGS " -fno-strict-aliasing")
	set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -lrt")
endif()

add_definitions(-DBOOST_CHRONO_HEADER_ONLY)

set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} OMP-SDK omp-gdk)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

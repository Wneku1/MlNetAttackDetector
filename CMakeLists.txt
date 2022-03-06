cmake_minimum_required( VERSION 3.22 )

project( AttackDetector LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

file( GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp )

set( TARGET_LINK_LIBRARIES ${Boost_LIBRARIES} )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )
set( CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo;Release" )

set( Boost_USE_STATIC_LIBS ON )
add_compile_definitions( BOOST_ERROR_CODE_HEADER_ONLY )
find_package( Boost 1.69.0 )
include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIR} )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
execute_process( COMMAND ln -sf "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" )

configure_file( launch.json.in ${CMAKE_SOURCE_DIR}/.vscode/launch.json )

add_executable( ${CMAKE_PROJECT_NAME} ${SRC} )  
target_link_libraries( ${CMAKE_PROJECT_NAME} PRIVATE ${TARGET_LINK_LIBRARIES} )
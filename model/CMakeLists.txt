cmake_minimum_required( VERSION 3.22 )

project( AttackDetector LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_FLAGS "-lboost_serialization" )


file( GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp )

set( TARGET_LINK_LIBRARIES ${Boost_LIBRARIES} ${MLPACK_LIBRARY} ${MLPACK_LIBRARIES} armadillo )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake" )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )
set( CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo;Release" )

set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
add_compile_definitions( BOOST_ERROR_CODE_HEADER_ONLY )

find_package( Boost 1.79.0 REQUIRED COMPONENTS filesystem serialization wserialization )
find_package( MLPACK REQUIRED )

include_directories( ${Boost_INCLUDE_DIR} ${MLPACK_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIR} )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
execute_process( COMMAND ln -sf "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" )

configure_file( launch.json.in ${CMAKE_SOURCE_DIR}/.vscode/launch.json )

add_executable( ${CMAKE_PROJECT_NAME} ${SRC} )  
target_link_libraries( ${CMAKE_PROJECT_NAME} PRIVATE ${TARGET_LINK_LIBRARIES} )
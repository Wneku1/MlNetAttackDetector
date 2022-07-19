cmake_minimum_required ( VERSION 3.4.3 )
project ( defender CXX )

set ( TARGET_NAME "defender" )

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

set( TARGET_LINK_LIBRARIES ${Boost_LIBRARIES} ${MLPACK_LIBRARY} ${MLPACK_LIBRARIES} armadillo )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake" )
set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
add_compile_definitions( BOOST_ERROR_CODE_HEADER_ONLY )

find_package( Boost 1.79.0 REQUIRED COMPONENTS filesystem serialization wserialization thread )
find_package( MLPACK REQUIRED )

include_directories( ${Boost_INCLUDE_DIR} ${MLPACK_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIR} )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
execute_process( COMMAND ln -sf "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" )

include ( FindPkgConfig )
pkg_search_module ( SNORT3 REQUIRED snort>=3 )

add_library (
    ${TARGET_NAME} MODULE
    api_conf.cpp
    config.hpp
    config.cpp
    inspector.hpp
    inspector.cpp
    module.hpp
    module.cpp
    featuresExtractor.hpp
    featuresExtractor.cpp
    model.hpp
    model.cpp
    packet_length_collector.hpp
    packet_length_collector.cpp
    utils.hpp
)

set_target_properties (
    ${TARGET_NAME}
    PROPERTIES
        PREFIX ""
)

target_include_directories (
    ${TARGET_NAME} PUBLIC
    ${SNORT3_INCLUDE_DIRS}
)

install (
    TARGETS ${TARGET_NAME}
    LIBRARY
        DESTINATION "${INSPECTOR_INSTALL_PATH}"
)

target_link_libraries( ${TARGET_NAME} PUBLIC ${TARGET_LINK_LIBRARIES} )

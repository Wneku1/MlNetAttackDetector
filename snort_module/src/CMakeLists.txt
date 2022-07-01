cmake_minimum_required ( VERSION 3.4.3 )
project ( defender CXX )

set(INSPECTOR_INSTALL_PATH "${PLUGIN_INSTALL_PATH}/inspectors")
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

include ( FindPkgConfig )
pkg_search_module ( SNORT3 REQUIRED snort>=3 )

add_library (
    defender MODULE
    api_conf.cpp
    config.hpp
    config.cpp
    inspector.hpp
    inspector.cpp
    module.hpp
    module.cpp
    featuresExtractor.hpp
    featuresExtractor.cpp
)

set_target_properties (
    defender
    PROPERTIES
        PREFIX ""
)

target_include_directories (
    defender PUBLIC
    ${SNORT3_INCLUDE_DIRS}
)

install (
    TARGETS defender
    LIBRARY
        DESTINATION "${INSPECTOR_INSTALL_PATH}"
)

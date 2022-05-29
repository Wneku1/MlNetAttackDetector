cmake_minimum_required ( VERSION 3.4.3 )
project ( detector CXX )

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

include ( FindPkgConfig )
pkg_search_module ( SNORT3 REQUIRED snort>=3 )

add_library (
    detector MODULE
    api_conf.cpp
    config.hpp
    config.cpp
	inspector.hpp
    inspector.cpp
    module.hpp
    module.cpp
    param_default_value.hpp
    parameters_name.hpp
)

set_target_properties (
    detector
    PROPERTIES
        PREFIX ""
)

target_include_directories (
    detector PUBLIC
    ${SNORT3_INCLUDE_DIRS}
)

install (
    TARGETS detector
    LIBRARY
        DESTINATION "${INSPECTOR_INSTALL_PATH}"
)

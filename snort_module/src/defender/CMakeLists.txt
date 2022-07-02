cmake_minimum_required ( VERSION 3.4.3 )
project ( defender CXX )

set (TARGET_NAME ${CMAKE_PROJECT_NAME})

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

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

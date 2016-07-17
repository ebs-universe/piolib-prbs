
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0007 NEW)

PROJECT(prbs C)
SET(prbs_VERSION_MAJOR 1)
SET(prbs_VERSION_MINOR 0)
SET(prbs_VERSION_PATCH 0)
SET(prbs_VERSION_TWEAK 0)

SET(TMP_PROJECT_DESCRIPTION "Simple pseudo random bitstream generator for link and protocol testing"
        CACHE STRING "Project Description")

FILE(GLOB SOURCES *.c)
FILE(GLOB_RECURSE HEADERS *.h)

IF(CMAKE_TOOLCHAIN_FILE)
    # This is a cross-platform build, and therefore is assumed to be intended for an 
    # embedded target.
    SET(CMAKE_INSTALL_PREFIX ${PLATFORM_PACKAGES_PATH})
    SET(PUBLIC_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
	    	    
    ADD_PLATFORM_LIBRARY(prbs STATIC "" ${SOURCES})
    INSTALL_PLATFORM_LIBRARY(prbs ${HEADERS})
    
ELSE(CMAKE_TOOLCHAIN_FILE)
    # This is a native build, and is assumed to be intended for the host. 
    # Libraries and bindings are therefore installed into the appropriate host prefix.
    
    # NOTE: C library is not compiled separately and is not installed.
    
    # Create PYTHON bindings
    FIND_PACKAGE(SWIG REQUIRED)
    INCLUDE(${SWIG_USE_FILE})
    
    FIND_PACKAGE(PythonLibs)
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
    SET(CMAKE_SWIG_FLAGS "")
    SWIG_ADD_MODULE(prbs python prbs.i prbs.c)
    SWIG_LINK_LIBRARIES(prbs ${PYTHON_LIBRARIES})
    
    # Install PYTHON bindings
    EXECUTE_PROCESS(COMMAND python -c "from distutils.sysconfig import get_python_lib; print get_python_lib()" 
                    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
    INSTALL(TARGETS _prbs DESTINATION ${PYTHON_SITE_PACKAGES})
    INSTALL(FILES ${CMAKE_BINARY_DIR}/prbs.py DESTINATION ${PYTHON_SITE_PACKAGES})
    
ENDIF(CMAKE_TOOLCHAIN_FILE)
#/*************************************************************************************************
# * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                       *
# *                                                                                               *
# * See the NOTICE file(s) distributed with this work for additional information regarding        *
# * copyright ownership.                                                                          *
# *                                                                                               *
# * This program and the accompanying materials are made available under the terms of the Eclipse *
# * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                 *
# *                                                                                               *
# * SPDX-License-Identifier: EPL-2.0                                                              *
# *************************************************************************************************/

PROJECT(KeyplePluginPcscCppLib C CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(VERSION_MAJOR "2")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "0")

SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

SET(PACKAGE_NAME "keyple-plugin-pcsc-cpp-lib")
SET(PACKAGE_VERSION ${VERSION})
SET(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")

SET(CMAKE_MACOSX_RPATH 1)
SET(CMAKE_CXX_STANDARD 11)

SET(LIBRARY_NAME keyplepluginpcsccpplib)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DKEYPLEPLUGINPCSC_EXPORT")

SET(CALYPSONET_CARD_DIR    "../../../github.com.calypsonet.calypsonet-terminal-card-cpp-api")
SET(CALYPSONET_READER_DIR  "../../../github.com.calypsonet.calypsonet-terminal-reader-cpp-api")
SET(KEYPLE_COMMON_DIR      "../../../github.com.calypsonet.keyple-common-cpp-api")
SET(KEYPLE_PLUGIN_DIR      "../../../github.com.calypsonet.keyple-plugin-cpp-api")
SET(KEYPLE_UTIL_DIR        "../../../github.com.calypsonet.keyple-util-cpp-lib")
SET(KEYPLE_SERVICE_DIR     "../../../github.com.calypsonet.keyple-service-cpp-lib")
SET(KEYPLE_UTIL_LIB        "keypleutilcpplib")

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/exception

    ${CALYPSONET_CARD_DIR}/src/main
    ${CALYPSONET_CARD_DIR}/src/main/spi

    ${CALYPSONET_READER_DIR}/src/main
    ${CALYPSONET_READER_DIR}/src/main/selection
    ${CALYPSONET_READER_DIR}/src/main/selection/spi
    ${CALYPSONET_READER_DIR}/src/main/spi

    ${KEYPLE_COMMON_DIR}/src/main

    ${KEYPLE_PLUGIN_DIR}/src/main
    ${KEYPLE_PLUGIN_DIR}/src/main/spi
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader/observable
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader/observable/state/insertion
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader/observable/state/processing
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader/observable/state/removal

    ${KEYPLE_UTIL_DIR}/src/main
    ${KEYPLE_UTIL_DIR}/src/main/cpp
    ${KEYPLE_UTIL_DIR}/src/main/cpp/exception

    ${KEYPLE_SERVICE_DIR}/src/main/cpp

    /usr/include/PCSC
)

ADD_LIBRARY(
    ${LIBRARY_NAME}

    ${LIBRARY_TYPE}

    ${CMAKE_CURRENT_SOURCE_DIR}/AbstractPcscPluginAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AbstractPcscReaderAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PcscPluginAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PcscPluginFactoryAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PcscPluginFactoryBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PcscReaderAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PcscReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PcscSupportedContactProtocol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PcscSupportedContactlessProtocol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/CardTerminal.cpp
)

IF(APPLE)                                                                                           
        FIND_LIBRARY(PCSC PCSC)                                                                     
ELSEIF(UNIX)                                                                                            
        FIND_LIBRARY(PCSC pcsclite)                                                                 
ELSEIF(WIN32)                                                                                           
        SET(CMAKE_FIND_LIBRARY_PREFIXES "")                                                         
        SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")                                                     
        SET(CMAKE_BUILD_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../../../..")                     
        SET(PCSC winscard.lib)                                                                      
ENDIF(APPLE)                                                                                        
                                                                                                    
IF(NOT PCSC)                                                                                        
        MESSAGE(FATAL_ERROR "PC/SC framework/library not found")                                    
ENDIF() 

FIND_LIBRARY(UTIL ${KEYPLE_UTIL_LIB} HINTS ${KEYPLE_UTIL_DIR}/build/bin)

TARGET_LINK_LIBRARIES(${LIBRARY_NAME} ${PCSC} ${UTIL})

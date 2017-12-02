# Install script for directory: /Users/Nick/repositories/exp/EXP/examples/ex1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/Nick/repositories/exp/EXP/examples/bin" TYPE EXECUTABLE FILES "/Users/Nick/repositories/exp/EXP/examples/build/ex1/Debug/EXP_ex1")
    if(EXISTS "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPUtil/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPGL/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPTask/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPSQL/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/Nick/repositories/exp/EXP/examples/bin" TYPE EXECUTABLE FILES "/Users/Nick/repositories/exp/EXP/examples/build/ex1/Release/EXP_ex1")
    if(EXISTS "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPUtil/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPGL/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPTask/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPSQL/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/Nick/repositories/exp/EXP/examples/bin" TYPE EXECUTABLE FILES "/Users/Nick/repositories/exp/EXP/examples/build/ex1/MinSizeRel/EXP_ex1")
    if(EXISTS "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPUtil/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPGL/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPTask/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPSQL/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/Nick/repositories/exp/EXP/examples/bin" TYPE EXECUTABLE FILES "/Users/Nick/repositories/exp/EXP/examples/build/ex1/RelWithDebInfo/EXP_ex1")
    if(EXISTS "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPUtil/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPGL/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPTask/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      execute_process(COMMAND /opt/local/bin/install_name_tool
        -delete_rpath "/Users/Nick/repositories/exp/EXP/EXPSQL/lib"
        "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/Nick/repositories/exp/EXP/examples/bin/EXP_ex1")
      endif()
    endif()
  endif()
endif()


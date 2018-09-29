# Install script for directory: /home/coin/learn-coding-practice/C/cmake

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/bin/main" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/bin/main")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/bin/main"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/coin/learn-coding-practice/C/cmake/bin/main")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/coin/learn-coding-practice/C/cmake/bin" TYPE EXECUTABLE FILES "/home/coin/learn-coding-practice/C/cmake/bin/main")
  if(EXISTS "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/bin/main" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/bin/main")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/bin/main"
         OLD_RPATH "/home/coin/learn-coding-practice/C/cmake/.:/home/coin/learn-coding-practice/C/cmake/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/bin/main")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/lib/libplay.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/lib/libplay.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/lib/libplay.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/coin/learn-coding-practice/C/cmake/lib/libplay.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/coin/learn-coding-practice/C/cmake/lib" TYPE SHARED_LIBRARY FILES "/home/coin/learn-coding-practice/C/cmake/lib/libplay.so")
  if(EXISTS "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/lib/libplay.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/lib/libplay.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/coin/learn-coding-practice/C/cmake/lib/libplay.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/coin/learn-coding-practice/C/cmake/cmake/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

# Install script for directory: /home/jan/projects/rexgen/trunk/src/librexgen

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librexgen.so.1.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librexgen.so.1.0")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librexgen.so.1.0"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/jan/projects/rexgen/trunk/src/librexgen/librexgen.so.1.0")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librexgen.so.1.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librexgen.so.1.0")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librexgen.so.1.0")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/librexgen" TYPE FILE FILES
    "/home/jan/projects/rexgen/trunk/src/librexgen/osdepend.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/rexgen_options.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/simplestring.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/version.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/unicode.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/debug.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/librexgen/regex" TYPE FILE FILES
    "/home/jan/projects/rexgen/trunk/src/librexgen/regex/regexalternatives.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/regex/classregex.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/regex/terminalregex.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/regex/quantifier.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/regex/regex.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/regex/groupreference.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/regex/regexcontainer.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/regex/compoundregex.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/regex/streamregex.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/librexgen/iterator" TYPE FILE FILES
    "/home/jan/projects/rexgen/trunk/src/librexgen/iterator/iterator.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/iterator/compoundregexiterator.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/iterator/iteratorstate.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/iterator/streamregexiterator.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/iterator/regexalternativesiterator.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/iterator/classregexiterator.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/iterator/topiterator.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/iterator/iteratorpermuter.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/iterator/terminalregexiterator.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/iterator/groupreferenceiterator.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/librexgen/parser" TYPE FILE FILES
    "/home/jan/projects/rexgen/trunk/src/librexgen/parser/rexgenparsercontext.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/parser/parse_escapes.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/parser/syntaxerror.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/librexgen/unicode" TYPE FILE FILES
    "/home/jan/projects/rexgen/trunk/src/librexgen/unicode/simple_string.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/unicode/utf32.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/librexgen/state" TYPE FILE FILES
    "/home/jan/projects/rexgen/trunk/src/librexgen/state/invaliditeratoridexception.h"
    "/home/jan/projects/rexgen/trunk/src/librexgen/state/serializablestate.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/librexgen/api/c" TYPE FILE FILES "/home/jan/projects/rexgen/trunk/src/librexgen/api/c/librexgen.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")


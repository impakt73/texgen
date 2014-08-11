CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( TexGen )

#
#	TexGen
#
SET( BIN_DIR ${CMAKE_HOME_DIRECTORY}/bin )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}" )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}" )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}" )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}" )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}" )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}" )

SET( CMAKE_DEBUG_POSTFIX "_Debug" )
SET( CMAKE_RELEASE_POSTFIX "_Release" )

SET( BEAST_USE_LUAJIT ON )

IF( UNIX )
    SET( CMAKE_C_COMPILER "clang" )
    SET( CMAKE_CXX_COMPILER "clang++" )

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
ENDIF()

SET( LIB_DIR ${CMAKE_HOME_DIRECTORY}/lib )
INCLUDE_DIRECTORIES( "${CMAKE_HOME_DIRECTORY}/src" "${CMAKE_HOME_DIRECTORY}/include" )
LINK_DIRECTORIES   ( "${BIN_DIR}" "${LIB_DIR}" )
ADD_DEFINITIONS	   ( "-D_UNICODE" "-DUNICODE" "-D_CRT_SECURE_NO_WARNINGS" )

SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG -D_CRTDBG_MAP_ALLOC" )

FUNCTION( ADD_SOURCE inVariableName inDirPrefix inSourceGroup outSourceList )
	SET( "${inVariableName}" ${ARGN} )
	FOREACH( filename ${${inVariableName}} )
		LIST( APPEND FILE_LIST ${inDirPrefix}/${filename}  )
	ENDFOREACH( filename )
	SET( "${outSourceList}" ${${outSourceList}} ${FILE_LIST} PARENT_SCOPE )
	SOURCE_GROUP( "${inSourceGroup}" FILES ${FILE_LIST} )
ENDFUNCTION( ADD_SOURCE )

#
#	Source Files
#
#->Main
ADD_SOURCE( MAIN_SRC "src" "" SRC_FILES Main.cpp )
ADD_SOURCE( TEXGEN_SRC "src/TexGen" "TexGen" SRC_FILES stb_image_write.h stb_image_write.cpp OperationNode.h Texture.h TextureNode.h Node.h NodeType.h Parser.h Parser.cpp File.h TokenData.h NumberTokenData.h IdentifierTokenData.h Lexer.h Lexer.cpp Token.h File.cpp Generator.h Generator.cpp Scanner.h Scanner.cpp )
ADD_SOURCE( TEXGEN_SRC "src/TexGen/Operations" "TexGen\\Operations" SRC_FILES Operation.h ClearOperation.h ClearOperation.cpp NoiseOperation.h NoiseOperation.cpp )

ADD_EXECUTABLE( "${PROJECT_NAME}" WIN32 ${SRC_FILES} )

IF( WIN32 )
	#For VS2012 Compatibility
	SET_TARGET_PROPERTIES( ${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SAFESEH:NO" )
ENDIF()

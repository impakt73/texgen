#pragma once

class File
{
public:
	static const char *ReadTextFile( const char *filename );
	static const unsigned char *ReadBinaryFile( const char *filename, unsigned int *length );
    static long int GetLastModified( const char* inFilename );
};

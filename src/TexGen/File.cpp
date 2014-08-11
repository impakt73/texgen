#include <TexGen/File.h>
#include <cstdio>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <sys/stat.h>
#endif

const char *File::ReadTextFile( const char *filename )
{
	//Open File
	FILE *f = fopen( filename, "rb" );

	if( f == NULL )
	{
		return NULL;
	}
	
	//Determine Filesize
	fseek( f, 0L, SEEK_END );

	long fileSize = ftell( f );

	fseek( f, 0L, SEEK_SET );
	
	//Allocate buffer
	char *data = new char[fileSize+1];
	fread( ( void * )data, sizeof( char ), fileSize, f );
	data[fileSize] = '\0';

	//Close the file
	fclose( f );

	return data;
}

const unsigned char *File::ReadBinaryFile( const char *filename, unsigned int *length )
{
	//Open File
	FILE *f = fopen( filename, "rb" );

	if( f == NULL )
	{
		return NULL;
	}
	
	//Determine Filesize
	fseek( f, 0L, SEEK_END );

	long fileSize = ftell( f );

	fseek( f, 0L, SEEK_SET );
	
	//Allocate buffer
	unsigned char *data = new unsigned char[fileSize];
	fread( ( void * )data, sizeof( char ), fileSize, f );

	//Close the file
	fclose( f );

	*length = fileSize;

    return data;
}

long int File::GetLastModified(const char *inFilename)
{
#ifdef WIN32
	HANDLE handle = CreateFileA( inFilename,
			GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL );
		if( handle != INVALID_HANDLE_VALUE )
		{
			FILETIME lastWrite;
			if( GetFileTime( handle, nullptr, nullptr, &lastWrite ) )
			{
				ULONGLONG timeValue = (((ULONGLONG) lastWrite.dwHighDateTime) << 32) + lastWrite.dwLowDateTime;
				long int timeInSeconds = (long)(( timeValue / 10000000 ) - 11644473600LL);
				return timeInSeconds;
            }
            CloseHandle( handle );
		}
#else
    struct stat fileStat;
    if(stat(inFilename, &fileStat) == 0)
    {
        return fileStat.st_mtim.tv_sec;
    }
#endif
    return -1;
}

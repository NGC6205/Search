#include "FileSystemClass.h"
#include "NTFS_class.h"
#include "FAT32_class.h"
#include "ExFAT_class.h"

// ---------------------------------------------------------------------------
FileSystemClass::FileSystemClass( )
{
	FileHandle = 0;
	BytesPerCluster = 0;
	TotalClusters = 0;
}

// ---------------------------------------------------------------------------
FileSystemClass::~FileSystemClass( )
{
}

// ---------------------------------------------------------------------------
bool FileSystemClass::Open( wstring fileName )
{
	if ( FileHandle != 0 )
	{
		MessageBoxW( NULL, L"Уже есть открытый файл, закройте его", L"Ошибка", MB_OK );
		return false;
	}
	FileHandle = CreateFileW( fileName.c_str( ), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( FileHandle == INVALID_HANDLE_VALUE )
	{
		MessageBoxW( NULL, L"Ошибка открытия файла, проверьте правильность пути", L"Ошибка", MB_OK );
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
void FileSystemClass::Close( )
{
	if ( FileHandle == 0 )
	{
		MessageBoxW( NULL, L"Файл не был открыт", L"Ошибка", MB_OK );
		return;
	}
	CloseHandle( FileHandle );
	FileHandle = 0;
}

// ---------------------------------------------------------------------------
FileSystemClass * FileSystemClass::GetFileSystem( FsType fsType )
{
	FileSystemClass * p;
	switch ( fsType )
	{
	case NTFS:
		p = new NTFS_class( );
		break;
	case FAT32:
		p = new FAT32_class( );
		break;
	case ExFAT:
		p = new ExFAT_class( );
		break;
	default:
		p = NULL;
		break;
	}
	return p;
}

// ---------------------------------------------------------------------------
ULONGLONG FileSystemClass::GetTotalClusters( )
{
	return TotalClusters;
}

// ---------------------------------------------------------------------------
UINT32 FileSystemClass::GetBytesPerCluster( )
{
	return BytesPerCluster;
}

// ---------------------------------------------------------------------------
std::string FileSystemClass::GetOEMName( )
{
	return OEMName;
}

// ---------------------------------------------------------------------------
UINT32 FileSystemClass::GetBeginCluster( )
{
	return BeginCluster;
}
// ---------------------------------------------------------------------------

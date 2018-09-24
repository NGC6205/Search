#include "ExFAT_class.h"
#include "ExFATClusterIterator.h"

// ---------------------------------------------------------------------------
ExFAT_class::ExFAT_class( ) : FileSystemClass( )
{
	SectorOfBitmap = 0;
}

// ---------------------------------------------------------------------------
bool ExFAT_class::ReadBootSector( )
{
	if ( FileHandle == 0 || FileHandle == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	BYTE BootSector[ 512 ];
	ULONGLONG StartOffset = 0;
	DWORD BytesToRead = 512;
	DWORD BytesRead;
	LARGE_INTEGER SectorOffset;
	SectorOffset.QuadPart = StartOffset;

	unsigned long CurrentPosition = SetFilePointer( FileHandle, SectorOffset.LowPart, &SectorOffset.HighPart, FILE_BEGIN );

	if ( CurrentPosition != SectorOffset.LowPart )
	{
		//MessageBoxW( NULL, L"Ошибка позицинирования в файле", L"Ошибка", MB_OK );
		return false;
	}

	bool ReadResult = ReadFile( FileHandle, BootSector, BytesToRead, &BytesRead, NULL );

	if ( !ReadResult || BytesRead != BytesToRead )
	{
		//MessageBoxW( NULL, L"Ошибка чтения файла", L"Ошибка", MB_OK );
		return false;
	}
	bootExFAT * pBootExFAT;
	pBootExFAT = ( bootExFAT * ) BootSector;
	OEMName.assign( ( char * ) pBootExFAT->OEMName, 8 );
	if ( OEMName == "\x45\x58\x46\x41\x54\x20\x20\x20" )
	{
		SectorOfBitmap = pBootExFAT->sectorOfBitmap;
		BytesPerCluster = ( 1 << pBootExFAT->sizeOfSector ) * ( 1 << pBootExFAT->clusterMlt );
		TotalClusters = pBootExFAT->countOfCluster;
		BeginCluster = 0;
		return true;
	}
	else
	{
		//MessageBoxW( NULL, L"Файловая система раздела не ExFAT", L"Ошибка", MB_OK );
		return false;
	}

}

// ---------------------------------------------------------------------------
IndexIterator < ClusterDisk > * ExFAT_class::GetClusterIterator( )
{
	return new ExFATClusterIterator( this );
}

// ---------------------------------------------------------------------------
bool ExFAT_class::ReadCluster(
	ULONGLONG startCluster,
	DWORD     numberOfCluster,
	BYTE *    outBuffer )
{
	if ( FileHandle == 0 || BytesPerCluster == 0 )
	{
		//MessageBoxW( NULL, L"Ошибка раздел не был открыт или открыт неверно", L"Ошибка", MB_OK );
		return false;
	}
	ULONGLONG StartOffset = 512 * SectorOfBitmap - 2 * BytesPerCluster + BytesPerCluster * startCluster;
	DWORD BytesToRead = BytesPerCluster * numberOfCluster;
	DWORD BytesRead;
	LARGE_INTEGER SectorOffset;
	SectorOffset.QuadPart = StartOffset;

	unsigned long CurrentPosition = SetFilePointer( FileHandle, SectorOffset.LowPart, &SectorOffset.HighPart, FILE_BEGIN );

	if ( CurrentPosition != SectorOffset.LowPart )
	{
		//MessageBoxW( NULL, L"Ошибка позиционирования в разделе", L"Ошибка", MB_OK );
		return false;
	}

	bool ReadResult = ReadFile( FileHandle, outBuffer, BytesToRead, &BytesRead, NULL );

	if ( !ReadResult || BytesRead != BytesToRead )
	{
		//MessageBoxW( NULL, L"Ошибка чтения кластера", L"Ошибка", MB_OK );
		return false;
	}
	return true;

}

// -----------------------------------ClusterIterator----------------------------
ExFATClusterIterator::ExFATClusterIterator( ExFAT_class * fileSystem )
{
	FileSystem = fileSystem;
	CurrentCluster = FileSystem->GetBeginCluster( );
	BytesPerCluster = FileSystem->GetBytesPerCluster( );
	DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void ExFATClusterIterator::First( )
{
	CurrentCluster = FileSystem->GetBeginCluster( );
}

// ------------------------------------------------------------------------------
void ExFATClusterIterator::Next( )
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool ExFATClusterIterator::IsDone( ) const
{
	int TotalClusters = FileSystem->GetTotalClusters( );
	return ( CurrentCluster >= TotalClusters );
}

// ------------------------------------------------------------------------------
ClusterDisk ExFATClusterIterator::GetCurrent( )
{
	FileSystem->ReadCluster( CurrentCluster, 1, DataBuffer );
	Cluster.assign( DataBuffer, DataBuffer + BytesPerCluster );
	return Cluster;
}

// ------------------------------------------------------------------------------
ExFATClusterIterator::~ExFATClusterIterator( )
{
	delete[ ]DataBuffer;
}

// ------------------------------------------------------------------------------
int ExFATClusterIterator::GetCurrentIndex( ) const
{
	return CurrentCluster;
}

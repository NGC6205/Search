#include "FAT32_class.h"


// ---------------------------------------------------------------------------
FAT32_class::FAT32_class( ) : FileSystemClass( )
{
	BytesPerReservedArea = 0;
	BytesPerCopiesFAT = 0;
}

// ---------------------------------------------------------------------------
bool FAT32_class::ReadBootSector( )
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
	bootFAT32 * pBootFAT32;
	pBootFAT32 = ( bootFAT32 * ) BootSector;
	OEMName.assign( ( char * ) pBootFAT32->markOfTypeFS, 8 );
	if ( OEMName == "\x46\x41\x54\x33\x32\x20\x20\x20" )
	{
		BytesPerReservedArea = pBootFAT32->reservedArea * pBootFAT32->bytesPerSector;
		BytesPerCopiesFAT = pBootFAT32->sizeOfCopiesFAT32 * pBootFAT32->countOfCopiesFAT * pBootFAT32->bytesPerSector;
		BytesPerCluster = pBootFAT32->bytesPerSector * pBootFAT32->sectorPerClusterMlt;
		BeginCluster = 2;

		if ( pBootFAT32->countOfSectors16 == 0 )
		{
			TotalClusters = pBootFAT32->countOfSectors32 / pBootFAT32->sectorPerClusterMlt;
		}
		else
		{
			TotalClusters = pBootFAT32->countOfSectors16 / pBootFAT32->sectorPerClusterMlt;
		}
		return true;
	}
	else
	{
		//MessageBoxW( NULL, L"Файловая система раздела не FAT32", L"Ошибка", MB_OK );
		return false;
	}
}

// ---------------------------------------------------------------------------
Iterator < ClusterDisk > * FAT32_class::GetClusterIterator( )
{
	return new FAT32ClusterIterator( this );
}

// ---------------------------------------------------------------------------
bool FAT32_class::ReadCluster(	ULONGLONG startCluster,	DWORD     numberOfCluster,	BYTE *    outBuffer )
{
	if ( FileHandle == 0 || BytesPerCluster == 0 )
	{
		//MessageBoxW( NULL, L"Ошибка раздел не был открыт или открыт неверно", L"Ошибка", MB_OK );
		return false;
	}
	ULONGLONG StartOffset = BytesPerReservedArea + BytesPerCopiesFAT + BytesPerCluster * ( startCluster - BeginCluster );
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
// ---------------------------------------------------------------------------
// ------------------------------------------------------------------------------
FAT32ClusterIterator::FAT32ClusterIterator( FAT32_class * fileSystem )
{
	FileSystem = fileSystem;
	CurrentCluster = FileSystem->GetBeginCluster( );
	BytesPerCluster = FileSystem->GetBytesPerCluster( );
	DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void FAT32ClusterIterator::First( )
{
	CurrentCluster = FileSystem->GetBeginCluster( );
}

// ------------------------------------------------------------------------------
void FAT32ClusterIterator::Next( )
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool FAT32ClusterIterator::IsDone( ) const
{
	int TotalClusters = FileSystem->GetTotalClusters( );
	return ( CurrentCluster >= TotalClusters );
}

// ------------------------------------------------------------------------------
ClusterDisk FAT32ClusterIterator::GetCurrent( )
{
	FileSystem->ReadCluster( CurrentCluster, 1, DataBuffer );
	Cluster.assign( DataBuffer, DataBuffer + BytesPerCluster );
	return Cluster;
}

// ------------------------------------------------------------------------------
FAT32ClusterIterator::~FAT32ClusterIterator( )
{
	delete[ ]DataBuffer;
}

// ------------------------------------------------------------------------------
int FAT32ClusterIterator::GetCurrentIndex( ) const
{
	return CurrentCluster;
}

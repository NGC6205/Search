// Файл с реализацией функций класса
#include "NTFS_class.h"

// ---------------------------------------------------------------------------
bool NTFS_class::ReadBootSector( )
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
	bootNTFS * pBootNTFS;
	pBootNTFS = ( bootNTFS * ) BootSector;
	OEMName.assign( ( char * ) pBootNTFS->OEMName, 8 );
	if ( OEMName == "\x4e\x54\x46\x53\x20\x20\x20\x20" )
	{
		BytesPerCluster = pBootNTFS->bytesPerSector * pBootNTFS->sectorPerCluster;
		TotalClusters = pBootNTFS->totalSectors / pBootNTFS->sectorPerCluster;
		BeginCluster = 0;
		return true;
	}
	else
	{
		//MessageBoxW( NULL, L"Файловая система раздела не NTFS", L"Ошибка", MB_OK );
		return false;
	}
}

// ---------------------------------------------------------------------------
bool NTFS_class::ReadCluster(
	ULONGLONG startCluster,
	DWORD     numberOfCluster,
	BYTE *    outBuffer )
{
	if ( FileHandle == 0 || BytesPerCluster == 0 )
	{
		//MessageBoxW( NULL, L"Ошибка раздел не был открыт или открыт неверно", L"Ошибка", MB_OK );
		return false;
	}
	ULONGLONG StartOffset = BytesPerCluster * startCluster;
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
Iterator < ClusterDisk > * NTFS_class::GetClusterIterator( )
{
	return new NTFSClusterIterator( this );
}
// ---------------------------------------------------------------------------

// ------------------------------------------------------------------------------
NTFSClusterIterator::NTFSClusterIterator( NTFS_class * fileSystem )
{
	FileSystem = fileSystem;
	CurrentCluster = FileSystem->GetBeginCluster( );
	BytesPerCluster = FileSystem->GetBytesPerCluster( );
	DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void NTFSClusterIterator::First( )
{
	CurrentCluster = FileSystem->GetBeginCluster( );
}

// ------------------------------------------------------------------------------
void NTFSClusterIterator::Next( )
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool NTFSClusterIterator::IsDone( ) const
{
	int TotalClusters = FileSystem->GetTotalClusters( );
	return ( CurrentCluster >= TotalClusters );
}

// ------------------------------------------------------------------------------
ClusterDisk NTFSClusterIterator::GetCurrent( )
{
	FileSystem->ReadCluster( CurrentCluster, 1, DataBuffer );
	Cluster.assign( DataBuffer, DataBuffer + BytesPerCluster );
	return Cluster;
}

// ------------------------------------------------------------------------------
NTFSClusterIterator::~NTFSClusterIterator( )
{
	delete[ ]DataBuffer;
}

// ------------------------------------------------------------------------------
int NTFSClusterIterator::GetCurrentIndex( ) const
{
	return CurrentCluster;
}
// ---------------------------------------------------------------------------

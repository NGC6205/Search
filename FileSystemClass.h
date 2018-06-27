#ifndef FileSystemClassH
#define FileSystemClassH
// ---------------------------------------------------------------------------
#include "Iterator.h"
#include "Structures.h"

// ---------------------------------------------------------------------------
class FileSystemClass
{
protected:
	HANDLE FileHandle;
	ULONGLONG TotalClusters;
	UINT32 BytesPerCluster;
	UINT32 BeginCluster;
	string OEMName;

public:
	FileSystemClass( );
	~FileSystemClass( );

	bool Open( wstring fileName );
	void Close( );
	ULONGLONG GetTotalClusters( );
	UINT32 GetBytesPerCluster( );
	UINT32 GetBeginCluster( );
	string GetOEMName( );
	virtual bool ReadCluster(
		ULONGLONG startCluster,
		DWORD     numberOfCluster,
		BYTE *    outBuffer ) = 0;
	virtual bool ReadBootSector( ) = 0;
	virtual Iterator < ClusterDisk > * GetClusterIterator( ) = 0;
	static FileSystemClass * GetFileSystem( FsType fsType );
} ;
// ---------------------------------------------------------------------------
#endif

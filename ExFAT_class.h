// ---------------------------------------------------------------------------
#ifndef ExFAT_classH
#define ExFAT_classH
// ---------------------------------------------------------------------------
#include "Structures.h"
#include "FileSystemClass.h"
#include "IndexIterator.h"
// ---------------------------------------------------------------------------

class ExFAT_class : public FileSystemClass
{
private:
	UINT32 SectorOfBitmap;

public:
	ExFAT_class( );

	bool ReadCluster(
		ULONGLONG startCluster,
		DWORD     numberOfCluster,
		BYTE *    outBuffer );
	bool ReadBootSector( );
	IndexIterator < ClusterDisk > * GetClusterIterator( );
} ;
// ---------------------------------------------------------------------------
class ExFATClusterIterator : public IndexIterator < ClusterDisk >
{
private:
	ExFAT_class * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	ExFATClusterIterator( ExFAT_class * fileSystem );
	virtual ~ExFATClusterIterator( );
	virtual void First( );
	virtual void Next( );
	virtual bool IsDone( ) const ;
	virtual ClusterDisk GetCurrent( );
	virtual int GetCurrentIndex( ) const ;

} ;
// ---------------------------------------------------------------------------
#endif

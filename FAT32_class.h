// ---------------------------------------------------------------------------
#ifndef FAT32_classH
#define FAT32_classH

// ---------------------------------------------------------------------------
#include "Structures.h"
#include "FileSystemClass.h"
#include "Iterator.h"
// ---------------------------------------------------------------------------

class FAT32_class : public FileSystemClass
{
private:
	UINT32 BytesPerReservedArea;
	UINT32 BytesPerCopiesFAT;

public:
	FAT32_class( );

	bool ReadCluster(
		ULONGLONG startCluster,
		DWORD     numberOfCluster,
		BYTE *    outBuffer );
	bool ReadBootSector( );
	Iterator < ClusterDisk > * GetClusterIterator( );
} ;

// ------------------------------------------------------------------------------
class FAT32ClusterIterator : public Iterator < ClusterDisk >
{
private:
	FAT32_class * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	FAT32ClusterIterator( FAT32_class * fileSystem );
	virtual ~FAT32ClusterIterator( );
	virtual void First( );
	virtual void Next( );
	virtual bool IsDone( ) const ;
	virtual ClusterDisk GetCurrent( );
	virtual int GetCurrentIndex( ) const ;

} ;
#endif

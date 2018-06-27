
#ifndef NTFS_classH
#define NTFS_classH
// -------------------------------------------------------------------------
#include "Structures.h"
#include "FileSystemClass.h"
#include "Iterator.h"


// -------------------------------------------------------------------------
class NTFS_class : public FileSystemClass
{
public:
	NTFS_class( ) : FileSystemClass( )
	{
	} ;

	bool ReadCluster(
		ULONGLONG startCluster,
		DWORD     numberOfCluster,
		BYTE *    outBuffer );
	bool ReadBootSector( );
	Iterator < ClusterDisk > * GetClusterIterator( );
} ;
// -------------------------------------------------------------------------

class NTFSClusterIterator : public Iterator < ClusterDisk >
{
private:
	NTFS_class * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	NTFSClusterIterator( NTFS_class * fileSystem );
	virtual ~NTFSClusterIterator( );
	virtual void First( );
	virtual void Next( );
	virtual bool IsDone( ) const ;
	virtual ClusterDisk GetCurrent( );
	virtual int GetCurrentIndex( ) const ;

} ;
// ----------------------------------------------------------------------------
#endif

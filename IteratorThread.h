// ---------------------------------------------------------------------------

#ifndef IteratorThreadH
#define IteratorThreadH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
// ---------------------------------------------------------------------------
#include "SearchThread.h"
#include "FileSystemClass.h"

// ---------------------------------------------------------------------------
class IteratorThread : public TThread
{
private:
	HANDLE FileSystemHandle;
	SearchThread * MySearchThread;
	FileSystemClass * FileSystem;
	bool RangeSearch;
	int BeginCluster;
	int EndCluster;
	wstring FilePath;
	FsType FileSystemType;

protected:
	void __fastcall Execute( );

public:
	__fastcall IteratorThread(
		wstring filePath,
		int     beginCluster,
		int     endCluster,
		FsType  fsType,
		bool    rangeSearch,
		bool    CreateSuspended );

} ;
// ---------------------------------------------------------------------------
#endif

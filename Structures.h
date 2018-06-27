// ---------------------------------------------------------------------------
#ifndef StructuresH
#define StructuresH
// ---------------------------------------------------------------------------

#include <Windows.h>
#include <string>
#include <vector>
// ---------------------------------------------------------------------------
using namespace std;
// ---------------------------------------------------------------------------
enum FsType
{
	NTFS, FAT32
};
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct
{
	BYTE machInstruction[ 3 ];
	BYTE OEMName[ 8 ];
	UINT16 bytesPerSector;
	BYTE sectorPerCluster;
	BYTE padding1[ 2 ];
	BYTE padding2[ 5 ];
	BYTE typeStore;
	BYTE padding3[ 2 ];
	BYTE padding4[ 8 ];
	BYTE padding5[ 4 ];
	BYTE padding6[ 4 ];
	ULONGLONG totalSectors;
	ULONGLONG clusterMFT;
	ULONGLONG clusterDataMFT;
	BYTE sizeMFT;
	BYTE padding7[ 3 ];
	BYTE sizeIndex;
	BYTE padding8[ 3 ];
	ULONGLONG serialNumber;
	BYTE padding9[ 4 ];
	BYTE padding10[ 426 ];
	BYTE signature[ 2 ];

} bootNTFS;
#pragma pack(pop)
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct
{
	BYTE machInstruction[ 3 ];
	BYTE OEMName[ 8 ];
	UINT16 bytesPerSector;
	BYTE sectorPerClusterMlt;
	UINT16 reservedArea;
	BYTE countOfCopiesFAT;
	UINT16 maxCountOfFiles;
	UINT16 countOfSectors16;
	BYTE typeOfStore;
	UINT16 sizeOfCopiesFAT16;
	UINT16 sectorPerTrack;
	UINT16 countOfHeads;
	UINT32 sectorsBeforePartition;
	UINT32 countOfSectors32;
	UINT32 sizeOfCopiesFAT32;
	UINT16 refresh;
	UINT16 version;
	UINT32 clusterRoot;
	UINT16 sectorFSINFO;
	UINT16 sectorCopiesOfBootSector;
	BYTE padding[ 12 ];
	BYTE numberDiskBIOS;
	BYTE padding2;
	BYTE extSignature;
	UINT32 numberOfVolume;
	BYTE markOfVolume[ 11 ];
	BYTE markOfTypeFS[ 8 ];
	BYTE padding3[ 420 ];
	BYTE siganture[ 2 ];
} bootFAT32;
#pragma pack(pop)
// ---------------------------------------------------------------------------
typedef struct
{
	__int64 currentCluster;
	string signature;
	string extensionFile;
} findFile;
// ---------------------------------------------------------------------------
typedef vector < BYTE > ClusterDisk;
typedef struct
{
	string signature;
	string extensionFile;

} nodeSignature;
// ---------------------------------------------------------------------------
#endif

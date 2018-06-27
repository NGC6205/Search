// ---------------------------------------------------------------------------

#ifndef SearchThreadH
#define SearchThreadH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "Structures.h"
// ----------------------------------------------------------------------------


const int WaitDelayMs = 200;
const int NumSignatures = 32;
const nodeSignature signatures[ NumSignatures ] =
{
	{
		"\xed\xab\xee\xdb",
		".rpm"
	} ,
	{
		"\x53\x50\x30\x31",
		".bin"
	} ,
	{
		"\x1f\x9d",
		".tar.z"
	} ,
	{
		"\x1f\xa0",
		".tar.z"
	} ,
	{
		"\x47\x49\x46\x38\x37\x61",
		".gif"
	} ,
	{
		"\x47\x49\x46\x38\x39\x61",
		".gif"
	} ,
	{
		"\x49\x49\x2a\x00",
		".tif/.tiff"
	} ,
	{
		"\x4d\x4d\x00\x2a",
		".tif/.tiff"
	} ,
	{
		"\xff\xd8\xff",
		".jpg/.jpeg"
	} ,
	{
		"\x4d\x5a",
		".exe"
	} ,
	{
		"\x50\x4b\x03\x04",
		".zip"
	} ,
	{
		"\x50\x4b\x05\x06",
		".zip"
	} ,
	{
		"\x50\x4b\x07\x08",
		".zip"
	} ,
	{
		"\x52\x61\x72\x21\x1a\x07\x00",
		".rar"
	} ,
	{
		"\x52\x61\x72\x21\x1a\x07\x01\x00",
		".rar"
	} ,
	{
		"\x89\x50\x4e\x47\x0d\x0a\x1a\x0a",
		".png"
	} ,
	{
		"\xca\xfe\xba\xbe",
		".class"
	} ,
	{
		"\x25\x50\x44\x46",
		".pdf"
	} ,
	{
		"\x38\x42\x50\x53",
		".psd"
	} ,
	{
		"\xff\xfb",
		".mp3"
	} ,
	{
		"\x49\x44\x33",
		".mp3"
	} ,
	{
		"\x42\x4d",
		".bmp"
	} ,
	{
		"\x66\x4c\x61\x43",
		".flac"
	} ,
	{
		"\x4b\x44\x4d",
		".vmdk"

	} ,
	{
		"\x50\x4d\x4f\x43\x43\x4d\x4f\x43",
		".dat"
	} ,
	{
		"\x75\x73\x74\x61\x72\x00\x30\x30",
		".tar"
	} ,
	{
		"\x75\x73\x74\x61\x72\x20\x20\x00",
		".tar"
	} ,
	{
		"\x37\x7a\xbc\xaf\x27\x1c",
		".7z"
	} ,
	{
		"\x1f\x8b",
		".tar.gz"
	} ,
	{
		"\x1a\x45\xdf\xa3",
		".mkv"
	} ,
	{
		"\x7b\x5c\x72\x74\x66",
		".rtf"
	} ,
	{
		"\x3c\x3f\x78\x6d\x6c\x20",
		".xml"
	}
} ;
// ---------------------------------------------------------------------------
const vector < nodeSignature > vSignature(signatures, signatures + NumSignatures );

// ---------------------------------------------------------------------------
class SearchThread : public TThread
{
private:
	int BytesPerCluster;
	const vector < BYTE > *OutBufferPtr;
	BYTE * DataBuffer;
	int CurrentCluster;
	string CurrentSignature;
	string CurrentExtensionFile;

	void CopyData( );
	void SearchData( );
	void __fastcall AddMatch( );
	void __fastcall CompleteSearch( );
	void __fastcall ViewCluster( );

protected:
	void __fastcall Execute( );

public:
	__fastcall SearchThread(
		const vector < BYTE > * dataBufferPtr,
		int                     clusterSize,
		bool                    CreateSuspended );
	void SetCurrentCluster( int curCluster );

	// События, используемые для синхронизации
	TEvent * BufferReadyEvent;
	TEvent * BufferCopiedEvent;

} ;
// ---------------------------------------------------------------------------
#endif

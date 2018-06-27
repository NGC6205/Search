// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
// ---------------------------------------------------------------------------
#include "IteratorThread.h"
#include "Iterator.h"
#include "RangeDecorator.h"
#include "FileSystemClass.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
// ---------------------------------------------------------------------------

// Important: Methods and properties of objects in VCL can only be
// used in a method called using Synchronize, for example:
//
// Synchronize(&UpdateCaption);
//
// where UpdateCaption could look like:
//
// void __fastcall IteratorThread::UpdateCaption()
// {
// Form1->Caption = "Updated in a thread";
// }
// ---------------------------------------------------------------------------

__fastcall IteratorThread::IteratorThread(
	wstring filePath,
	int     beginCluster,
	int     endCluster,
	FsType  fsType,
	bool    rangeSearch,
	bool    CreateSuspended ) : TThread(
	        CreateSuspended )
{
	FreeOnTerminate = true;
	FileSystemType = fsType;
	FilePath = filePath;
	RangeSearch = rangeSearch;
	BeginCluster = beginCluster;
	EndCluster = endCluster;
}

// ---------------------------------------------------------------------------
void __fastcall IteratorThread::Execute( )
{
	// ������� �������� �������
	FileSystem = FileSystemClass::GetFileSystem( FileSystemType );
	if ( FileSystem == NULL )
	{
		MessageBoxW( NULL, L"�� ������ ��� �������� �������", L"������", MB_OK );
		return;
	}
	if ( !FileSystem->Open( FilePath ) )
	{
		return;
	}
	// ���������� ������ ��������
	if ( !FileSystem->ReadBootSector( ) )
	{
		return;
	}
	int bytesPerCluster = FileSystem->GetBytesPerCluster( );
	ClusterDisk CurrentCluster;
	MySearchThread = new SearchThread( &CurrentCluster, bytesPerCluster, false );

	if ( BeginCluster > EndCluster )
	{
		MessageBoxW( NULL, L"�������� ������� �� ����� ���� ������ ����������", L"������", MB_OK );
		return;
	}

	// ������� �������� ��� ������� �� ��������� �����
	Iterator < ClusterDisk > *it;
	if ( RangeSearch )
	{
		it = new RangeDecorator( FileSystem->GetClusterIterator( ), BeginCluster, EndCluster );
	}
	else
	{
		it = FileSystem->GetClusterIterator( );
	}

	// ������� ��������� �����

	for ( it->First( ); !it->IsDone( ); it->Next( ) )
	{
		CurrentCluster = it->GetCurrent( );
		
		// ��������� ���� ���������� ������
		MySearchThread->BufferReadyEvent->SetEvent( );

		// ������� ��������� ����������� ������
		while ( MySearchThread->BufferCopiedEvent->WaitFor( WaitDelayMs ) != wrSignaled )
		{
		}
		MySearchThread->SetCurrentCluster( it->GetCurrentIndex( ) );
		MySearchThread->BufferCopiedEvent->ResetEvent( );
		if ( Terminated )
		{
			break;
		}
	}

	// ��������� �����
	MySearchThread->Terminate( );
	FileSystem->Close( );
	delete FileSystem;

}
// ---------------------------------------------------------------------------

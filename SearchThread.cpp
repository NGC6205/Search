// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
// ---------------------------------------------------------------------------
#include "SearchThread.h"
#include "Unit1.h"
//#include "Structures.h"
//#include "FileSystemClass.h"
//#include "Iterator.h"
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
// void __fastcall SearchThread::UpdateCaption()
// {
// Form1->Caption = "Updated in a thread";
// }
// ---------------------------------------------------------------------------
// typedef vector < string > VString;

__fastcall SearchThread::SearchThread(
	const vector < BYTE > * dataBufferPtr,
	int                     bytesPerCluster,
	bool                    CreateSuspended ) : TThread(
	                        CreateSuspended )
{
	FreeOnTerminate = true;

	BufferReadyEvent = new TEvent( NULL, true, false, "", false );
	BufferCopiedEvent = new TEvent( NULL, true, false, "", false );
	CurrentCluster = 0;
	OutBufferPtr = dataBufferPtr;
	BytesPerCluster = bytesPerCluster;
	DataBuffer = new BYTE[ bytesPerCluster ];
}

// ---------------------------------------------------------------------------
void __fastcall SearchThread::Execute( )
{
	// ---- Place thread code here ----
	while ( true )
	{
		// Ждать, пока не будет подготовлен буфер для копирования
		if ( BufferReadyEvent->WaitFor( WaitDelayMs ) == wrSignaled )
		{
			// Скопировать данные
			CopyData( );

			// Отпустить буфер
			BufferReadyEvent->ResetEvent( );
			BufferCopiedEvent->SetEvent( );

			// Запустить поиск
			SearchData( );
		}
		if ( Terminated )
		{
			break;
		}
	}
	// Удалить события
	delete BufferReadyEvent;
	delete BufferCopiedEvent;

	// Удалить буфер
	delete[ ]DataBuffer;
	Synchronize( & CompleteSearch );

}

// ---------------------------------------------------------------------------
void SearchThread::CopyData( )
{
	copy( OutBufferPtr->begin( ), OutBufferPtr->end( ), DataBuffer );
}

// ---------------------------------------------------------------------------
void SearchThread::SearchData( )
{
	// Провести поиск
	for ( int i = 0; i < vSignature.size( ); i++ )
	{
		if ( memcmp( DataBuffer, vSignature[ i ].signature.c_str( ), vSignature[ i ].signature.length( ) ) == 0 )
		{
			CurrentSignature = vSignature[ i ].signature;
			CurrentExtensionFile = vSignature[ i ].extensionFile;
			Synchronize( & AddMatch );
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall SearchThread::AddMatch( )
{
	PVirtualNode newNode = Form1->VirtualStringTree1->AddChild( Form1->VirtualStringTree1->RootNode );
	findFile * nodeData = ( findFile * )Form1->VirtualStringTree1->GetNodeData( newNode );
	nodeData->currentCluster = CurrentCluster;
	nodeData->signature = CurrentSignature;
	nodeData->extensionFile = CurrentExtensionFile;

}

// ---------------------------------------------------------------------------
void __fastcall SearchThread::CompleteSearch( )
{
	Application->MessageBoxW( L" Поиск завершен или остановлен !", L" Успешно ", MB_OK );
}
// ----------------------------------------------------------------------------

void SearchThread::SetCurrentCluster( int currentCluster )
{
	CurrentCluster = currentCluster;
	Synchronize( & ViewCluster );
}
// ---------------------------------------------------------------------------
void __fastcall SearchThread::ViewCluster( )
{
Form1 ->StatusLabel ->Caption=CurrentCluster;
}
// ---------------------------------------------------------------------------

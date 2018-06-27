// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "NTFS_class.h"
#include "Unit1.h"
#include "IteratorThread.h"
#include "SearchThread.h"
#include <stdio.h>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 * Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1( TComponent * Owner ) : TForm( Owner )
{
	VirtualStringTree1->NodeDataSize = sizeof( findFile );
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnSearchClick( TObject * Sender )
{
	// Поиск

	VirtualStringTree1->Clear( );
	myIteratorThread = new IteratorThread( 
	editPath->Text.c_str( ), 
	editBegin->Text.ToInt( ), 
	editEnd->Text.ToInt( ), 
	( FsType )cbFsType->ItemIndex,		
	chbRange->Checked, false );

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnStopClick( TObject * Sender )
{
	// Остановка поиска

	if ( myIteratorThread != NULL )
	{
		myIteratorThread->Terminate( );
	}

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTree1GetText(
	TBaseVirtualTree * Sender,
	PVirtualNode       Node,
	TColumnIndex       Column,
	TVSTTextType       TextType,
	UnicodeString &    CellText )

{
	if ( !Node )
	{
		MessageBoxW( NULL, L"Ошибка выбора Node", L"Ошибка", MB_OK );
		return;
	}
	findFile * nodeData = ( findFile * )Sender->GetNodeData( Node );
	switch ( Column )
	{
	case 0:
		CellText = nodeData->currentCluster;
		break;
	case 1:
		CellText = nodeData->signature.c_str( );
		break;
	case 2:
		CellText = nodeData->extensionFile.c_str( );
		break;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::chbRangeClick( TObject * Sender )
{
	if ( chbRange->Checked )
	{
		lblBegin->Enabled = true;
		lblEnd->Enabled = true;
		editBegin->Enabled = true;
		editEnd->Enabled = true;
	}
	else
	{
		lblBegin->Enabled = false;
		lblEnd->Enabled = false;
		editBegin->Enabled = false;
		editEnd->Enabled = false;
	}

}




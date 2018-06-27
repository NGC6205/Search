// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.Dialogs.hpp>

// ---------------------------------------------------------------------------
#include "IteratorThread.h"

// ---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published: // IDE-managed Components

	TButton * btnSearch;
	TButton * btnStop;
	TEdit * editPath;
	TVirtualStringTree * VirtualStringTree1;
	TEdit * editBegin;
	TEdit * editEnd;
	TLabel * lblPath;
	TLabel * lblBegin;
	TLabel * lblEnd;
	TLabel * lblFsType;
	TCheckBox * chbRange;
	TComboBox *cbFsType;
	TLabel *Label1;
	TLabel *StatusLabel;
	void __fastcall btnStopClick( TObject * Sender );
	void __fastcall VirtualStringTree1GetText(
		TBaseVirtualTree * Sender,
		PVirtualNode       Node,
		TColumnIndex       Column,
		TVSTTextType       TextType,
		UnicodeString &    CellText );
	void __fastcall chbRangeClick( TObject * Sender );
	void __fastcall btnSearchClick(TObject *Sender);

private: // User declarations
		public : // User declarations
	__fastcall TForm1( TComponent * Owner );

	IteratorThread * myIteratorThread;
} ;

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 * Form1;
// ---------------------------------------------------------------------------
#endif


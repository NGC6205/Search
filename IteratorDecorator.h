#ifndef IteratorDecoratorH
#define IteratorDecoratorH
// ---------------------------------------------------------------------------
#include "Iterator.h"
// ---------------------------------------------------------------------------
template < class Type >
class IteratorDecorator : public Iterator < Type >
{
protected:
	Iterator < Type > *It;

	IteratorDecorator( )
	{
	}

public:
	IteratorDecorator( Iterator < Type > * it )
	{
		It = it;
	}

	virtual ~IteratorDecorator( )
	{
		delete It;
	}

	virtual void First( )
	{
		It->First( );
	}

	virtual void Next( )
	{
		It->Next( );
	}

	virtual bool IsDone( ) const
	{
		return It->IsDone( );
	}

	virtual Type GetCurrent( )
	{
		return It->GetCurrent( );
	}

	virtual int GetCurrentIndex( ) const
	{
		return It->GetCurrentIndex( );
	}
} ;
// ---------------------------------------------------------------------------
#endif

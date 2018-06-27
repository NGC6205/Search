#ifndef IteratorH
#define IteratorH
// ---------------------------------------------------------------------------
template < class Type >
class Iterator
{
protected:

public:
	Iterator( )
	{
	} ;

	virtual ~Iterator( )
	{
	} ;
	virtual void First( ) = 0;
	virtual void Next( ) = 0;
	virtual bool IsDone( ) const = 0;
	virtual Type GetCurrent( ) = 0;
	virtual int GetCurrentIndex( ) const = 0;
} ;
// ---------------------------------------------------------------------------
#endif

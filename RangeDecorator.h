#ifndef RangeDecoratorH
#define RangeDecoratorH
// ---------------------------------------------------------------------------
#include "IteratorDecorator.h"
#include "Iterator.h"
#include "Structures.h"
// ---------------------------------------------------------------------------

class RangeDecorator : public IteratorDecorator < ClusterDisk >
{
protected:
	int BeginCluster;
	int EndCluster;

public:
	RangeDecorator(
		Iterator < ClusterDisk > * it,
		int                             beginCluster,
		int                             endCluster );

	virtual ~RangeDecorator( );
	virtual void First( );
	virtual void Next( );
	virtual bool IsDone( ) const ;
	virtual ClusterDisk GetCurrent( );
	virtual int GetCurrentIndex( ) const ;
} ;
// ---------------------------------------------------------------------------
#endif

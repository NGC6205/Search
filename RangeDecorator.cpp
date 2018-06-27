#include "RangeDecorator.h"

// ---------------------------------------------------------------------------
RangeDecorator::RangeDecorator(
	Iterator < ClusterDisk > * it,
	int                             beginCluster,
	int                             endCluster ) : IteratorDecorator < ClusterDisk > (
	                                it )
{
	BeginCluster = beginCluster;
	EndCluster = endCluster;
}

// ---------------------------------------------------------------------------
RangeDecorator::~RangeDecorator( )
{

}

// ---------------------------------------------------------------------------
void RangeDecorator::First( )
{
	for ( It->First( ); !It->IsDone( ); It->Next( ) )
	{
		if ( It->GetCurrentIndex( ) >= BeginCluster )
		{
			break;
		}
	}
}

// ---------------------------------------------------------------------------
void RangeDecorator::Next( )
{
	It->Next( );
}

// ---------------------------------------------------------------------------
bool RangeDecorator::IsDone( ) const
{
	if ( It->GetCurrentIndex( ) > EndCluster || It->IsDone( ) )
	{
		return true;
	}
	else
	{
		return It->IsDone( );
	}
}

// ---------------------------------------------------------------------------
ClusterDisk RangeDecorator::GetCurrent( )
{
	return It->GetCurrent( );
}

// ---------------------------------------------------------------------------
int RangeDecorator::GetCurrentIndex( ) const
{
	return It->GetCurrentIndex( );
}
// ---------------------------------------------------------------------------

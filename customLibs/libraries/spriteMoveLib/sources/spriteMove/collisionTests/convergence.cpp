#include "spriteMove/collisionTests/convergence.h"

bool convergeOnGivenAxis(int axisNorm, double locationCoordinate, double destinationCoordinate)
{
	if( locationCoordinate == destinationCoordinate )
	{
		return true;
	}
	else if( locationCoordinate < destinationCoordinate && axisNorm > 0 )
	{
		return true;
	}
	else if( locationCoordinate > destinationCoordinate && axisNorm < 0 )
	{
		return true;
	}
	else{
		return false;
	}
}
#include "spriteMove/collisionTests/affineFunction.h"
#include "spriteMove/objectMove.h"

AffineFunction::AffineFunction():
	dirCoef{ 1 },
	originCoord{ 0 },
	xCoord{ 0 },
	isFunctionValid{ false }
{
	
}

AffineFunction::AffineFunction(const spriteMove::ObjectMoving& object)
{
	computeData(object);
}

AffineFunction::AffineFunction(double newDirCoef, double newOriginCoord):
	dirCoef{ newDirCoef },
	originCoord{ newOriginCoord },
	xCoord{ 0 },
	isFunctionValid{ true }
{
	
}

void AffineFunction::computeData(const spriteMove::ObjectMoving& object)
{
	if( object.get_x_norm() != 0 )
	{
		dirCoef = static_cast<double>(object.get_y_norm() ) / static_cast<double>(object.get_x_norm() );
		originCoord = object.getPosition().y - dirCoef * object.getPosition().x;
		isFunctionValid = true;
	}
	else{
		dirCoef = 0;
		originCoord = 0;
		xCoord = object.getPosition().x;
		isFunctionValid = false;
	}
}

bool AffineFunction::operator== ( const AffineFunction& toCompare ) const
{
	if( isFunctionValid )
	{
		return dirCoef == toCompare.dirCoef && originCoord == toCompare.originCoord;
	}
	else{
		return xCoord == toCompare.xCoord;
	}
}
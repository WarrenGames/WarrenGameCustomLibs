#include "spriteMove/collisionTests/objectsCollisionInfos.h"
#include "spriteMove/collisionTests/functionsCollisionsTests.h"
#include "spriteMove/collisionTests/convergence.h"
#include "spriteMove/collisionTests/affineFunction.h"
#include "spriteMove/objectMove.h"
#include <cassert>

spriteMove::CollisionInfos::CollisionInfos():
	doesObjectsCollide{ false }
{
	
}

spriteMove::CollisionInfos::CollisionInfos(const spriteMove::ObjectMoving& obj1, const spriteMove::ObjectMoving& obj2):
	doesObjectsCollide{ false }
{
	checkCollisionBetweenObjects(obj1, obj2);
}

bool spriteMove::CollisionInfos::collide() const
{
	return doesObjectsCollide;
}

const AccurCoords& spriteMove::CollisionInfos::getCollisionPoint() const
{
	return collisionPoint;
}

double spriteMove::CollisionInfos::getFunc1_coefDir() const
{
	return obj1_func.dirCoef;
}

double spriteMove::CollisionInfos::getFunc2_coefDir() const
{
	return obj2_func.dirCoef;
}

double spriteMove::CollisionInfos::getFunc1_originCoord() const
{
	return obj1_func.originCoord;
}

double spriteMove::CollisionInfos::getFunc2_originCoord() const
{
	return obj2_func.originCoord;
}

void spriteMove::CollisionInfos::checkCollisionBetweenObjects(const spriteMove::ObjectMoving& obj1, const spriteMove::ObjectMoving& obj2)
{
	startIntersectionTest(obj1, obj2);
	checkIntersectionAccordingToVectorsDirections(obj1, obj2);
}

void spriteMove::CollisionInfos::setNoCollision()
{
	collisionPoint.x = 0;
	collisionPoint.y = 0;
	doesObjectsCollide = false;
}

void spriteMove::CollisionInfos::startIntersectionTest(const spriteMove::ObjectMoving& obj1, const spriteMove::ObjectMoving& obj2)
{
	obj1_func.computeData(obj1);
	obj2_func.computeData(obj2);
	if( obj1.getPosition().x == obj2.getPosition().x && obj1.getPosition().y == obj2.getPosition().y )
	{
		//If points have from the start the same coordinates. 
		doesObjectsCollide = true;
		collisionPoint = obj1.getPosition();
	}
	else
	{
		if( obj1_func.isFunctionValid && obj2_func.isFunctionValid && obj1_func.dirCoef == obj2_func.dirCoef && obj1_func.originCoord != obj2_func.originCoord )
		{
			//If affine functions are parallel but not parallel with y axis and with different coordinates at the origin.
			setNoCollision();
		}
		else if( false == obj1_func.isFunctionValid && false == obj2_func.isFunctionValid && obj1_func.xCoord != obj2_func.xCoord )
		{
			//If affine function are parallel to the y axis but with different 'x' equation parameter.
			setNoCollision();
		}
		else
		{
			if( obj1_func.isFunctionValid && obj2_func.isFunctionValid )
			{
				collisionPoint.x = getXCollisionCoords(obj1_func, obj2_func);
				collisionPoint.y = getYCollisionCoords(obj1_func, obj2_func);
				doesObjectsCollide = true;
			}
			else if( obj1_func.isFunctionValid != obj2_func.isFunctionValid )
			{
				determineCollisionWithOneIllFormedFunction();
			}
			else{
				setNoCollision();
			}
		}
	}
}

void spriteMove::CollisionInfos::determineCollisionWithOneIllFormedFunction()
{
	assert( obj1_func.isFunctionValid || obj2_func.isFunctionValid );
	if( false == obj1_func.isFunctionValid && obj2_func.isFunctionValid )
	{
		doesObjectsCollide = true;
		collisionPoint.x = obj1_func.xCoord;
		collisionPoint.y = obj2_func.dirCoef * obj1_func.xCoord + obj2_func.originCoord;
	}
	else if( obj1_func.isFunctionValid && false == obj2_func.isFunctionValid )
	{
		doesObjectsCollide = true;
		collisionPoint.x = obj2_func.xCoord;
		collisionPoint.y = obj1_func.dirCoef * obj2_func.xCoord + obj1_func.originCoord;
	}
}

void spriteMove::CollisionInfos::checkIntersectionAccordingToVectorsDirections(const spriteMove::ObjectMoving& obj1, const spriteMove::ObjectMoving& obj2)
{
	if( convergeOnGivenAxis(obj1.get_x_norm(), obj1.getPosition().x, collisionPoint.x)
		&& convergeOnGivenAxis(obj1.get_y_norm(), obj1.getPosition().y, collisionPoint.y)
		&& convergeOnGivenAxis(obj2.get_x_norm(), obj2.getPosition().x, collisionPoint.x)
		&& convergeOnGivenAxis(obj2.get_y_norm(), obj2.getPosition().y, collisionPoint.y) )
	{
		doesObjectsCollide = true;
	}
	else{
		doesObjectsCollide = false;
	}
}
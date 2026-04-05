#ifndef GAME_COMMON_COMPUTER_PLAYER_OBJECTS_COLLISION_INFOS_H
#define GAME_COMMON_COMPUTER_PLAYER_OBJECTS_COLLISION_INFOS_H

#include "spriteMove/collisionTests/affineFunction.h"
#include "customTypes/positionTypes.h"

namespace spriteMove{ 
	class ObjectMoving;

class CollisionInfos
{
private:
	bool doesObjectsCollide;
	AffineFunction obj1_func;
	AffineFunction obj2_func;
	AccurCoords collisionPoint;
	
public:
	CollisionInfos();
	CollisionInfos(const spriteMove::ObjectMoving& obj1, const spriteMove::ObjectMoving& obj2);
	~CollisionInfos() = default;
	CollisionInfos( const CollisionInfos& ) = default;
	CollisionInfos& operator= ( const CollisionInfos& ) = default;
	CollisionInfos( CollisionInfos&& ) = default;
	CollisionInfos& operator= ( CollisionInfos&& ) = default;
	
	bool collide() const;
	const AccurCoords& getCollisionPoint() const;
	double getFunc1_coefDir() const;
	double getFunc2_coefDir() const;
	double getFunc1_originCoord() const;
	double getFunc2_originCoord() const;
	
	void checkCollisionBetweenObjects(const spriteMove::ObjectMoving& obj1, const spriteMove::ObjectMoving& obj2);
	void startIntersectionTest(const spriteMove::ObjectMoving& obj1, const spriteMove::ObjectMoving& obj2);
	
private:
	void setNoCollision();
	void determineCollisionWithOneIllFormedFunction();
	void checkIntersectionAccordingToVectorsDirections(const spriteMove::ObjectMoving& obj1, const spriteMove::ObjectMoving& obj2);
};

}

#endif //GAME_COMMON_COMPUTER_PLAYER_OBJECTS_COLLISION_INFOS_H
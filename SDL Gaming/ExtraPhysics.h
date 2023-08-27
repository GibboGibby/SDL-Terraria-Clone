#pragma once
#include "PhysicsManager.h"
#include "Graphics.h"
#include "PointCollider.h"

namespace Physics
{
	bool RaycastOld(Vector2 origin, Vector2 direction, float distance = -1, PhysicsEntity* current = NULL, PhysicsManager::CollisionFlags layers = PhysicsManager::CollisionFlags::None)
	{
		if (distance == -1) distance = 9999;
		Graphics::Instance()->DrawLine(origin, origin + (direction * distance));
		Vector2 position = origin;

		for (float i = 0; i < distance; i++)
		{
			//temp->Position() = origin + direction.Normalized();
			Collider* temp = new PointCollider(position);
			bool collision = PhysicsManager::Instance()->CollisionCheck(temp, current);
			if (collision)
			{
				//printf("Raycast has hit something\n");
				return true;
			}
			position = origin + (direction * i);
		}
		return false;
	}



	bool Raycast(Vector2 origin, Vector2 direction, float distance, PhysicsEntity* current = NULL)
	{
		return RaycastOld(origin, direction, distance, current);
	}
}



struct RaycastHit
{
	PhysicsEntity* other;
};
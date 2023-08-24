#pragma once
#include "PhysicsManager.h"
#include "Graphics.h"
#include "PointCollider.h"

namespace Physics
{


	bool Raycast(Vector2 origin, Vector2 direction, float distance = -1, PhysicsManager::CollisionFlags layers = PhysicsManager::CollisionFlags::None)
	{
		if (distance == -1) distance = 9999;
		Graphics::Instance()->DrawLine(origin, origin + (direction * distance));
		Vector2 position = origin;
		for (int i = 0; i < distance; i++)
		{
			//temp->Position() = origin + direction.Normalized();
			Collider* temp = new PointCollider(position);
			bool collision = PhysicsManager::Instance()->CollisionCheck(temp);
			if (collision)
			{
				printf("Raycast has hit something\n");
				return true;
			}
			position += direction;
		}
		return false;
	}


}
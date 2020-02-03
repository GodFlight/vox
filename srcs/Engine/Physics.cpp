#include "Engine/Physics.h"
#include "Engine/Game.h"

Physics::Physics(Game* game)
{
	_game = game;
	_world = _game->GetWorld();
}

Physics::RayCastHitInfo Physics::RayCast(const glm::vec3 _position, glm::vec3 direction, const float rayLength, float rayStep)
{
	RayCastHitInfo ray;
	glm::vec3 tmpDirection;

	if (rayStep >= rayLength)
		rayStep = rayLength * 0.25f;

	direction = glm::normalize(direction);
	ray.hitRayPos = glm::vec3(0.f, 0.f, 0.f);
	for (float step = 0.f; step <= rayLength; step += rayStep)
	{
		ray.lastRayStep = ray.hitRayPos;
		tmpDirection = direction * step;
		ray.hitRayPos = _position + tmpDirection;
		ray.hitBlock = _world->GetBlock(ray.hitRayPos);
		if (ray.hitBlock != Block::Air)
		{
			ray.hit = true;
			ray.distance = step;
			return ray;
		}
	}
	ray.hitRayPos = glm::vec3(INFINITY, INFINITY, INFINITY);
	ray.lastRayStep = glm::vec3(INFINITY, INFINITY, INFINITY);
	ray.hit = false;
	return ray;
}

Physics::CollisionInfo Physics::CheckCollision(const glm::vec3& direction, const glm::vec3& upperBody, const glm::vec3& middleBody,
													const glm::vec3& lowerBody, const glm::vec3& _position, const float& avoidBlockDistance)
{
	CollisionInfo col;
	col.isCollision = false;
	col.sideNormal = glm::vec3(1.f, 0.f, 1.f);

	if (!direction.x && !direction.z)
		return col;

	glm::vec3 tmpPosition = _position;
	tmpPosition.x = glm::abs(tmpPosition.x);
	tmpPosition.z = glm::abs(tmpPosition.z);
	float distX = tmpPosition.x - floorf(tmpPosition.x);
	float distZ = tmpPosition.z - floorf(tmpPosition.z);
	distX = (distX > 0.5f ? 1.f - distX : distX);
	distZ = (distZ > 0.5f ? 1.f - distZ : distZ);

	if (distX > avoidBlockDistance && distZ > avoidBlockDistance)
		return col;

	if (distX < avoidBlockDistance)
	{
		glm::vec3 offset = glm::vec3(direction.x < 0 ? -0.5f : 0.5f, 0.f, 0.f);
		Block blockX = _world->GetBlock(lowerBody + offset);
		if (blockX != Block::Air)
		{
			col.isCollision = true;
			col.sideNormal.z = 0.f;
		}
		blockX = _world->GetBlock(middleBody + offset);
		if (blockX != Block::Air)
		{
			col.isCollision = true;
			col.sideNormal.z = 0.f;
		}
		blockX = _world->GetBlock(upperBody + offset);
		if (blockX != Block::Air)
		{
			col.isCollision = true;
			col.sideNormal.z = 0.f;
		}
	}
	if (distZ < avoidBlockDistance)
	{
		glm::vec3 offset = glm::vec3(0.f, 0.f, direction.z < 0 ? -0.5f : 0.5f);
		Block blockZ = _world->GetBlock(lowerBody + offset);
		if (blockZ != Block::Air)
		{
			col.isCollision = true;
			col.sideNormal.x = 0.f;
		}
		blockZ = _world->GetBlock(middleBody + offset);
		if (blockZ != Block::Air)
		{
			col.isCollision = true;
			col.sideNormal.x = 0.f;
		}
		blockZ = _world->GetBlock(upperBody + offset);
		if (blockZ != Block::Air)
		{
			col.isCollision = true;
			col.sideNormal.x = 0.f;
		}
	}
	return col;
}

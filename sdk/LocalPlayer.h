#pragma once
#include "../sdk/entity.h"

namespace LocalPlayer {
	CEntity* Get();
	int GetClosestEnemy();
	int GetEnemyInCrosshair();
};
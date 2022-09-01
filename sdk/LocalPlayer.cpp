#include <Windows.h>
#include <iostream>

#include "../src/offsets.h"

#include "LocalPlayer.h"
#include "clientEntitylist.h"

CEntity* LocalPlayer::Get() {
	// 1 = first item of the entitylist = locaplayer
	return entityList->GetClientEntity(1);
}

int LocalPlayer::GetClosestEnemy() {
	int closest = -1;
	for (int i = 1; i <= 64; i++)
	{
		CEntity* ent = entityList->GetClientEntity(i);
		if (ent != nullptr) {
			// sanity check
			CEntity* LocalPlayer = LocalPlayer::Get();

			if (LocalPlayer != ent && ent->GetTeamNum() != LocalPlayer->GetTeamNum() && !ent->GetDormant() )
			{
				Vector3 epos = ent->GetPosition();
				Vector3 pos = LocalPlayer->GetPosition();
				Vector3 delta = { epos.x - pos.x, epos.y - pos.y, epos.z - pos.z };

				if (sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) < 500) {
					closest = i;
				}
			}
		}
	}
	return closest;
}

int LocalPlayer::GetEnemyInCrosshair() {
	return *reinterpret_cast<int*>(entityList->GetClientEntity(1) + m_iCrosshairId);
}
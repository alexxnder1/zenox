#pragma once
#include "../src/vec.h"

class CEntity
{
public:
	const int& GetHealth();
	const Vector3& GetPosition();
	const int& GetTeamNum();
	const int& GetDormant();
	const bool& isAlive();
	const int& GetFlags();
	
	Vector3 GetBonePos(int bone);
	Vector3* GetEyePos();
};
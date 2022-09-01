#include <windows.h>
#include "entity.h"
#include <iostream>
#include "../src/offsets.h"
#include "../sdk/clientEntitylist.h"
#include "../src/mat3x4.h"

const int& CEntity::GetHealth() {
	return *reinterpret_cast<int*>((uintptr_t)this + m_iHealth);
}

const Vector3& CEntity::GetPosition() {
	return *reinterpret_cast<Vector3*>((uintptr_t)this + m_vecOrigin);
}

const int& CEntity::GetTeamNum() {
	return *reinterpret_cast<int*>((uintptr_t)this + m_iTeamNum);
}

const int& CEntity::GetDormant() {
	return *reinterpret_cast<int*>((uintptr_t)this + m_bDormant);
}

const bool& CEntity::isAlive() {
	return ((uintptr_t)this->GetHealth() > 0) ? true : false;
}

const int& CEntity::GetFlags() {
	return *reinterpret_cast<int*>((uintptr_t)this + 0x104);
}

Vector3 CEntity::GetBonePos(int bone) {
	Vector3 bonePos;

	uintptr_t matrice = *reinterpret_cast<uintptr_t*>((uintptr_t)this + m_dwBoneMatrix);
	bonePos.x = *reinterpret_cast<float*>(matrice + 0x30 * bone + 0x0C);
	bonePos.y = *reinterpret_cast<float*>(matrice + 0x30 * bone + 0x1C);
	bonePos.z = *reinterpret_cast<float*>(matrice + 0x30 * bone + 0x2C);
	return bonePos;
}

Vector3* CEntity::GetEyePos() {
	return reinterpret_cast<Vector3*>((uintptr_t)this + m_vecOrigin + m_vecViewOffset);
}
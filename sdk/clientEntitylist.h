#pragma once
#include "entity.h"
#include "../src/interfaces.h"

class IClientEntityList
{
public:
	// Get IClientNetworkable interface for specified entity
	virtual void * GetClientNetworkable(int entnum) = 0;
	virtual void* GetClientNetworkableFromHandle(unsigned long hEnt) = 0;
	virtual void* GetClientUnknownFromHandle(unsigned long hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual CEntity* GetClientEntity(int entnum) = 0;
	virtual CEntity* GetClientEntityFromHandle(unsigned long hEnt) = 0;

	// Returns number of entities currently in use
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	// Returns highest index actually used
	virtual int					GetHighestEntityIndex(void) = 0;

	// Sizes entity list to specified size
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
};

inline IClientEntityList* entityList = (IClientEntityList*)interfaces::get("client.dll", "VClientEntityList003");
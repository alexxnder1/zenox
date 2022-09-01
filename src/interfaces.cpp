#include <windows.h>
#include "interfaces.h"

typedef void* (__cdecl* tCreateInterface) (const char* dllname, int* returnCode);
void* interfaces::get(const char* dllname, const char* interfaceName) {
	HMODULE handle = GetModuleHandle(dllname);
	if (!handle)
		return (void*)0;

	tCreateInterface CreateInterface = (tCreateInterface)(GetProcAddress(handle, "CreateInterface"));
	
	if (!CreateInterface)
		return (void*)0;

	return (void*)CreateInterface(interfaceName, 0);;
}
#include <Windows.h>

#include "Feature.h"
#include "ForceLodA.h"

void Init()
{
	Config::Init();

	*Game::FrontSteerAngle = Config::Global.FrontSteerAngle;
	
	if (Config::Global.ExpandMemoryPools)
	{
		injector::WriteMemory<int>(0x0065F761, 0x2C8000, true); // GManager::GetVaultAllocator
		injector::WriteMemory<int>(0x0065F781, 0x2C8000, true); // 

		injector::WriteMemory<DWORD>(0x00A58F9C, 0x0BE6E0, true); // CarLoaderPoolSizes
		injector::WriteMemory<DWORD>(0x00A60DE4, 0x01CC00, true); // FEngMemoryPoolSize 

		injector::WriteMemory<DWORD>(0x00453016, 0x7D000, true); // ePolySlotPool
	}

	InitForceLodA();
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);

		if (strstr((const char*)(base + (0xA49742 - base)), "ProStreet08Release.exe"))
			Init();

		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use a NOCD v1.1 NFS.exe.", "NFSPS Extra Options", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;

}
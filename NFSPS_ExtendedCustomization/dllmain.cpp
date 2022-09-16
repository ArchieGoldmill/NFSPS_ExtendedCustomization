#include <Windows.h>

#include "Feature.h"
#include "ForceLodA.h"
#include "Stance.h"

void Init()
{
	Config::Init();

	*Game::FrontSteerAngle = Config::Global.FrontSteerAngle;

	if (Config::Global.ExpandMemoryPools)
	{
		injector::WriteMemory<int>(0x0065F761, 0x164000 * 2, true); // GManager::GetVaultAllocator
		injector::WriteMemory<int>(0x0065F781, 0x164000 * 2, true); // 

		injector::WriteMemory<DWORD>(0x00A58F9C, 0x0BB800 * 2, true); // FEngMemoryPoolSize
		injector::WriteMemory<DWORD>(0x00A60DE4, 0x13880 * 2, true); // CarLoaderPoolSizes
	}

	if (Config::Global.InfiniteTuningSliders)
	{
		injector::MakeNOP(0x005C192C, 8, true);
		injector::MakeNOP(0x005C18DC, 2, true);
		injector::MakeNOP(0x005C185A, 2, true);
		injector::MakeJMP(0x005C18E6, 0x005C19AC, true);
	}

	InitForceLodA();
	InitStance();
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
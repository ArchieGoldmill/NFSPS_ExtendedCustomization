#include <Windows.h>

#include "Feature.h"
#include "ForceLodA.h"
#include "Stance.h"
#include "InfiniteSliders.h"
#include "ReplacementTextures.h"

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

	InitForceLodA();
	InitStance();
	InitInfiniteSliders();
	InitReplacementTextures();
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if (nt->OptionalHeader.AddressOfEntryPoint + 0x400000 == 0x00828c25)
		{
			Init();
		}
		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use a NOCD v1.1 NFS.exe.", "NFSPS Extended Customization", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;

}
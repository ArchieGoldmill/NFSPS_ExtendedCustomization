#include <Windows.h>

#include "Config.h"
#include "ForceLodA.h"

void Init()
{
	Config::Init();

	*Game::FrontSteerAngle = Config::Global.FrontSteerAngle;

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
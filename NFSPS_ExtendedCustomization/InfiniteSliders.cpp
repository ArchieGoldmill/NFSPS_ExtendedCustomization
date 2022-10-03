#include "Feature.h"
#include "InfiniteSliders.h"


void __declspec(naked) AutosculptSliderCave()
{
	static constexpr auto cExit = 0x007E7E7F;
	static constexpr float AutosculptSliderValue = 2.56f;

	_asm
	{
		fld dword ptr[AutosculptSliderValue];
		fstp dword ptr[esp + 04];
		jmp cExit;
	}
}

void InitInfiniteSliders()
{
	if (Config::Global.InfiniteTuningSliders)
	{
		injector::MakeNOP(0x005C192C, 8, true);
		injector::MakeNOP(0x005C18DC, 2, true);
		injector::MakeNOP(0x005C185A, 2, true);
		injector::MakeJMP(0x005C18E6, 0x005C19AC, true);
	}

	if (Config::Global.InfiniteAutosculptSliders)
	{
		injector::MakeNOP(0x00757290, 2, true);
		injector::MakeJMP(0x007E7E79, AutosculptSliderCave, true);
	}
}
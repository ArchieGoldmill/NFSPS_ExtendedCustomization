#include "Stance.h"
#include "Feature.h"

float __stdcall GetTrackWidth(int** carRenderInfo, int wheel, int original)
{
	float result = original / 1000.0f;
	if (carRenderInfo)
	{
		int* rideInfo = carRenderInfo[0xFC];
		if (rideInfo)
		{
			int* part = rideInfo + 0x36;

			float* ptr = (float*)Game::DBCarPart_GetAppliedAttributeIParam(part, wheel < 2 ? FRONT_TIRE_OFFSET : REAR_TIRE_OFFSET, 0);
			if (ptr)
			{
				result = ptr[1];
			}
		}
	}

	return result;
}

void __declspec(naked) TrackWidthCave()
{
	static constexpr auto hExit = 0x00773D44;

	__asm
	{
		pushad;
		push[esp + 0x34];
		push ebp;
		push[esp + 0x2C];
		call GetTrackWidth;
		popad;

		mov eax, [esp + 0x10];
		jmp hExit;
	}
}

void InitStance()
{
	injector::MakeJMP(0x00773D3C, TrackWidthCave, true);
	injector::MakeNOP(0x00773D4F, 6, true);
}
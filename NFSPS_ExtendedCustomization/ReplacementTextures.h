#pragma once
#include "Feature.h"

struct ReplacementTexturesEntry
{
	Hash Old;
	Hash New;
	void* Texture;
};

void __fastcall UpdateReplacementTextures(UINT** carRenderInfo)
{
	Game::CarRenderInfo_UpdateReplacementTextures(carRenderInfo);

	UINT* rideInfo = carRenderInfo[0xFC];
	if (rideInfo)
	{
		int tire = rideInfo[0x26C] + 1;
		if (tire > 1)
		{
			char tireStyle[128];

			sprintf(tireStyle, "TIRE_STYLE%02d", tire);
			auto newHash = Game::StringHash(tireStyle);
			if (Game::GetTextureInfo(newHash, 0, 0))
			{
				auto tireEntry = (ReplacementTexturesEntry*)(carRenderInfo + 0x171);
				tireEntry->Old = TIRE_STYLE01;
				tireEntry->New = newHash;
				tireEntry->Texture = 0;

				tireEntry = (ReplacementTexturesEntry*)(carRenderInfo + 0x174);
				tireEntry->Old = TIRE_STYLE77;
				tireEntry->New = newHash;
				tireEntry->Texture = 0;

				sprintf(tireStyle, "TIRE_STYLE%02d_N", tire);
				newHash = Game::StringHash(tireStyle);
				if (!Game::GetTextureInfo(newHash, 0, 0))
				{
					newHash = PLAIN_NORMAL;
				}

				tireEntry = (ReplacementTexturesEntry*)(carRenderInfo + 0x177);
				tireEntry->Old = TIRE_STYLE01_N;
				tireEntry->New = newHash;
				tireEntry->Texture = 0;
			}
		}
	}
}

void __stdcall AttachReplacementTable(void* model, void* originalTable, UINT carRenderInfo, int partId)
{
	auto table = originalTable;
	if (partId == 0x5F || partId == 0x60)
	{
		table = (void*)(carRenderInfo + 0x5A4);
	}

	Game::eModel_AttachReplacmentTable(model, table);
}

void __declspec(naked) AttachReplacementTableCave()
{
	static constexpr auto hExit = 0x0077DB18;

	__asm
	{
		push[esp + 0x24];
		push[esp + 0x20];
		push ebx;
		push ecx;
		call AttachReplacementTable;
		jmp hExit;
	}
}

void InitReplacementTextures()
{
	injector::MakeCALL(0x0078BE44, UpdateReplacementTextures);
	injector::MakeCALL(0x0078C9F9, UpdateReplacementTextures);

	injector::MakeJMP(0x0077DB12, AttachReplacementTableCave);
}
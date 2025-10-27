#pragma once
#include "Feature.h"

struct ReplacementTexturesEntry
{
	Hash Old;
	Hash New;
	void* Texture;
};

void __stdcall UpdateReplacementTextures(UINT** carRenderInfo)
{
	UINT* rideInfo = carRenderInfo[0xFC];
	if (rideInfo)
	{
		int tire = rideInfo[0x26C] + 1;

		char tireStyle[128];

		sprintf(tireStyle, "TIRE_STYLE%02d", tire);
		auto newHash = Game::StringHash(tireStyle);
		if (Game::GetTextureInfo(newHash, 0, 0))
		{
			auto tireEntry = (ReplacementTexturesEntry*)(carRenderInfo + 0x171);
			tireEntry->Old = TIRE_STYLE01;
			tireEntry->New = newHash;
			tireEntry->Texture = 0;

			auto tireEntryN = (ReplacementTexturesEntry*)(carRenderInfo + 0x174);
			tireEntryN->Old = TIRE_STYLE01_N;
			sprintf(tireStyle, "TIRE_STYLE%02d_N", tire);
			tireEntryN->New = Game::StringHash(tireStyle);
			tireEntryN->Texture = 0;
		}
	}
}

void __declspec(naked) ReplacementTexturesCave()
{
	static constexpr auto hExit = 0x00787F45;

	__asm
	{
		pushad;
		push esi;
		call UpdateReplacementTextures;
		popad;

		mov esi, [esi + 0x00004544];
		jmp hExit;
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
	injector::MakeJMP(0x00787F3F, ReplacementTexturesCave);
	injector::MakeJMP(0x0077DB12, AttachReplacementTableCave);
}
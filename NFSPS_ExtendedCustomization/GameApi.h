#pragma once

typedef unsigned int Hash;
const Hash FRONT_TIRE_OFFSET = 0xFDE70341;
const Hash REAR_TIRE_OFFSET = 0x2FC42D62;

namespace Game
{
	static float* FrontSteerAngle = (float*)0x00A8918C;

	static auto StringHash = (Hash(__cdecl*)(const char*))0x00436680;
	static auto StringHash1 = (Hash(__cdecl*)(const char*, Hash))0x004366B0;

	static auto DBCarPart_GetAppliedAttributeIParam = (void* (__thiscall*)(void*, Hash, int))0x00754CD0;
}
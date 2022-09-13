#pragma once

typedef unsigned int Hash;

namespace Game
{
	static float* FrontSteerAngle = (float*)0x00A8918C;

	static auto StringHash = (Hash(__cdecl*)(const char*))0x00436680;
	static auto StringHash1 = (Hash(__cdecl*)(const char*, Hash))0x004366B0;
}
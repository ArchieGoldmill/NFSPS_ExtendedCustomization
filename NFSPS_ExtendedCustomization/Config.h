#pragma once
#include "GameApi.h"
#include <string>

namespace Config
{
	class _Common
	{
	public:
		bool ForceLodA;
	};

	class _Global : public _Common
	{
	public:
		float FrontSteerAngle;
	};

	class _Car : public _Common
	{
	public:
		std::string Name;
		Hash NameHash;
	};

	extern _Global Global;

	_Car* GetCarByHash(Hash nameHash);
	void Init();
}
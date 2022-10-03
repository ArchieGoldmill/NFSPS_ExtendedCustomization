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
		bool ExpandMemoryPools;
		bool InfiniteTuningSliders;
		bool InfiniteAutosculptSliders;
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
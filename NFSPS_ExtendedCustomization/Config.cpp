#include "Config.h"
#include "includes/IniReader/IniReader.h"
#include <stdlib.h>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

namespace Config
{
	_Global Global;
	std::vector<_Car*> Cars;

	_Car* GetCarByHash(Hash nameHash)
	{
		for (_Car* i : Cars)
		{
			if (nameHash == i->NameHash)
			{
				return i;
			}
		}

		return NULL;
	}

	void InitCommon(_Common* commonCfg, CIniReader& iniReader)
	{
		commonCfg->ForceLodA = iniReader.ReadInteger("GENERAL", "ForceLodA", 0) == 1;
	}

	void InitCars()
	{
		std::string path = "ExtendedCustomizationCars";
		fs::directory_iterator iterator;
		try
		{
			iterator = fs::directory_iterator(path);
		}
		catch (...)
		{
			return;
		}

		for (const auto& entry : iterator)
		{
			auto path = entry.path();
			CIniReader iniReader(path.string().c_str());

			auto carCfg = new _Car();
			carCfg->Name = path.filename().string();
			carCfg->NameHash = Game::StringHash(carCfg->Name.c_str());
			InitCommon(carCfg, iniReader);
			Cars.push_back(carCfg);
		}
	}

	void Init()
	{
		CIniReader iniReader("NFSPSExtendedCustomization.ini");
		InitCommon(&Global, iniReader);
		Global.FrontSteerAngle = iniReader.ReadFloat("GENERAL", "FrontSteerAngle", 340);
		Global.ExpandMemoryPools = iniReader.ReadInteger("GENERAL", "ExpandMemoryPools", 0) == 1;
		Global.InfiniteTuningSliders = iniReader.ReadInteger("GENERAL", "InfiniteTuningSliders", 0) == 1;

		InitCars();
	}
}
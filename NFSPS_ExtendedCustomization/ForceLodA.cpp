#include "Feature.h"
#include "ForceLodA.h"

void MakeLod(char* str, char lod)
{
	int len = strlen(str);
	str[len - 1] = 'A';
}

Hash __cdecl ChangePartString(char* str, Hash modelHash)
{
	auto carConfig = Config::GetCarByHash(modelHash);
	bool carForceLodA = carConfig && carConfig->ForceLodA;
	if (Config::Global.ForceLodA || carForceLodA)
	{
		MakeLod(str, 'A');
	}

	return Game::StringHash1(str, modelHash);
}

void InitForceLodA()
{
	injector::MakeCALL(0x00777D11, ChangePartString, true);
}
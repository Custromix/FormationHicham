#include "HichamBlueprintFunctionLibrary.h"

#include "Materials/MaterialInstanceConstant.h"

bool UHichamBlueprintFunctionLibrary::SetStaticSwitchParameterValue(UMaterialInstance* Instance, FName ParameterName, bool Value)
{
	if (!Instance)
		return false;
	
	UMaterialInstanceConstant* MIC = Cast<UMaterialInstanceConstant>(Instance);
	if (!MIC)
		return false;
	
	FStaticParameterSet StaticParams = MIC->GetStaticParameters();

	bool bFound = false;

	for (FStaticSwitchParameter& SwitchParam : StaticParams.StaticSwitchParameters)
	{
		if (SwitchParam.ParameterInfo.Name == ParameterName)
		{
			SwitchParam.Value = Value;
			SwitchParam.bOverride = true;
			bFound = true;
			break;
		}
	}

	if (!bFound)
	{
		return false;
	}

	MIC->UpdateStaticPermutation(StaticParams);
	MIC->PostEditChange();

	return true;
}

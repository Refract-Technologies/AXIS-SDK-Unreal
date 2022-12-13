// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UMG.h"
#include "UMGStyle.h"
#include "Slate/SObjectWidget.h"
#include "IUMGModule.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Core/Public/Misc/ConfigCacheIni.h"

class FAxis : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
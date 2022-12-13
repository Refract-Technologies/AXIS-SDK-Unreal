// Fill out your copyright notice in the Description page of Project Settings.

#include "Axis.h"
#include "Modules/ModuleManager.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "Developer/Settings/Public/ISettingsSection.h"
#include "Developer/Settings/Public/ISettingsContainer.h"

#define LOCTEXT_NAMESPACE "FAxis"

void FAxis::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	

}

void FAxis::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

}
#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAxis, Axis)
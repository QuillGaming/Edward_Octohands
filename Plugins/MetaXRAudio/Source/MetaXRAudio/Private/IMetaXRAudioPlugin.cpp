// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.
// Copyright Epic Games, Inc. All Rights Reserved.

#include "IMetaXRAudioPlugin.h"
#include "AudioDevice.h"
#include "Features/IModularFeatures.h"
#include "MetaXRAudioLogging.h"
#include "MetaXRAudioPlatform.h"
#include "Misc/CoreDelegates.h"
#ifdef META_NATIVE_UNREAL_PLUGIN
#include "MetaXRAudioContextManager.h"
#endif

void MetaXRAudioModulePreEngineExit() {
#ifdef META_WWISE_UNREAL_PLUGIN
  const FName WwiseSoundEngineModuleName("WwiseSoundEngine");
  FModuleManager& ModuleManager = FModuleManager::Get();
  IModuleInterface* ModuleInterface = ModuleManager.GetModule(WwiseSoundEngineModuleName);
  if (ModuleInterface == nullptr) {
    METAXR_AUDIO_LOG_ERROR(
        "[FMetaXRAudioPlugin::OnPreEngineExit] Wwise is not installed.\
            This plugin is the MetaXRAudio Wwise integration. Install Wwise or Use native distribution of this plugin");
    return;
  }
  ModuleInterface->ShutdownModule();
#endif
}

void FMetaXRAudioPlugin::StartupModule() {
  FMetaXRAudioLibraryManager::Get().Initialize();
#ifdef META_NATIVE_UNREAL_PLUGIN
  IModularFeatures::Get().RegisterModularFeature(FMetaXRSpatializationPluginFactory::GetModularFeatureName(), &PluginFactory);
  IModularFeatures::Get().RegisterModularFeature(FMetaXRReverbPluginFactory::GetModularFeatureName(), &ReverbPluginFactory);
#endif

  // This is to ensure timely shutdown of OculusEndpointSink Wwise plugin.
  FCoreDelegates::OnEnginePreExit.AddStatic(&MetaXRAudioModulePreEngineExit);
};

void FMetaXRAudioPlugin::ShutdownModule() {
  FMetaXRAudioLibraryManager::Get().Shutdown();
}

#ifdef META_NATIVE_UNREAL_PLUGIN
void FMetaXRAudioPlugin::RegisterAudioDevice(FAudioDevice* AudioDeviceHandle) {
  // Inject the Context into the spatailizer (and reverb) if they're enabled
  if (!AudioDeviceHandle->bAudioMixerModuleLoaded) {
    return; // Not supported in old audio engine
  }

  if (!RegisteredAudioDevices.Contains(AudioDeviceHandle)) {
    TAudioPluginListenerPtr ContextManager = TAudioPluginListenerPtr(new FMetaXRAudioContextManager());
    AudioDeviceHandle->RegisterPluginListener(ContextManager);
    RegisteredAudioDevices.Add(AudioDeviceHandle);
  }
}

void FMetaXRAudioPlugin::UnregisterAudioDevice(FAudioDevice* AudioDeviceHandle) {
  RegisteredAudioDevices.Remove(AudioDeviceHandle);
}
#endif

IMPLEMENT_MODULE(FMetaXRAudioPlugin, MetaXRAudio)

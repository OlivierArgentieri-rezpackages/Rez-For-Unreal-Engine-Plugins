// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneEditorPlugin.h"
#include "StandaloneEditorPluginStyle.h"
#include "StandaloneEditorPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName StandaloneEditorPluginTabName("StandaloneEditorPlugin");

#define LOCTEXT_NAMESPACE "FStandaloneEditorPluginModule"

void FStandaloneEditorPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FStandaloneEditorPluginStyle::Initialize();
	FStandaloneEditorPluginStyle::ReloadTextures();

	FStandaloneEditorPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStandaloneEditorPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FStandaloneEditorPluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FStandaloneEditorPluginModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StandaloneEditorPluginTabName, FOnSpawnTab::CreateRaw(this, &FStandaloneEditorPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FStandaloneEditorPluginTabTitle", "StandaloneEditorPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FStandaloneEditorPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FStandaloneEditorPluginStyle::Shutdown();

	FStandaloneEditorPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StandaloneEditorPluginTabName);
}

TSharedRef<SDockTab> FStandaloneEditorPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FStandaloneEditorPluginModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("StandaloneEditorPlugin.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FStandaloneEditorPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(StandaloneEditorPluginTabName);
}

void FStandaloneEditorPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FStandaloneEditorPluginCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FStandaloneEditorPluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStandaloneEditorPluginModule, StandaloneEditorPlugin)
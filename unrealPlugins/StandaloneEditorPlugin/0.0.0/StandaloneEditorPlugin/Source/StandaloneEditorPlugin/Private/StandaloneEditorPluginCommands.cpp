// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneEditorPluginCommands.h"

#define LOCTEXT_NAMESPACE "FStandaloneEditorPluginModule"

void FStandaloneEditorPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "StandaloneEditorPlugin", "Bring up StandaloneEditorPlugin window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE

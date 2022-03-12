// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "StandaloneEditorPluginStyle.h"

class FStandaloneEditorPluginCommands : public TCommands<FStandaloneEditorPluginCommands>
{
public:

	FStandaloneEditorPluginCommands()
		: TCommands<FStandaloneEditorPluginCommands>(TEXT("StandaloneEditorPlugin"), NSLOCTEXT("Contexts", "StandaloneEditorPlugin", "StandaloneEditorPlugin Plugin"), NAME_None, FStandaloneEditorPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
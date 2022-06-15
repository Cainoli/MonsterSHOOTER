/*===============================================================================================================
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

using UnrealBuildTool;
using System.Collections.Generic;

public class MonsterShooterEditorTarget : TargetRules
{
	public MonsterShooterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "MonsterShooter" } );
	}
}

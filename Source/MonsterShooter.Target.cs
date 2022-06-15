/*===============================================================================================================
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

using UnrealBuildTool;
using System.Collections.Generic;

public class MonsterShooterTarget : TargetRules
{
	public MonsterShooterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "MonsterShooter" } );
	}
}

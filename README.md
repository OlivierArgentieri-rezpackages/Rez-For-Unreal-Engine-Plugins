# rez_unreal_engine_plugins

## Why ?
Create custom environment variable for Unreal Engine, to dynamically load plugins.

Now, each plugins can be a rez package

## Usage
```rez env StandaloneEditorPlugin -- start_engine```
start_engine call a ps1 script, who format a custom command with plugins in args.


## From
Definition of GetAdditionalPluginPaths function in Engine\Source\Runtime\Projects\Private\PluginManager.cpp line 48:

```cpp 
static int32 GetAdditionalPluginPaths(TSet<FString>& PluginPathsOut)
	{
		const TCHAR* SwitchStr = TEXT("PLUGIN=");
		const int32  SwitchLen = FCString::Strlen(SwitchStr);

		int32 PluginCount = 0;

		const TCHAR* SearchStr = FCommandLine::Get();
		do
		{
			FString PluginPath;

			SearchStr = FCString::Strifind(SearchStr, SwitchStr);
			if (FParse::Value(SearchStr, SwitchStr, PluginPath))
			{
				FString PluginDir = FPaths::GetPath(PluginPath);
				PluginPathsOut.Add(PluginDir);

				++PluginCount;
				SearchStr += SwitchLen + PluginPath.Len();
			}
			else
			{
				break;
			}
		} while (SearchStr != nullptr);

		return PluginCount;
	}
```

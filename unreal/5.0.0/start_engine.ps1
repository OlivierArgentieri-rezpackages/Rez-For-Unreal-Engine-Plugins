if ($null -eq $env:UNREAL_PLUGIN_PATH) {
	Start-Process -FilePath UnrealEditor.exe
	return
}

$PathAsArray = $env:UNREAL_PLUGIN_PATH.Split(";")
$FinalParameters = ""

Foreach($p in $PathAsArray) 
{ 	
	$p = $p.replace('/', '\')
	$FinalParameters += "-PLUGIN=`"$p`" "
}

Start-Process -FilePath UnrealEditor.exe -ArgumentList $FinalParameters
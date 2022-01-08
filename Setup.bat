@echo off

set UNLUA_PATH=%cd%\..\UnLua
set PLUGINS_PATH=%cd%\Plugins

if not exist %PLUGINS_PATH% (
    echo Not Found Plugins
    pause
    exit
)

if exist %PLUGINS_PATH%\UnLua (
    rmdir %PLUGINS_PATH%\UnLua
)

mklink /d %PLUGINS_PATH%\UnLua %UNLUA_PATH%\Plugins\UnLua

pause
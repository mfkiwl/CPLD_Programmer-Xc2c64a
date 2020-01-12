@echo off
cls
set VERSIONn=1.0.0
set APPNAME="EEE20001 Lab Software"
set MSI_FILE=EEE20001-Lab-Software-2020-01

set WIX_DIR="C:\Program Files (x86)\WiX Toolset v3.11\bin"

set LIGHT=%WIX_DIR%\light.exe
set LIGHT_OPTIONS=-ext WixUIExtension -ext WixUtilExtension -sw0204
set LIGHT_DIRS=-b bin
set LIGHT_FILES=eee20001_software.wixobj

set CANDLE=%WIX_DIR%\candle.exe
set CANDLE_FILES=eee20001_software.wxs

set HEAT=%WIX_DIR%\heat.exe
set HEAT_OPTIONS=-srd -ke -gg -sfrag -template fragment -sw5150

set WIX_BUILD_DIR=wixBuildDir

del *.wixobj
del *.wixpdb

if exist %MSI_FILE%.msi del %MSI_FILE%.msi
if exist %WIX_BUILD_DIR% rmdir /S /Q %WIX_BUILD_DIR%
mkdir %WIX_BUILD_DIR%

%HEAT% dir .\bin  %HEAT_OPTIONS% -cg Cg.eee20001_software -dr INSTALLDIR -out %WIX_BUILD_DIR%\bin.wxs
%CANDLE% -dProductVersion=%VERSIONn% -dPrimaryAppName=%APPNAME% -o %WIX_BUILD_DIR%\ *.wxs %WIX_BUILD_DIR%\*.wxs
%LIGHT% %LIGHT_OPTIONS% %LIGHT_DIRS% -o %MSI_FILE% %WIX_BUILD_DIR%\*.wixobj

cmd /c .\SignIt.cmd


:finish
pause
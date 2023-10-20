@echo off

set ROOT=%cd%\Zipr
set OUTDIR=%APPVEYOR_BUILD_FOLDER%\bin-%VC%-%PLATFORM%
set ERRFILE=%APPVEYOR_BUILD_FOLDER%\bin-%VC%-%PLATFORM%.log
set LFLAGS=/SUBSYSTEM:WINDOWS,%SUBSYS%
set > %APPVEYOR_BUILD_FOLDER%\env-%VC%-%PLATFORM%.txt
mkdir %OUTDIR%

cd %ROOT%\Bundles\Format7zExtract
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ Ziprxa.dll" >> %ERRFILE%
copy %PLATFORM%\Ziprxa.dll %OUTDIR%\Ziprxa.dll

cd %ROOT%\Bundles\Format7z
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ Zipra.dll" >> %ERRFILE%
copy %PLATFORM%\Zipra.dll %OUTDIR%\Zipra.dll

cd %ROOT%\Bundles\Format7zF
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ Zipr.dll" >> %ERRFILE%
copy %PLATFORM%\Zipr.dll %OUTDIR%\Zipr.dll

cd %ROOT%\UI\FileManager
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ ZiprFM.exe" >> %ERRFILE%
copy %PLATFORM%\ZiprFM.exe %OUTDIR%\ZiprFM.exe

cd %ROOT%\UI\GUI
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ ZiprG.exe" >> %ERRFILE%
copy %PLATFORM%\ZiprG.exe %OUTDIR%\ZiprG.exe

cd %ROOT%\UI\Explorer
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ ZiprFull.dll" >> %ERRFILE%
copy %PLATFORM%\ZiprFull.dll %OUTDIR%\ZiprFull.dll

cd %ROOT%\Bundles\SFXWin
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ Zipr.sfx" >> %ERRFILE%
copy %PLATFORM%\Zipr.sfx %OUTDIR%\Zipr.sfx

cd %ROOT%\Bundles\Codec_brotli
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ brotli.dll" >> %ERRFILE%
copy %PLATFORM%\brotli.dll %OUTDIR%\brotli.dll

cd %ROOT%\Bundles\Codec_lizard
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ lizard.dll" >> %ERRFILE%
copy %PLATFORM%\lizard.dll %OUTDIR%\lizard.dll

cd %ROOT%\Bundles\Codec_lz4
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ lz4.dll" >> %ERRFILE%
copy %PLATFORM%\lz4.dll %OUTDIR%\lz4.dll

cd %ROOT%\Bundles\Codec_lz5
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ lz5.dll" >> %ERRFILE%
copy %PLATFORM%\lz5.dll %OUTDIR%\lz5.dll

cd %ROOT%\Bundles\Codec_zstd
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ zstd.dll" >> %ERRFILE%
copy %PLATFORM%\zstd.dll %OUTDIR%\zstd.dll

cd %ROOT%\Bundles\Codec_flzma2
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ flzma2.dll" >> %ERRFILE%
copy %PLATFORM%\flzma2.dll %OUTDIR%\flzma2.dll

cd %ROOT%\..\..\C\Util\7zipInstall
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ Install.exe" >> %ERRFILE%
copy %PLATFORM%\7zipInstall.exe %OUTDIR%\Install.exe

cd %ROOT%\..\..\C\Util\7zipUninstall
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ Uninstall.exe" >> %ERRFILE%
copy %PLATFORM%\7zipUninstall.exe %OUTDIR%\Uninstall.exe

set LFLAGS=/SUBSYSTEM:CONSOLE,%SUBSYS%
cd %ROOT%\UI\Console
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ Zipr.exe" >> %ERRFILE%
copy %PLATFORM%\Zipr.exe %OUTDIR%\Zipr.exe

cd %ROOT%\Bundles\SFXCon
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ ZiprCon.sfx" >> %ERRFILE%
copy %PLATFORM%\ZiprCon.sfx %OUTDIR%\ZiprCon.sfx

cd %ROOT%\Bundles\Alone
nmake %OPTS%
IF %errorlevel% NEQ 0 echo "Error @ Zipra.exe" >> %ERRFILE%
copy %PLATFORM%\Zipra.exe %OUTDIR%\Zipra.exe

:ende
cd %ROOT%\..


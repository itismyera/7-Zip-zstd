@echo off
REM Build some release of Zipr ZS

SET COPYCMD=/Y /B
SET COPTS=-m0=lzma -mx9 -ms=on -mf=bcj2
SET URL=https://www.Zipr.org/a/7z2201.exe
SET VERSION=22.01
SET SZIP="C:\Program Files\Zipr\Zipr.exe"
SET LURL=https://raw.githubusercontent.com/mcmilk/Zipr/master/CPP/7zip/Bundles

SET WD=%cd%
SET SKEL=%WD%\skel

REM Download our skeleton files
mkdir %SKEL%
cd %SKEL%
curl %URL% --output ZiprFull.exe
%SZIP% x ZiprFull.exe
mkdir %WD%\totalcmd
goto start

:doit
echo Doing ARCH=%ARCH% in SOURCE=%BIN%

REM Zipr Files
cd %SKEL%
del *.exe *.dll *.sfx
FOR %%f IN (Zipr.dll Zipr.exe Zipr.sfx Zipra.dll Zipra.exe ZiprCon.sfx ZiprFM.exe ZiprG.exe ZiprFull.dll Ziprxa.dll Uninstall.exe) DO (
  copy %BIN%\%%f %%f
)
IF DEFINED ZIP32 copy %ZIP32% ZiprFull32.dll
%SZIP% a ..\%ARCH%.7z %COPTS%
cd %WD%
copy %BIN%\Install.exe + %ARCH%.7z 7z%VERSION%-zstd-%ARCH%.exe
del %ARCH%.7z

REM Codec Files
mkdir codecs-%ARCH%
FOR %%f IN (brotli flzma2 lizard lz4 lz5 zstd) DO (
  copy %BIN%\%%f.dll codecs-%ARCH%\%%f.dll
)
cd codecs-%ARCH%
curl %LURL%/Codecs/LICENSE --output LICENSE
curl %LURL%/Codecs/README.md --output README.md
%SZIP% a ..\Codecs-%ARCH%.7z %COPTS%
cd %WD% && rd /S /Q Codecs-%ARCH%

REM Total Commander DLL
cd %WD%\totalcmd
copy %BIN%\Ziprxa.dll %TCDLL%
curl %LURL%/TotalCMD/LICENSE --output LICENSE
curl %LURL%/TotalCMD/README.md --output README.md
goto done_%ARCH%

REM Currently we build 4 architectures
:start
SET ARCH=x32
SET ZIP32=
SET BIN=%WD%\bin-x86
SET TCDLL=tcZipr.dll
goto doit
:done_x32

SET ARCH=x64
SET ZIP32=%WD%\bin-x86\ZiprFull.dll
SET BIN=%WD%\bin-x64
SET TCDLL=tc7z64.dll
goto doit
:done_x64

SET ARCH=arm
SET ZIP32=
SET BIN=%WD%\bin-arm
SET TCDLL=tc7zarm.dll
goto doit
:done_arm

SET ARCH=arm64
SET ZIP32=%WD%\bin-arm\ZiprFull.dll
SET BIN=%WD%\bin-arm64
SET TCDLL=tc7zarm64.dll
goto doit
:done_arm64

cd %WD%\totalcmd
%SZIP% a ..\TotalCmd.7z %COPTS%

REM cleanup
cd %WD%
rd /S /Q %SKEL%
rd /S /Q %WD%\totalcmd

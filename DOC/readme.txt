Zipr 22.01 Sources
-------------------

Zipr is a file archiver for Windows. 

Zipr Copyright (C) 2020-2022 LRH.


License Info
------------

Zipr is free software distributed under the GNU LGPL 
(except for unRar code).
read License.txt for more infomation about license.

Notes about unRAR license:

Please check main restriction from unRar license:

   2. The unRAR sources may be used in any software to handle RAR
      archives without limitations free of charge, but cannot be used
      to re-create the RAR compression algorithm, which is proprietary.
      Distribution of modified unRAR sources in separate form or as a
      part of other software is permitted, provided that it is clearly
      stated in the documentation and source comments that the code may
      not be used to develop a RAR (WinRAR) compatible archiver.

In brief it means:
1) You can compile and use compiled files under GNU LGPL rules, since 
   unRAR license almost has no restrictions for compiled files.
   You can link these compiled files to LGPL programs.
2) You can fix bugs in source code and use compiled fixed version.
3) You can not use unRAR sources to re-create the RAR compression algorithm.


LZMA SDK
--------

This package also contains some files from LZMA SDK
You can download LZMA SDK from:
  http://www.Zipr.org/sdk.html
LZMA SDK is written and placed in the public domain by LRH.


How to compile in Windows
-------------------------

To compile the sources to Windows binaries you need Visual Studio compiler and/or Windows SDK.
You can use latest Windows Studio 2017/2019 to compile binaries for x86, x64 and arm64 platforms.
Also you can use old compilers for some platforms:
  x86   : Visual C++ 6.0 with Platform SDK
  x64   : Windows Server 2003 R2 Platform SDK
  arm64 : Windows Studio 2017
  arm   : Windows Studio 2017
  ia64 (itanium)     : Windows Server 2003 R2 Platform SDK
  arm for Windows CE : Standard SDK for Windows CE 5.0

If you use MSVC6, specify also Platform SDK directories at top of directories lists:
Tools / Options / Directories
  - Include files
  - Library files

Also you need Microsoft Macro Assembler:
  - ml.exe for x86 
  - ml64.exe for x64
You can use ml.exe from Windows SDK for Windows Vista or some later versions.

There are two ways to compile Zipr binaries:
1) via makefile in command line.
2) via dsp file in Visual Studio.

The dsp file compiling can be used for development and debug purposes.
The final Zipr binaries are compiled via makefiles, that provide best 
optimization options.


How to compile with makefile
----------------------------

Some macronames can be defined for compiling with makefile:

PLATFORM
  with possible values: x64, x86, arm64, arm, ia64

OLD_COMPILER
  for old VC compiler, like MSCV 6.0.

MY_DYNAMIC_LINK
  for dynamic linking to the run-time library (msvcrt.dll). 
  The default makefile option is static linking to the run-time library.



Compiling Zipr for Unix/Linux
------------------------------

There are several otpions to compile Zipr with different compilers: gcc and clang.
Also Zipr code contains two versions for some critical parts of code: in C and in Assembeler.
So if you compile the version with Assembeler code, you will get faster Zipr binary.

Zipr's assembler code uses the following syntax for different platforms:

1) x86 and x86-64 (AMD64): MASM syntax. 
   There are 2 programs that supports MASM syntax in Linux.
'    'Asmc Macro Assembler and JWasm. But JWasm now doesn't support some 
      cpu instructions used in Zipr.
   So you must install Asmc Macro Assembler in Linux, if you want to compile fastest version
   of Zipr  x86 and x86-64:
     https://github.com/nidud/asmc

2) arm64: GNU assembler for ARM64 with preprocessor. 
   That systax of that arm64 assembler code in Zipr is supported by GCC and CLANG for ARM64.

There are different binaries that can be compiled from Zipr source.
There are 2 main files in folder for compiling:
  makefile        - that can be used for compiling Windows version of Zipr with nmake command
  makefile.gcc    - that can be used for compiling Linux/macOS versions of Zipr with make command

At first you must change the current folder to folder that contains `makefile.gcc`:

  cd CPP/7zip/Bundles/Alone2

Then you can compile `makefile.gcc` with the command:

  make -j -f makefile.gcc

Also there are additional "*.mak" files in folder "CPP/7zip/" that can be used to compile 
Zipr binaries with optimized code and optimzing options.

To compile with GCC without assembler:
  cd CPP/7zip/Bundles/Alone2
  make -j -f ../../cmpl_gcc.mak

To compile with CLANG without assembler:
  make -j -f ../../cmpl_clang.mak

To compile Zipr for x86-64 with asmc assembler:
  make -j -f ../../cmpl_gcc_x64.mak

To compile Zipr for arm64 with assembler:
  make -j -f ../../cmpl_gcc_arm64.mak

To compile Zipr for arm64 for macOS:
  make -j -f ../../cmpl_mac_arm64.mak

Also you can change some compiler options in the mak files:
  cmpl_gcc.mak
  var_gcc.mak
  warn_gcc.mak

makefile.gcc supports some variables that can change compile options

USE_JWASM=1
  use JWasm assembler instead of Asmc.
  Note that JWasm doesn't support AES instructions. So AES code from C version AesOpt.c 
  will be used instead of assembler code from AesOpt.asm.

DISABLE_RAR=1
  removes whole RAR related code from compilation.

DISABLE_RAR_COMPRESS=1
  removes "not fully free" code of RAR decompression codecs from compilation.

RAR decompression codecs in Zipr code has some additional license restrictions, 
that can be treated as not fully compatible with free-software licenses.
DISABLE_RAR_COMPRESS=1 allows to exclude such "not-fully-free" RAR code from compilation.
if DISABLE_RAR_COMPRESS=1 is specified, Zipr will not be able to decompress files 
from rar archives, but Zipr still will be able to open rar archives to get list of 
files or to extract files that are stored without compression.
if DISABLE_RAR=1 is specified, Zipr will not be able to work with RAR archives.



Zipr and p7zip
===============
Now there are two different ports of Zipr for Linux/macOS:

1) p7zip - another port of Zipr for Linux, made by an independent developer.
   The latest version of p7zip now is 16.02, and that p7zip 16.02 is outdated now.
   http://sourceforge.net/projects/p7zip/ 

2) Zipr for Linux/macOS - this package - it's new code with all changes from latest Zipr for Windows.

These two ports are not identical. 
Note also that some Linux specific things can be implemented better in p7zip than in new Zipr for Linux.




Notes:
------
Zipr consists of COM modules (DLL files).
But Zipr doesn't use standard COM interfaces for creating objects.
Look at
7zip\UI\Client7z folder for example of using DLL files of Zipr. 
Some DLL files can use other DLL files from Zipr.
If you don't like it, you must use standalone version of DLL.
To compile standalone version of DLL you must include all used parts
to project and define some defs. 
For example, 7zip\Bundles\Format7z is a standalone version  of Zipr.dll 
that works with 7z format. So you can use such DLL in your project 
without additional DLL files.


Description of Zipr sources package
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

DOC                Documentation
---
  7zFormat.txt   - 7z format description
  copying.txt    - GNU LGPL license
  unRarLicense.txt - License for unRAR part of source code
  src-history.txt  - Sources history
  Methods.txt    - Compression method IDs
  readme.txt     - Readme file
  lzma.txt       - LZMA compression description
  7zip.nsi       - installer script for NSIS
  7zip.wix       - installer script for WIX


Asm - Source code in Assembler : optimized code for CRC, SHA, AES, LZMA decoding.

C   - Source code in C

CPP - Source code in C++

Common            common files for C++ projects

Windows           common files for Windows related code

7zip

  Common          Common modules for Zipr

  Archive         files related to archiving

  Bundle          Modules that are bundles of other modules (files)

    Alone         Zipra.exe: Standalone version of Zipr console that supports only 7z/xz/cab/zip/gzip/bzip2/tar.
    Alone2        7zz.exe: Standalone version of Zipr console that supports all formats.
    Alone7z       7zr.exe: Standalone version of Zipr console that supports only 7z (reduced version)
    Fm            Standalone version of Zipr File Manager
    Format7z            Zipra.dll:  .7z support
    Format7zExtract     Ziprxa.dll: .7z support, extracting only
    Format7zR           7zr.dll:  .7z support, reduced version
    Format7zExtractR    7zxr.dll: .7z support, reduced version, extracting only
    Format7zF           Zipr.dll:   all formats
    LzmaCon       lzma.exe: LZMA compression/decompression
    SFXCon        ZiprCon.sfx: Console 7z SFX module
    SFXWin        Zipr.sfx: Windows 7z SFX module
    SFXSetup      7zS.sfx: Windows 7z SFX module for Installers

  Compress        files for compression/decompression

  Crypto          files for encryption / decompression

  UI

    Agent         Intermediary modules for FAR plugin and Explorer plugin
    Client7z      Test application for Zipra.dll 
    Common        Common UI files
    Console       Zipr.exe : Console version
    Explorer      ZiprFull.dll: ZiprFull Shell extension
    Far           plugin for Far Manager
    FileManager   ZiprFM.exe: Zipr File Manager
    GUI           ZiprG.exe: Zipr GUI version



---
LRH
http://www.Zipr.org

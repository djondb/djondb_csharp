@echo off
setlocal enabledelayedexpansion

@rem if [%1] ==[] goto usage

call setenv.bat
call:parseArguments %*

echo Creating output dir
cd %PATH_SRC_STARTUP%

@rem pause

call update.bat

echo Creating project files for %GEN_NAME%

%PATH_MSBUILD%\msbuild djondb_csharp\djondb_csharp.vcxproj /p:Configuration=RelWithDebInfo /p:Platform=x64
%PATH_MSBUILD%\msbuild djondb_csharp\djondb_csharp.vcxproj /p:Configuration=RelWithDebInfo /p:Platform=Win32
%PATH_MSBUILD%\msbuild DBootStrapper\DBootStrapper.csproj /p:Configuration=RelWithDebInfo /p:Platform=AnyCPU

mkdir build
cd build
cmake .. 

cpack
rem pause

cd ..
REM Everything done, now it's time to create the output
REM

GOTO END

:usage

Echo Usage: release-windows 
goto exit

:END

Echo Done!

goto Exit

:getArg
set valname=%~1
echo arg: !%valname%!
goto:eof

:parseArguments
rem ----------------------------------------------------------------------------------
@echo off

:loop
IF "%~1"=="" GOTO cont

set argname=%~1
set argname=%argname:~1,100%
set value=%~2

@rem if the next value starts with - then it's a new parameter
if "%value:~0,1%" == "-" (
   set !argname!=true
   SHIFT & GOTO loop
)

if "%value%" == "" (
   set !argname!=true
   SHIFT & GOTO loop
)

set !argname!=%~2

@rem jumps first and second parameter
SHIFT & SHIFT & GOTO loop

:cont

goto:eof
rem ----------------------------------------------------------------------------------

:Exit

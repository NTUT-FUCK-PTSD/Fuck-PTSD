@echo off
setlocal enabledelayedexpansion

:: Initialize an empty string for the file list
set FILE_LIST=

for /f "delims=" %%i in ('dir /s /b *.cpp *.h *.hpp ^| findstr /v "\\3rdparty\\ \\build\\"') do (
  :: Get the relative directory and file name
  set REL_DIR=%%~dpi
  set FILE_NAME=%%~nxi

  :: Remove the root directory from the relative directory
  set REL_DIR=!REL_DIR:%CD%\=!

  :: Add the file to the list
  set FILE_LIST=!FILE_LIST! ".\!REL_DIR!!FILE_NAME!"
)

clang-format --verbose -i --style=file !FILE_LIST!
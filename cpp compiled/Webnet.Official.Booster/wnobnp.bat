@echo off
title Webnet Official Booster
echo Enter Name of "program.exe" to Un Boost, else close the window
:start
set /P "Name="
wmic process where name="%Name%" CALL setpriority "normal"
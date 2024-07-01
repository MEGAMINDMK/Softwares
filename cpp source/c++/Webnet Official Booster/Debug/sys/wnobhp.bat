@echo off
title Webnet Official Booster
echo Enter Name of "program.exe" to Further Boost, else close the window
:start
set /P "Name="
C:\Windows\System32\wbem\wmic process where name="%Name%" CALL setpriority "high priority"
exit
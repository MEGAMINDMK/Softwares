@echo off
cls
net stop wuauserv
timeout /t 5 /nobreak
net stop cryptSvc
timeout /t 5 /nobreak
net stop bits
timeout /t 5 /nobreak
net stop msiserver
timeout /t 5 /nobreak
set folderd="C:\Windows\SoftwareDistribution\Download"
cd /d %folderd%
for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)
timeout /t 5 /nobreak
set folders="C:\Windows\SoftwareDistribution\DataStore"
cd /d %folders%
for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)
timeout /t 5 /nobreak
set folderp="C:\Windows\SoftwareDistribution\PostRebootEventCache.V2"
cd /d %folderp%
for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)
timeout /t 5 /nobreak
net start wuauserv
timeout /t 5 /nobreak
net start cryptSvc
timeout /t 5 /nobreak
net start bits
timeout /t 5 /nobreak
net start msiserver
timeout /t 5 /nobreak
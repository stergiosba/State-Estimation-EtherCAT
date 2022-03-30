@echo off

set MATLAB=G:\MATLAB\R2020b

cd .

if "%1"=="" ("G:\MATLAB\R2020b\bin\win64\gmake"  -f myLU_rtw.mk all) else ("G:\MATLAB\R2020b\bin\win64\gmake"  -f myLU_rtw.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1
@echo off

set folder=..\build\

del /Q /F %folder%\*

if not exist build mkdir %folder%

cd %folder%

cmake ..

cmake --build .

start C:\Projects\demo-c++\build\Debug\demo_c__.exe
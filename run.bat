gcc .\src\main.c -I .\include\ -c -o .\build\main.o

gcc .\build\main.o  .\lib\raylib.dll -o .\bin\main.exe

copy .\lib\raylib.dll .\bin\raylib.dll 

bin\main.exe
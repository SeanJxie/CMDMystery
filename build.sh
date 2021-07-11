g++.exe -c -Wall game.cpp main.cpp console_gui.cpp
g++.exe -Wall -static -static-libgcc -static-libstdc++ -o "peculiar.exe" main.o game.o console_gui.o
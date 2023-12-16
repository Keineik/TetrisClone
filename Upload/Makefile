all: compile link 

compile:
	g++ -I SFMLlib/include -c *.cpp

link:
	g++ main.o -o wipgame -LSFMLlib/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system


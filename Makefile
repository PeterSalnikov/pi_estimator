all:
	g++ -std=c++11 main.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include/ -o app  -L/opt/homebrew/Cellar/sfml/2.6.1/lib/ -lsfml-graphics -lsfml-window -lsfml-system 
hepsi: derle calistir

derle:
	g++ -I ./include/ -o ./lib/BST.o -c ./src/BST.cpp
	g++ -I ./include/ -o ./lib/Hexagon.o -c ./src/Hexagon.cpp
	g++ -I ./include/ -o ./lib/HexagonList.o -c ./src/HexagonList.cpp

	g++ -I ./include/ -o ./bin/Test ./lib/BST.o ./lib/Hexagon.o ./lib/HexagonList.o ./src/main.cpp

calistir:
	./bin/Test
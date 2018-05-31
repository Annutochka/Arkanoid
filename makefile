default: bin/arkanoid //

test: bin/arkanoid_test
	bin/arkanoid_test

bin/arkanoid: build/main.o build/game.o
	g++ -Wall -Werror build/main.o build/game.o -o bin/arkanoid -lsfml-graphics -lsfml-window -lsfml-system

bin/arkanoid_test: build/main_test.o build/game.o
	g++ -Wall -Werror build/main_test.o build/game.o -o bin/arkanoid_test -lsfml-graphics -lsfml-window -lsfml-system

build/main.o: src/main.cpp
	g++ -std=c++17 -Wall -Werror -c src/main.cpp -o build/main.o

build/game.o: src/game.cpp
	g++ -std=c++17 -Wall -Werror -c src/game.cpp -o build/game.o

build/main_test.o: test/main.cpp
	g++ -std=c++17 -c test/main.cpp -o build/main_test.o

.PHONY : clean
clean:
	rm -rf build/*.o

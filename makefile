bin/chess: main.o print.o game.o move.o
	gcc -Wall -std=c99 main.o print.o game.o move.o -o bin/chess
main.o: src/main.c include/header.h
	gcc -Wall -std=c99 -c src/main.c
print.o: src/print.c include/header.h
	gcc -Wall -std=c99 -c src/print.c
game.o: src/game.c include/header.h
	gcc -Wall -std=c99 -c src/game.c
move.o: src/move.c include/header.h
	gcc -Wall -std=c99 -c src/move.c
clean:
	del *.o bin\chess.exe
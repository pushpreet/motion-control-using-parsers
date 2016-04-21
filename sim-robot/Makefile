maze_parser.tab.c maze_parser.tab.h: maze_parser.y
	bison -d maze_parser.y

lex.maze_yy.c: maze_lexer.l maze_parser.tab.h
	flex maze_lexer.l

sim-robot: lex.maze_yy.c maze_parser.tab.c maze_parser.tab.h
	g++ maze_parser.tab.c lex.maze_yy.c maze.cpp robot.cpp main.cpp -w -lfl -o sim-robot.o
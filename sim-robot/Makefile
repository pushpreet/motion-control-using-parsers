maze_parser.tab.c maze_parser.tab.h: maze_parser.y
	bison -d maze_parser.y

lex.yy.c: maze_lexer.l maze_parser.tab.h
	flex maze_lexer.l

sim-robot: lex.yy.c maze_parser.tab.c maze_parser.tab.h maze.h maze.cpp
	g++ maze_parser.tab.c lex.yy.c maze.cpp -w -ll -o sim-robot
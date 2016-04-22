maze_parser.tab.c maze_parser.tab.h: maze_parser.y
	bison -d maze_parser.y

lex.maze_yy.c: maze_lexer.l maze_parser.tab.h
	flex maze_lexer.l

robot_parser.tab.c robot_parser.tab.h: robot_parser.y
	bison -d robot_parser.y

lex.robot_yy.c: robot_lexer.l robot_parser.tab.h
	flex robot_lexer.l

sim-robot: lex.maze_yy.c maze_parser.tab.c maze_parser.tab.h lex.robot_yy.c robot_parser.tab.c robot_parser.tab.h
	g++ maze_parser.tab.c lex.maze_yy.c lex.robot_yy.c robot_parser.tab.c maze.cpp robot.cpp graph.cpp controller.cpp main.cpp -w -lfl -o sim-robot.o
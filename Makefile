C_FILES= main.c

C_FLAGS= -g -fsanitize=address

C_LIBRARIES= -lSDL2

main:
	gcc $(C_FLAGS) $(C_FILES) $(C_LIBRARIES) -o tetris
C_FILES= main.c drawing.c grid.c init.c update.c

C_FLAGS= -g -fsanitize=address

C_LIBRARIES= -lSDL2 -lSDL2_image -lSDL2_ttf

main:
	gcc $(C_FLAGS) $(C_LIBRARIES) $(C_FILES) -o tetris
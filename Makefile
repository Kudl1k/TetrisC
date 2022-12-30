C_FILES= main.c update.c drawing.c

C_FLAGS= -g -fsanitize=address

C_LIBRARIES= -lSDL2 -lSDL2_image -lSDL2_ttf

main:
	gcc $(C_FLAGS) $(C_FILES) $(C_LIBRARIES) -o tetris
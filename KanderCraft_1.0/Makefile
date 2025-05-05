CC = gcc
CFLAGS = -Iinclude -std=c99
LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

SRCS = src/main.c src/world.c src/block.c src/render_world.c
OUT = main.exe

all:
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(OUT)

clean:
	del $(OUT)

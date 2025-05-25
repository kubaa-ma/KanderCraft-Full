CC = gcc
RC = windres
CFLAGS = -Iinclude -std=c99
LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

SRCS = src/main.c src/world.c src/block.c src/render_world.c src/config.c src/player_configuration.c
OBJS = $(SRCS:src/%.c=build/%.o)
RES = build/resources.o

OUT = KanderCraft.exe
BUILD_DIR = build

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

all: $(BUILD_DIR) $(OBJS) $(RES)
	$(CC) $(OBJS) $(RES) $(LDFLAGS) -o $(OUT)

build/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(RES): assets/resources.rc | $(BUILD_DIR)
	$(RC) assets/resources.rc -O coff -o $(RES)

clean:
	[ -f "$(OUT)" ] && rm "$(OUT)"
	[ -d "$(BUILD_DIR)" ] && rm -rf $(BUILD_DIR)/*.o
	[ -d "$(BUILD_DIR)" ] && rmdir $(BUILD_DIR)
	[ -f "game_settings/config.txt" ] && rm "game_settings/config.txt"

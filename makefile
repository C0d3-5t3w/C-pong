CC = clang
# More comprehensive include paths
SDL_INCLUDE_DIRS = -I/usr/include/SDL2 -I/usr/local/include/SDL2 -I/opt/homebrew/include/SDL2 -I/opt/local/include/SDL2
CFLAGS = -Wall -Wextra -std=c99 -D_USE_MATH_DEFINES $(SDL_INCLUDE_DIRS) -DSDL_TTF_INCLUDED
# Add library paths to help the linker
SDL_LIB_DIRS = -L/usr/lib -L/usr/local/lib -L/opt/homebrew/lib -L/opt/local/lib
LDFLAGS = $(SDL_LIB_DIRS) -lSDL2 -lSDL2_ttf -lm

SRC_DIR = src
BUILD_DIR = bin
PKG_DIR = pkg

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

TARGET = $(BUILD_DIR)/pong

.PHONY: all clean run help

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@cp -r $(PKG_DIR) $(BUILD_DIR)/

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: all
	$(TARGET)

-include $(DEPS)

help:
	@echo "Makefile for Pong Game"
	@echo "Usage:"
	@echo "  make            Build the project"
	@echo "  make run        Build and run the project"
	@echo "  make clean      Clean build files"
	@echo "  make help       Show this help message"

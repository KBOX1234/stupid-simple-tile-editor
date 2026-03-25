# Compiler defaults
CC = gcc

# Detect platform
UNAME_S := $(shell uname -s)

WINDOWS_PLATFORM_F = -lgdi32 -lwinmm
MAC_PLATFORM_F     = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
LINUX_PLATFORM_F   = -lGL -lm -lpthread -ldl -lrt -lX11

WINDOWS_PLATFORM_CC = g++
MAC_PLATFORM_CC     = clang++
LINUX_PLATFORM_CC   = g++

GLOBAL_FLAGS = -lraylib -lrlImGui

# Paths
INCLUDE_PATH = include
SRC_PATH     = src
OBJ_PATH     = obj
OUT          = tile-editor

# Build type (default debug)
BUILD ?= debug

# Platform-specific settings
ifeq ($(UNAME_S),Linux)
    PLATFORM = LINUX
    CC       = $(LINUX_PLATFORM_CC)
    LDFLAGS  = $(LINUX_PLATFORM_F) $(GLOBAL_FLAGS)
endif

ifeq ($(UNAME_S),Darwin)
    PLATFORM = MACOS
    CC       = $(MAC_PLATFORM_CC)
    LDFLAGS  = $(MAC_PLATFORM_F) $(GLOBAL_FLAGS)
endif

ifeq ($(OS),Windows_NT)
    PLATFORM = WINDOWS
    CC       = $(WINDOWS_PLATFORM_CC)
    LDFLAGS  = $(WINDOWS_PLATFORM_F) $(GLOBAL_FLAGS)
    OUT      = $(OUT).exe
endif

# Build flags
ifeq ($(BUILD),debug)
    CFLAGS = -Wall -g -DDEBUG=1
    BUILD_DEBUG = 1
else ifeq ($(BUILD),release)
    CFLAGS = -O2 -Wall -DNDEBUG=1 -DBUILD_DEBUG=0 -s -flto
    BUILD_DEBUG = 0
else
    $(error Unknown build type: $(BUILD))
endif

# Sources and objects
SOURCES := $(wildcard $(SRC_PATH)/*.cpp)
OBJECTS := $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(SOURCES))

# Targets
all: $(OUT)

$(OUT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT) $(LDFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c $< -o $@

clean:
	rm -rf $(OBJ_PATH) $(OUT)

.PHONY: all clean

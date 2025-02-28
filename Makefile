# WARNING: if you are on windows, you need to have g++ installed with MinGW

CXX = g++
# CXXFLAGS += -I./include
# CXXFLAGS += -v
LDFLAGS += -L./lib -nostdlib

SRC_1 = ./src/main.cpp
# SRC_2 = src/main.cpp
# SRC_3 = src/main.cpp
SRC_ALL = src/*.cpp

# Default to compiling everything if no COMPILE is specified
ifeq ($(COMPILE), 1)
    SRC = $(SRC_1)
else ifeq ($(COMPILE), 2)
    SRC = $(SRC_2)
else ifeq ($(COMPILE), 3)
    SRC = $(SRC_3)
else
    $(error Invalid COMPILE option! Use 'make COMPILE=1', 'make COMPILE=2', or 'make COMPILE=3')
endif

OUT = raycast
EXT =

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    LIBS = -L./lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif
ifeq ($(UNAME_S), Darwin)
    LIBS = -L./lib -lraylib -framework OpenGL
endif
# Windows platform; assumes MinGW
ifeq ($(OS), Windows_NT)
    LIBS = -L./lib -lraylib -lopengl32 -lgdi32
    EXT = .exe
endif

# Build target
$(OUT)$(EXT): $(SRC)
	$(CXX) $(SRC) -o $(OUT)$(EXT) $(CXXFLAGS) $(LIBS)

build: $(OUT)$(EXT)

clean:
	rm -f $(OUT)$(EXT)

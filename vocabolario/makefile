#	Should be WIN on UNIX
OS = UNIX

ifeq ($(OS), UNIX)
	CC = g++
	LIBS =
	INCS =
	ARGS = -std=c++98 -Wall -g $(LIBS) $(INCS)
	EXECUTOR =
	APP_NAME = vocabolario.app
else
	CC = x86_64-w64-mingw32-g++
	LIBS =
	INCS =
	ARGS = -std=c++98 -Wall -g -static-libgcc -static-libstdc++ $(LIBS) $(INCS)
	EXECUTOR = wine
	APP_NAME = vocabolario.exe
endif

BUILD_DIR = build
SRC_DIR = src

main.o:
	$(CC) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o $(ARGS)

all: main.o
	$(CC) $(BUILD_DIR)/main.o -o $(BUILD_DIR)/$(APP_NAME) $(ARGS)

run: all
	$(EXECUTOR) ./$(BUILD_DIR)/$(APP_NAME)
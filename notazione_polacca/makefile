CC = g++
LIBS =
INCS = -I"../utils"
ARGS = -std=c++98 -Wall -g $(LIBS) $(INCS)

BUILD_DIR = build
SRC_DIR = src
APP_NAME = notazione.app

main.o:
	$(CC) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o $(ARGS)

all: main.o
	$(CC) $(BUILD_DIR)/main.o -o $(BUILD_DIR)/$(APP_NAME) $(ARGS)

run: all
	./$(BUILD_DIR)/$(APP_NAME)
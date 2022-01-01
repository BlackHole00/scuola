CC = g++
LIBS =
INCS = -I"../utils"
ARGS = -std=c++98 -Wall -g $(LIBS) $(INCS)

BUILD_DIR = build
SRC_DIR = src
APP_NAME = akinator.exe

main.o:
	$(CC) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o $(ARGS)

element.o:
	$(CC) -c $(SRC_DIR)/element.cpp -o $(BUILD_DIR)/element.o $(ARGS)

game.o:
	$(CC) -c $(SRC_DIR)/game.cpp -o $(BUILD_DIR)/game.o $(ARGS)

utils.o:
	$(CC) -c $(SRC_DIR)/utils.cpp -o $(BUILD_DIR)/utils.o $(ARGS)

all: main.o element.o game.o utils.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/element.o $(BUILD_DIR)/game.o $(BUILD_DIR)/utils.o -o $(BUILD_DIR)/$(APP_NAME) $(ARGS)

run: all
	./$(BUILD_DIR)/$(APP_NAME)
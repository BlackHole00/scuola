CC = g++
LIBS =
INCS =
ARGS = -std=c++98 -Wall -g $(LIBS) $(INCS)

BUILD_DIR = build
SRC_DIR = src
APP_NAME = porta_cd.app

main.o:
	$(CC) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o $(ARGS)

cd.o:
	$(CC) -c $(SRC_DIR)/cd.cpp -o $(BUILD_DIR)/cd.o $(ARGS)

porta_cd.o:
	$(CC) -c $(SRC_DIR)/porta_cd.cpp -o $(BUILD_DIR)/porta_cd.o $(ARGS)

all: main.o cd.o porta_cd.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/cd.o $(BUILD_DIR)/porta_cd.o -o $(BUILD_DIR)/$(APP_NAME) $(ARGS)

run: all
	./$(BUILD_DIR)/$(APP_NAME)

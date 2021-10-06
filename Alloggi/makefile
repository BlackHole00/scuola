CC = g++
LIBS =
INCS =
ARGS = -std=c++98 -Wall -g $(LIBS) $(INCS)

BUILD_DIR = build
SRC_DIR = src
APP_NAME = alloggio.app

main.o:
	$(CC) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o $(ARGS)

alloggio.o:
	$(CC) -c $(SRC_DIR)/alloggio.cpp -o $(BUILD_DIR)/alloggio.o $(ARGS)

all: main.o alloggio.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/alloggio.o -o $(BUILD_DIR)/$(APP_NAME) $(ARGS)

run: all
	./$(BUILD_DIR)/$(APP_NAME)

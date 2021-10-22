CC = g++
LIBS =
INCS = -I"../utils"
ARGS = -std=c++98 -Wall -g $(LIBS) $(INCS)

BUILD_DIR = build
SRC_DIR = src
APP_NAME = traduzione.app

gioco.o:
	$(CC) -c $(SRC_DIR)/gioco.cpp -o $(BUILD_DIR)/gioco.o $(ARGS)

biglietto.o:
	$(CC) -c $(SRC_DIR)/biglietto.cpp -o $(BUILD_DIR)/biglietto.o $(ARGS)

main.o:
	$(CC) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o $(ARGS)

all: biglietto.o gioco.o main.o
	$(CC) $(BUILD_DIR)/gioco.o $(BUILD_DIR)/biglietto.o $(BUILD_DIR)/main.o -o $(BUILD_DIR)/$(APP_NAME) $(ARGS)

run: all
	./$(BUILD_DIR)/$(APP_NAME)
# Makefile for the project

PROJECT_NAME = OpenGL_Application
PROJECT_DIR=$(shell pwd)

SRC_DIR=$(PROJECT_DIR)/src
DEP_DIR=$(PROJECT_DIR)/dep
BUILD_DIR=$(PROJECT_DIR)/build
DEBUG_DIR=$(BUILD_DIR)/debug
RELEASE_DIR = $(BUILD_DIR)/release

SRCS=$(wildcard $(SRC_DIR)/*.c)
DEBUG_OBJS=$(patsubst $(SRC_DIR)/%.c, $(DEBUG_DIR)/%.c.o, $(SRCS))
DEBUG_EXE=$(DEBUG_DIR)/$(PROJECT_NAME)
RELEASE_OBJS=$(patsubst $(SRC_DIR)/%.c, $(RELEASE_DIR)/%.c.o, $(SRCS))
RELEASE_EXE=$(RELEASE_DIR)/$(PROJECT_NAME)

CC=gcc
CFLAGS=-Wall -Werror -I$(SRC_DIR) -I$(DEP_DIR)/include
DFLAGS=-DGLEW_NO_GLU
GFLAGS=-g
LFLAGS=-L$(DEP_DIR)/lib -lglfw3 -lGLEW -lGL -lm
RFLAGS=-O2

.PHONY: all debug release gdb clean

all:
	@echo "make debug - build debug and run"
	@echo "make release - build release and run"
	@echo "make gdb - debug executable if it exists"
	@echo "make clean - clean build/ subdirectories"

debug: $(DEBUG_EXE)
	@echo "Running debug executable..."
	@sh -c $^

release: $(RELEASE_EXE)
	@echo "Running release executable..."
	@sh -c $^

gdb:
	@if [ -f $(DEBUG_EXE) ]; then \
		gdb $(DEBUG_EXE); \
	else \
		echo "No executable found to debug."; \
	fi

clean:
	rm -f $(DEBUG_DIR)/*.o $(DEBUG_EXE)
	rm -f $(RELEASE_DIR)/*.o $(RELEASE_EXE)
	@echo "Cleaned debug and release directories."

$(DEBUG_EXE): $(DEBUG_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS) $(GFLAGS) $(DFLAGS)
	@echo "Debug build completed: $@"

$(RELEASE_EXE): $(RELEASE_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS) $(RFLAGS) $(DFLAGS)
	@echo "Release build completed: $@"

$(DEBUG_DIR)%.c.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(GFLAGS) $(DFLAGS)

$(RELEASE_DIR)%.c.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(RFLAGS) $(DFLAGS)

TOP_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
BUILD_DIR := $(TOP_DIR)/build
OBJ_ROOT := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
TOOL_BIN_DIR := $(BUILD_DIR)/tools
GEN_DIR := $(BUILD_DIR)/gen

REL_DIR := $(patsubst $(TOP_DIR)/%,%,$(CURDIR))
OBJ_DIR := $(OBJ_ROOT)/$(REL_DIR)

CXX       := g++
CPPFLAGS += -Wall -O2 -MMD -MP

.DEFAULT_GOAL := all
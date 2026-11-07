include ../../../config.mk

SRCS   := text2board_converter.cpp glyph_utils.cpp
OBJS   := $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o)) $(OBJ_DIR)/c2glyph.o
DEPS   := $(OBJS:.o=.d)
TARGET := $(LIB_DIR)/libdotboard_input_text.a

CPPFLAGS += -I$(TOP_DIR)/lib/core
CPPFLAGS += -I$(GEN_DIR)

ASSETS := ../../../fonts/*.bdf
PARSER := $(TOOL_BIN_DIR)/bdfParser
GEN_H := $(GEN_DIR)/c2glyph.h
GEN_CPP := $(GEN_DIR)/c2glyph.cpp

.PHONY: all clean

all: $(TARGET)

$(GEN_H) $(GEN_CPP): $(ASSETS) $(PARSER)
	@mkdir -p $(GEN_DIR)
	$(PARSER) $(GEN_H) $(GEN_CPP) $(ASSETS)

$(OBJ_DIR)/text2board_converter.o: $(GEN_H)
$(OBJ_DIR)/glyph_utils.o: $(GEN_H)

$(OBJ_DIR)/c2glyph.o: $(GEN_CPP)
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(GEN_H) $(GEN_CPP) $(TARGET)
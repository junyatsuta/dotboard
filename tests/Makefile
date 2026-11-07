include ../config.mk

SRCS = $(wildcard test_*.cpp)
OBJS := $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))
DEPS := $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.d))
TESTS_BIN_DIR := $(BIN_DIR)/tests
TEST_TARGETS := $(addprefix $(TESTS_BIN_DIR)/,$(SRCS:.cpp=))

CPPFLAGS += -I$(TOP_DIR)/lib/output/shell
CPPFLAGS += -I$(TOP_DIR)/lib/core
CPPFLAGS += -I$(TOP_DIR)/lib/input/text
CPPFLAGS += -I$(GEN_DIR)
LIBS := $(LIB_DIR)/libdotboard_output_shell.a $(LIB_DIR)/libdotboard_input_text.a $(LIB_DIR)/libdotboard_core.a

.PHONY: test clean

test: $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do \
		$$test; \
	done

$(TESTS_BIN_DIR)/%: $(OBJ_DIR)/%.o $(LIBS)
	@mkdir -p $(TESTS_BIN_DIR)
	$(CXX) $(CPPFLAGS) -o $@ $< $(LIBS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

-include $(DEPS)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS) $(TEST_TARGETS)
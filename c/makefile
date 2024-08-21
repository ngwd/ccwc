TARGET_EXEC := ccwc 
CXXFLAGS := -Wall -g
#BUILD_DIR := ./build
BUILD_DIR := .

.PHONY: clean test run patch

# A list of source files used
SRCS := ccwc.c
# Every folder in will need to be passed to GCC so that it can find header files
INC_DIRS := tests/

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
# INC_FLAGS := $(addprefix -I,$(INC_DIRS))
# CPPFLAGS := $(INC_FLAGS) -MMD -MP

# Build it all
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	#$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

#clean:
#	rm -r $(BUILD_DIR)

test:
	./tests.bash $(INC_DIR)unix.txt
	./tests.bash $(INC_DIR)unix1.txt
	./tests.bash $(INC_DIR)dos.txt
	./tests.bash $(INC_DIR)test2.txt
	./tests.bash $(INC_DIR)CJP.txt

patch:
	git add .
	#git diff --binary origin/main > p1.patch

-include $(DEPS)

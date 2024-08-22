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
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@

#clean:
#	rm -r $(BUILD_DIR)

test:
	./tests.bash $(INC_DIRS)unix.txt
	./tests.bash $(INC_DIRS)unix1.txt
	./tests.bash $(INC_DIRS)dos.txt
	./tests.bash $(INC_DIRS)test2.txt
	./tests.bash $(INC_DIRS)CJP.txt

patch:
	git add .
	#git diff --binary origin/main > p1.patch

-include $(DEPS)

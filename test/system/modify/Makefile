SHELL:= bash
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MKFILE_DIR := $(dir $(MKFILE_PATH))

TESTCASE_DIR := $(MKFILE_DIR)testcases/


CPPFLAGS += -isystem $(MKFILE_DIR)../../../include

OBJECT = modify

TESTCASE= $(TESTCASE_DIR)1 \
		  $(TESTCASE_DIR)2


.PHONY: test clean

$(OBJECT): $(OBJECT).cpp
	$(CXX) $(CPPFLAGS) $(OBJECT).cpp -o $@


test: $(OBJECT)
	for testcase in $(TESTCASE); \
	do \
		diff <( ./$(OBJECT) < $${testcase}.in) $${testcase}.out; \
	done


clean:
	rm -rf *.o $(OBJECT)




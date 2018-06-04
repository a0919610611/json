# This Makefile is for test cases only
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MKFILE_DIR := $(dir $(MKFILE_PATH))
# Points to the root of Google Test, relative to where this file is.
GTEST_DIR = $(MKFILE_DIR)google-test/googletest

# Where to find test code.
USER_DIR = ./test/

# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include -isystem $(MKFILE_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -pthread -std=c++11 -O0 -g

COVFLAGS = --coverage

# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# All tests produced by this Makefile.
TESTS = $(USER_DIR)unit-algorithms \
		$(USER_DIR)unit-alt-string \
		$(USER_DIR)unit-capacity \
		$(USER_DIR)unit-concepts \
		$(USER_DIR)unit-merge_patch \
		$(USER_DIR)unit-meta \
		$(USER_DIR)unit-readme \
		$(USER_DIR)unit-reference_access \
		$(USER_DIR)unit-wstring

all :
	@echo "Only support the following"
	@echo "make test_run"

test_run: $(TESTS)
	lcov $(addprefix -a ,$(addsuffix .info, $(TESTS))) $(LCOV_FLAGS) -o final.info
	genhtml -o html final.info

clean:
	rm -f $(TESTS) gtest.a $(USER_DIR)gtest_main.a *.o $(USER_DIR)*.o $(USER_DIR)*.gcov $(USER_DIR)*.gcda $(USER_DIR)*.gcno $(USER_DIR)*.info  final.info
	rm -rf html
# Internal variables.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

$(MKFILE_DIR)gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

$(MKFILE_DIR)gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

$(MKFILE_DIR)gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^
$(MKFILE_DIR)gtest_main.a : $(MKFILE_DIR)gtest-all.o $(MKFILE_DIR)gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

################################
# This is where the fun begins #
################################


$(USER_DIR)%: $(USER_DIR)%.cpp $(MKFILE_DIR)gtest_main.a
	cd test/ && $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(COVFLAGS) -lpthread $(subst test/,,$<) $(MKFILE_DIR)gtest_main.a -o $(subst test/,,$@)
	$@
	cd test/ && lcov $(LCOV_FLAGS) -c -d . -o $(subst test/,,$@)_full.info
	cd test/ && lcov $(LCOV_FLAGS) -r $(subst test/,,$@)_full.info '/usr/lib/*' '/usr/include/*' '$(PWD)/google-test/googletest/include/*' -o $(subst test/,,$@).info

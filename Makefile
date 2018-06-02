# This Makefile is for test cases only

# Points to the root of Google Test, relative to where this file is.
GTEST_DIR = ./google-test/googletest

# Where to find test code.
USER_DIR = ./test/

# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include -I ./

# Flags passed to the C++ compiler.
CXXFLAGS += -pthread -std=c++11

COVFLAGS = -fprofile-arcs -ftest-coverage

# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# All tests produced by this Makefile.
TESTS = $(USER_DIR)unit-simple_test \
		$(USER_DIR)unit-stronger_test

all :
	@echo "Only support the following"
	@echo "make test"
	@echo "make test_run"

test: $(TESTS)

clean:
	rm -f $(TESTS) gtest.a gtest_main.a *.o $(USER_DIR)*.o *.gcov $(USER_DIR)*.gcov *.gcda $(USER_DIR)*.gcda *.gcno $(USER_DIR)*.gcno

# Internal variables.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^
gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

################################
# This is where the fun begins #
################################

$(USER_DIR)%: $(USER_DIR)%.cpp gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(COVFLAGS) -lpthread $^ -o $@


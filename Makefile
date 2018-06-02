# This Makefile is for test cases only

# Points to the root of Google Test, relative to where this file is.
GTEST_DIR = ./google-test/googletest

# Where to find test code.
USER_DIR = ./test/

# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -pthread -std=c++11 -O0

COVFLAGS = -fprofile-arcs -ftest-coverage

# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# All tests produced by this Makefile.
TESTS = $(USER_DIR)unit-simple_test \
		$(USER_DIR)unit-stronger_test

all :
	@echo "Only support the following"
	@echo "make test_run"

test_run: pre $(TESTS)
	lcov $(addprefix -a ,$(addsuffix .info, $(TESTS))) $(LCOV_FLAGS) -o final.info

clean:
	rm -f $(TESTS) gtest.a $(USER_DIR)gtest_main.a *.o $(USER_DIR)*.o $(USER_DIR)*.gcov $(USER_DIR)*.gcda $(USER_DIR)*.gcno $(USER_DIR)*.info

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
	mv gtest_main.a test/

################################
# This is where the fun begins #
################################

pre:
	cp json.hpp test/

$(USER_DIR)%: $(USER_DIR)%.cpp gtest_main.a
	cd test/ && $(CXX) -isystem ../google-test/googletest/include $(CXXFLAGS) $(COVFLAGS) -lpthread $(subst test/,,$<) gtest_main.a -o $(subst test/,,$@)
	$@
	cd test/ && lcov $(LCOV_FLAGS) -c -d . -o $(subst test/,,$@)_full.info
	cd test/ && lcov $(LCOV_FLAGS)-r $(subst test/,,$@)_full.info '/usr/lib/*' '/usr/include/*' '$(PWD)/google-test/googletest/include/*' -o $(subst test/,,$@).info


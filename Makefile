# This Makefile is for test cases only
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MKFILE_DIR := $(dir $(MKFILE_PATH))
# Points to the root of Google Test, relative to where this file is.
GTEST_DIR = $(MKFILE_DIR)google-test/googletest

# Where to find test code.
USER_DIR = ./test/

# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include -isystem $(MKFILE_DIR)include

# Flags passed to the C++ compiler.
CXXFLAGS += -pthread -std=c++11 -O0 -g

COVFLAGS = --coverage

LCOV_FLAGS += --no-recursion --rc lcov_branch_coverage=1


# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# All tests produced by this Makefile.
TESTS = $(USER_DIR)unit-algorithms \
		$(USER_DIR)unit-alt-string \
		$(USER_DIR)unit-capacity \
		$(USER_DIR)unit-cbor \
		$(USER_DIR)unit-class_const_iterator \
		$(USER_DIR)unit-class_iterator \
		$(USER_DIR)unit-class_lexer \
		$(USER_DIR)unit-class_parser \
		$(USER_DIR)unit-comparison \
		$(USER_DIR)unit-conversions \
		$(USER_DIR)unit-concepts \
		$(USER_DIR)unit-constructor1 \
		$(USER_DIR)unit-constructor2 \
		$(USER_DIR)unit-convenience \
		$(USER_DIR)unit-deserialization \
		$(USER_DIR)unit-element_access1 \
		$(USER_DIR)unit-element_access2 \
		$(USER_DIR)unit-inspection \
		$(USER_DIR)unit-items \
		$(USER_DIR)unit-iterators1 \
		$(USER_DIR)unit-iterators2 \
		$(USER_DIR)unit-json_patch \
		$(USER_DIR)unit-json_pointer \
		$(USER_DIR)unit-merge_patch \
		$(USER_DIR)unit-meta \
		$(USER_DIR)unit-modifiers \
		$(USER_DIR)unit-msgpack \
		$(USER_DIR)unit-noexcept \
		$(USER_DIR)unit-pointer_access \
		$(USER_DIR)unit-readme \
		$(USER_DIR)unit-reference_access \
		$(USER_DIR)unit-regression \
		$(USER_DIR)unit-serialization \
		$(USER_DIR)unit-to_chars \
		$(USER_DIR)unit-testsuites\
		$(USER_DIR)unit-ubjson \
		$(USER_DIR)unit-udt \
		$(USER_DIR)unit-unicode \
		$(USER_DIR)unit-wstring


all :
	@echo "Only support the following"
	@echo "make test_run"

test_run: $(TESTS)
	lcov $(addprefix -a ,$(addsuffix .info, $(TESTS))) $(LCOV_FLAGS) --rc lcov_branch_coverage=1 -o final.info
	genhtml --rc genhtml_branch_coverage=1 -o html final.info

clean:
	rm -rf $(TESTS) gtest.a $(USER_DIR)gtest_main.a *.o $(USER_DIR)*.o $(USER_DIR)*.gcov $(USER_DIR)*.gcda $(USER_DIR)*.gcno $(USER_DIR)*.info  final.info
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
	cd test && \
	mkdir -p $(subst test/,,$@) && \
	cp $(subst test/,,$<) $(subst test/,,$@) && \
	cd $(subst test/,,$@) && \
	ln -fs ../../test .	&& \
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(COVFLAGS) -lpthread $(subst test/,,$<) $(MKFILE_DIR)gtest_main.a -o $(subst test/,,$@)  && \
	./$(subst test/,,$@) && \
	lcov $(LCOV_FLAGS)  -c -d . -o ../$(subst test/,,$@)_full.info
	cd test/ && lcov $(LCOV_FLAGS) -e $(subst test/,,$@)_full.info '$(MKFILE_DIR)include/json.hpp' -o $(subst test/,,$@).info


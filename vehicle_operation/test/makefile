#Unit Test code directory
TARGET = tpms_oem_utest.exe
TST_SRCS_DIR = ./
TST_OBJS_DIR = ./
TST_BIN_DIR	 = ./

#Unit under Testing directory
TGT_SRCS_DIR = ../
TGT_INCS_DIR = ../

#Google test libraries and headers
TEST_HARNESS_DIR 	= $(PROJECT_DIR)/gtest
GTEST_HDRS		= $(TEST_HARNESS_DIR)/Export/include/
GMOCK_HDRS		= $(TEST_HARNESS_DIR)/Export/include/
GTEST_LIB_DIR	= $(TEST_HARNESS_DIR)/Export/
GMOCK_LIB_DIR	= $(TEST_HARNESS_DIR)/Export/

#Unit test source code, objs and exe
TST_SRCS = $(wildcard $(TST_SRCS_DIR)*.cc)
TST_OBJS = $(patsubst $(TST_SRCS_DIR)%.cc,$(TST_OBJS_DIR)%.o,$(TST_SRCS))
TST_BIN  = $(TST_BIN_DIR)$(TARGET)

# unit under test sourcecode
TGT_SRCS = $(wildcard $(TGT_SRCS_DIR)*.cpp) 
TGT_OBJS = $(patsubst $(TGT_SRCS_DIR)%.cpp,$(TST_OBJS_DIR)%.o,$(TGT_SRCS))

# Flags
# preprocessing Flags
CPPFLAGS += -I$(GTEST_HDRS) -I$(GMOCK_HDRS) -I$(TGT_INCS_DIR) -DUNIT_TEST
#Linker`s Flags
#gmock has symbols needed by gtest apparently, so the gmock (unknown symbols) 
#shall be linked before gtest
LDFLAGS += -L$(GTEST_LIB_DIR) -L$(GMOCK_LIB_DIR) -lgmock -lgmock_main -lgtest -lgtest_main

.PHONY: retest test clean 

retest: clean test

test: build
	./$(TARGET)
	
build: $(TST_BIN)

$(TST_BIN): $(TGT_OBJS) $(TST_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@ -l:state_chart.a

$(TGT_OBJS): $(TGT_SRCS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $^ 
	
$(TST_OBJS): $(TST_SRCS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $^ 
	
clean:
	rm -f $(TGT_OBJS) $(TST_OBJS)
	rm -f $(TST_BIN)
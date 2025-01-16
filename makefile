Q = 
PROJECT_DIR := $(CURDIR)

# build directory
PATHB = $(PROJECT_DIR)/build
PATHO = $(PATHB)/objs
PATHA = $(PATHB)/archives
PATHE = $(PATHB)/bin

# Tool Definitions
CXX = g++
CXXFLAGS = -std=c++11 -O0 -Wall -Wextra -pthread
CPPFLAGS = -I$(PROJECT_DIR)/utils -I$(PROJECT_DIR)/state_chart -I$(PROJECT_DIR)/vehicle_operation
LDFLAGS = -L$(PATHA)

# Pass the variable to recursive calls
export PROJECT_DIR PATHB PATHO PATHA PATHE CXX CXXFLAGS CPPFLAGS LDFLAGS

TGT = $(PATHE)/main.exe

# Targets
.PHONY: test run retest build clean rebuild

retest:
	# $(Q) $(MAKE) retest -C ./state_chart/test
	$(Q) $(MAKE) retest -C ./vehicle_operation/test

test:
	# $(Q) $(MAKE) retest -C ./state_chart/test
	$(Q) $(MAKE) retest -C ./vehicle_operation/test

rebuild: clean build

build:
	$(Q) $(MAKE) build -C ./state_chart
	$(Q) $(MAKE) build -C ./vehicle_operation
	$(Q) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) main.cpp -o $(TGT) -l:state_chart.a -l:vehicle_operation.a

clean:
	$(Q) rm -f $(PATHA)/*.*
	$(Q) rm -f $(PATHO)/*.*
	$(Q) rm -f $(PATHE)/*.*

run:
	$(Q) $(PATHE)/main.exe $(ARGS)
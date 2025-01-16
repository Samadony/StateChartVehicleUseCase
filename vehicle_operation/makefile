#We try to detect the OS we are running on, and adjust commands as needed
CLEANUP = rm -f
MKDIR = mkdir

#Path Definitions
PATHS = .
PATHI = .

SRCS = $(wildcard $(PATHS)/*.cpp)
OBJS = $(patsubst $(PATHS)/%.cpp,$(PATHO)/%.o,$(SRCS))
TGT = $(PATHA)/vehicle_operation.a

.PHONY: rebuild build clean

rebuild: build
	
build: $(TGT)
	
$(TGT) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(PATHO)/%.o: $(PATHS)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
#We try to detect the OS we are running on, and adjust commands as needed
CLEANUP = rm -f
MKDIR = mkdir

#Path Definitions
PATHS = .
PATHI = .

SRCS = $(wildcard $(PATHS)/*.cpp)
OBJS = $(patsubst $(PATHS)/%.cpp,$(PATHO)/%.o,$(SRCS))
TGT = $(PATHA)/state_chart.a

.PHONY: rebuild build clean

rebuild: build
	
build: $(TGT)
	
$(TGT) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $^ -o $@
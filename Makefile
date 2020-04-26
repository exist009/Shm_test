CXX = $(CROSS_COMPILE)c++
CXXFLAGS = -std=c++17 -O2

WFLAGS += -Wall
WFLAGS += -Wextra
WFLAGS += -Wpedantic
WFLAGS += -Wcast-align
WFLAGS += -Wctor-dtor-privacy
WFLAGS += -Wdisabled-optimization
WFLAGS += -Winit-self
WFLAGS += -Wlogical-op
WFLAGS += -Wmissing-declarations
WFLAGS += -Wnoexcept
WFLAGS += -Woverloaded-virtual
WFLAGS += -Wredundant-decls
WFLAGS += -Wshadow
WFLAGS += -Wstrict-null-sentinel
WFLAGS += -Wstrict-overflow=5
WFLAGS += -Wundef
WFLAGS += -Weffc++
WFLAGS += -Wcast-qual
WFLAGS += -Wsign-promo
WFLAGS += -Wformat=1
WFLAGS += -Wswitch-default
WFLAGS += -Wold-style-cast
WFLAGS += -Wno-uninitialized
WFLAGS += -Wno-strict-overflow
WFLAGS += -Wno-cast-align
WFLAGS += -Wno-attributes

LDFLAGS += -I../Shm/ -L../Shm/ -Wl,-rpath=../Shm/ -lshm

%:%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

all: reader writer

clean:
	rm -f *.o
	rm -f ./reader
	rm -f ./writer

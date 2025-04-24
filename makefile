ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=out
endif

# A phony target is one that is not really the name of a file; rather it is just a name for a recipe to be executed when you make an explicit request.
# There are two reasons to use a phony target: to avoid a conflict with a file of the same name, and to improve performance.
# If you write a rule whose recipe will not create the target file, the recipe will be executed every time the target comes up for remaking. Here is an example: 
.PHONY: clean
.PHONY: test
.PHONY: all

LIBS = -lm 
CC=g++
###
CFLAGS += -g
CFLAGS += -Wall 
#CFLAGS += --std=c++17
CFLAGS += --std=c++20
#CFLAGS +=  -fno-elide-constructors

LDFLAGS += -Wl,-Map=hello.map


ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

INCLUDE_DIRS = -Isrc

SRC_ROOT=src/
PATHO=build/objs
PATHB=.

SRC_DIRS = $(sort $(dir $(wildcard $(SRC_ROOT)/*/))) $(SRC_ROOT)
CPP_SOURCES = $(wildcard $(SRC_ROOT)*.cpp)
CPP_OBJS = $(patsubst %.cpp,$(PATHO)/$(basename %).o,$(CPP_SOURCES))

.PHONY: all
#	$(CC) $(CFLAGS) -S src/*.cpp -o $(OBJDIR)/$*.asm $(INCLUDE_PATHS) -masm=intel
all: $(PATHB) $(PATHO)
	@echo "$(SRC_DIRS)"
	@echo "$(CPP_SOURCES)"
	@echo "$(CPP_OBJS)"
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) src/*.cpp -o hello.out -static-libstdc++ $(LDFLAGS)

$(PATHB):
	$(MKDIR) $(PATHB)
	
$(PATHO):
	$(MKDIR) $(PATHO)

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM

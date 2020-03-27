C_COMPILER=gcc

CFLAGS=-std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CFLAGS += -g

SRC_FILES1=\
  src/main.c \
  lib/conio/conio.h \
  lib/conio/conio.c

TARGET_BASE1=myProject
TARGET_EXTENSION=.exe
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)

SRC_FILES2=\
  src/sdl-test.c

TARGET_BASE2=sdlTest
TARGET_EXTENSION=.exe
TARGET2 = $(TARGET_BASE2)$(TARGET_EXTENSION)

default2:
	$(C_COMPILER) -g $(CFLAGS) $(SRC_FILES1) -o $(TARGET1)
	- ./$(TARGET1) -v

default:
	$(C_COMPILER) -g $(CFLAGS) $(SRC_FILES2) -o $(TARGET2)
	- ./$(TARGET2) -v
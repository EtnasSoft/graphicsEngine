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
  src/ProductionCode.c

TARGET_BASE1=myProject
TARGET_EXTENSION=.exe
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)

default:
	$(C_COMPILER) -g $(CFLAGS) $(SRC_FILES1) -o $(TARGET1)
	- ./$(TARGET1) -v
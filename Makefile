TARGET = fucktro
OBJS = src/main.o src/modplayer.o 

INCDIR = src
CFLAGS = -O2 -G0 -Wall -fpermissive
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -std=gnu++26
ASFLAGS = $(CFLAGS)

LIBDIR = src
LIBS = -lpspaudiolib -lpspaudio
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = WAB FucKTro
PSP_EBOOT_ICON = ICON.PNG

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


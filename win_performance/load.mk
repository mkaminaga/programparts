# makefile
# date 2019-10-12 14:22:26
# Copyright 2019 Mamoru Kaminaga
CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

OBJDIR = build
TARGET = load.exe
SRC = load.cc
OBJ = $(OBJDIR)/load.obj

CPPFLAGS = /nologo /W4 /Zi /Od /D"UNICODE" /D"_UNICODE" /EHsc /Fd"$(OBJDIR)/"
LFLAGS = "kernel32.lib" "user32.lib" /NOLOGO /SUBSYSTEM:WINDOWS

ALL: $(TARGET)

$(TARGET): $(OBJ) $(RES)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) $(OBJ) $(RES)

.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<

clean:
	rm $(OBJ) $(TARGET) *.map *.pdb *.ilk *.obj *.lib *.dll *.exp

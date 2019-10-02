#
# Makefile
# Date 2019-09-21 18:22:39
# Copyright 2019 Mamoru Kaminaga
#
TARGET = ScreenCaptureTool.exe
PDB = ScreenCaptureTool.pdb
MAP = ScreenCaptureTool.map
RES = resource.res
TMPDIR = build
SRC = main.cc folder_dialog.cc png_tool.cc util.cc capture.cc  task_tray.cc\
			key_hook.cc
OBJ = $(TMPDIR)\main.obj $(TMPDIR)\folder_dialog.obj $(TMPDIR)\png_tool.obj \
			$(TMPDIR)\util.obj $(TMPDIR)\capture.obj $(TMPDIR)\task_tray.obj
DLL = key_hook.dll
MYLIB = key_hook.lib

CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

!if 1
# Release mode.
CPPFLAGS = /nologo /W4 /Zi /O1 /MT /EHsc /Fd"$(TMPDIR)/"\
					 /D"UNICODE" /D"_UNICODE" /EHsc /I"$(LIBRARIES)\libpng"
LIBS = "kernel32.lib" "user32.lib" "gdi32.lib" "shell32.lib" "ole32.lib"
LFLAGS = $(LIBS)\
				 "$(LIBRARIES)\libpng\projects\visualc71\Win32_LIB_Release\libpng.lib" \
				 "$(LIBRARIES)\libpng\projects\visualc71\Win32_LIB_Release\ZLib\zlib.lib"\
				 /NOLOGO /SUBSYSTEM:WINDOWS
!else
# Debug mode.
CPPFLAGS = /nologo /W4 /Zi /MTd /EHsc /Fd"$(TMPDIR)/"\
					 /D"UNICODE" /D"_UNICODE" /EHsc /I"$(LIBRARIES)\libpng"\
					 /D"DEBUG"
LIBS = "kernel32.lib" "user32.lib" "gdi32.lib" "shell32.lib" "ole32.lib"
LFLAGS = $(LIBS)\
				 "$(LIBRARIES)\libpng\projects\visualc71\Win32_LIB_Debug\libpngd.lib" \
				 "$(LIBRARIES)\libpng\projects\visualc71\Win32_LIB_Debug\ZLib\zlibd.lib"\
				 /NOLOGO /SUBSYSTEM:WINDOWS /PROFILE /DEBUG /PDB:"$(PDB)" /MAP:"$(MAP)"
!endif

ALL: $(TARGET)

$(TARGET): $(OBJ) $(MYLIB) $(DLL) $(RES)
	$(LINK) $(MYLIB) $(LIBS) $(LFLAGS) /OUT:$(TARGET) /PDB:$(PDB)\
		/MAP:$(MAP) $(OBJ) $(RES)

.cc{$(TMPDIR)}.obj:
	@[ -d $(TMPDIR) ] || mkdir $(TMPDIR)
	$(CC) $(CPPFLAGS) /Fo"$(TMPDIR)\\" /c $<

.cc.lib:
	$(CC) $(CPPFLAGS) /LD $(LIBS) $<

clean:
	rm -f $(OBJ)
	rm -f $(TARGET)
	rm -f $(TMPDIR)/*
	rm -f *.dll
	rm -f *.exe
	rm -f *.exp
	rm -f *.ilk
	rm -f *.lib
	rm -f *.map
	rm -f *.obj
	rm -f *.pdb
	rm -f *.png

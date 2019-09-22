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
CPPFLAGS = /nologo /W4 /Zi /O2 /MT /EHsc /Fd"$(TMPDIR)/"\
					 /D"UNICODE" /D"_UNICODE" /EHsc /I"$(LIBRARIES)\libpng"
LIBS = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib"\
			 "advapi32.lib" "shell32.lib" "ole32.lib"	"oleaut32.lib" "uuid.lib"\
			 "odbc32.lib" "libcmt.lib"
LFLAGS = $(LIBS)\
				 "$(LIBRARIES)\libpng\projects\visualc71\Win32_LIB_Release\libpng.lib" \
				 "$(LIBRARIES)\libpng\projects\visualc71\Win32_LIB_Release\ZLib\zlib.lib"\
				 /NOLOGO /SUBSYSTEM:WINDOWS
!else
# Debug mode.
CPPFLAGS = /nologo /W4 /Zi /O2 /MTd /EHsc /Fd"$(TMPDIR)/"\
					 /D"UNICODE" /D"_UNICODE" /EHsc /I"$(LIBRARIES)\libpng"\
					 /D"DEBUG" /DEBUG
LIBS = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib"\
			 "advapi32.lib" "shell32.lib" "ole32.lib"	"oleaut32.lib" "uuid.lib"\
			 "odbc32.lib" "libcmtd.lib"
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
	rm $(OBJ)
	rm $(TARGET)\*
	rm *.dll
	rm *.exe
	rm *.exp
	rm *.ilk
	rm *.lib
	rm *.map
	rm *.obj
	rm *.pdb

# Makefile_header
# http://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html#Automatic-Prerequisites

PROGRAM = main
SRC = main.c graphics.c screen_cache.c
OBJS = $(patsubst %.c,%.o,${SRC})
DEPENDS = $(patsubst %.c,%.d,${SRC})

CC = gcc
CFLAGS = -Wall -DX_MAX=30 -DY_MAX=15
LDFLAGS =

${PROGRAM}: ${OBJS}
	${CC} -o $@ $(notdir ${OBJS})

.c.o:
	${CC} ${CFLAGS} ${LDFLAGS} -c $<

.PHONY: clean depend
clean:
	-${RM} ${PROGRAM} $(notdir ${OBJS}) $(notdir ${DEPENDS})

%.d: %.c
	@set -e; ${CC} -M ${CPPFLAGS} $< \
		| echo generating $(notdir $*).d

-include $(DEPENDS)

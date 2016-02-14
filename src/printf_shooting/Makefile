# Makefile_header
# http://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html#Automatic-Prerequisites

PROGRAM = main
SRC = main.c game.c screen_cache.c
OBJS = $(patsubst %.c,%.o,${SRC})
DEPENDS = $(patsubst %.c,%.d,${SRC})

CC = gcc
CFLAGS = -Wall -DX_MAX=18 -DY_MAX=8
LDFLAGS =

${PROGRAM}: ${OBJS}
	${CC} -o $@ $(notdir ${OBJS})

.c.o:
	${CC} ${CFLAGS} ${LDFLAGS} -c $<

.PHONY: clean depend
clean:
	-${RM} ${PROGRAM} $(notdir ${OBJS}) $(notdir ${DEPENDS})

%.d: %.c
	@set -e; $(CC) -M ${CPPFLAGS} $< \
		| sed -e 's/"$*\.o[ :]*"/"$*\.o $@ : "/g' > $(notdir $@);
-include $(DEPENDS)

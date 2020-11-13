TESTBIN:=\
	001-loadfile.test \
	002-loadconfig.test \
	003-loadconfig-errors.test \
	004-passml.test \
	005-number-appender.test \
	006-charset-appender.test \
	007-dictionary-appender.test \
	008-interact.test

CPP:=g++

CFLAGS:=\
	-Wall

BOLD:=\033[1m
NORM:=\033[0m
REDD:=\033[31m
GREN:=\033[32m
BLUE:=\033[34m
YLLW:=\033[33m

NEEDCLEAN:=*.test *.o *.gch

ifdef VERBOSE
	HUSH:=
	FROM:=" from $^"
else
	HUSH:=@
	FROM:=
endif

ifdef DEBUG
	CFLAGS=$(CFLAGS) -g
endif

all::$(TESTBIN)

.PRECIOUS: %.o

.PHONY: clean

# CREAR EL OBJETO SI EXISTE EL CPP
%.o: %.cpp %.hpp
	@echo "$(NORM)$(YLLW) □ $(NORM) $(NORM)CMP $@ $(NORM) $(FROM)"
	$(HUSH)$(CPP) -c $^

%.o: %.cpp
	@echo "$(NORM)$(YLLW) □ $(NORM) $(NORM)CMP $@ $(NORM) $(FROM)"
	$(HUSH)$(CPP) -c $^

# CREAR EL TEST SI ESTÁN TODOS LOS OBJETOS
%.test: %.o passgen.o tinyxml2.o chainsaws.o
	@echo "$(BOLD)$(GREN) ■ $(NORM) $(BOLD)GEN $@ $(NORM) $(FROM)"
	$(HUSH)$(CPP) -o $@ $^

clean:
	@echo "$(BOLD)$(REDD) ■ $(NORM) $(BOLD)DEL $(NEEDCLEAN)"
	-$(HUSH)rm -f $(NEEDCLEAN)

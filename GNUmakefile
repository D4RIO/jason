TESTBIN:=\
	001-loadfile.test

CPP:=g++

CFLAGS:=\
	-Wall

all:$(TESTBIN)

# CREAR EL OBJETO SI EXISTE EL CPP
%.o: %.cpp
	@echo COMP $@ from $<
	$(CPP) -c $<

# CREAR EL TEST SI ESTÁN TODOS LOS OBJETOS
%.test: %.o passgen.o
	@echo siii
	$(CPP) -o $@ $?

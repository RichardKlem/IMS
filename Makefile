# @author: Richard Klem
# @email: xklemr00@stud.fit.vutbr.cz
# @login: xklemr00

.PHONY: all run prog cleanall
SOURCES= main.cpp main.h my_string.cpp my_string.h CellularAutomaton.cpp CellularAutomaton.h Matrix.h Cell.h Person.h

all: $(SOURCES)
	g++ -Wextra -Wall -pedantic -o ebola main.cpp my_string.cpp CellularAutomaton.cpp


run:
	sudo ./covid

cleanall:
	rm  covid

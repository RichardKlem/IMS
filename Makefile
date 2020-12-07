# @author: Richard Klem
# @email: xklemr00@stud.fit.vutbr.cz
# @login: xklemr00

CXXFLAGS = -Wall -Wextra -pedantic -std=c++17
CC = g++
SOURCES= main.cpp main.h my_string.cpp my_string.h CellularAutomaton.h Matrix.h Cell.h Person.h utils.h
OUTDIR="outputs"
.PHONY: all run cleanall all_exp visualize install_req_all_exp install_req_vis

all: $(SOURCES)
	$(CC) $(CXXFLAGS) -o covid main.cpp my_string.cpp

run:
	mkdir -p $(OUTDIR)
	./covid -d $(OUTDIR)

cleanall:
	rm  covid

visualize: install_req_vis
	cd visualization && python3 visualize.py

all_exp: install_req_all_exp
	cd experiments && python3 run_experiment.py

install_req_all_exp:
	python3 -m pip install -r experiments/requirements.txt

install_req_vis:
	python -m pip install -r visualization/requirements.txt
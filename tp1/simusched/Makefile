export LC_ALL=C
CXXFLAGS= -O3 -Wall -Wextra -pedantic -g -ggdb -std=c++14
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_sjf.o sched_rsjf.o sched_mfq.o
MAIN=simusched

OUT_DIR=out

.PHONY: all clean new
all: $(OUT_DIR) $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ejercicio1: $(MAIN) tasks/ej1.tsk
	./simusched tasks/lote.tsk 1 1 1 SchedFCFS \
		| python2 ./graphsched.py > $(OUT_DIR)/ej1.png

ejercicio2:
	@echo "No implementado"
	@exit 1

ejercicio3:
	@echo "No implementado"
	@exit 1

ejercicio4:
	@echo "No implementado"
	@exit 1

ejercicio5:
	@echo "No implementado"
	@exit 1

ejercicio6:
	@echo "No implementado"
	@exit 1

ejercicio7:
	@echo "No implementado"
	@exit 1

ejercicio8:
	@echo "No implementado"
	@exit 1

ejercicio9:
	@echo "No implementado"
	@exit 1

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
	sched_mfq.h sched_rr.h sched_rsjf.h sched_sjf.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

$(OUT_DIR):
	mkdir -p $@

clean:
	rm -fr out/*
	rm -f $(OBJS) $(MAIN)

new: clean all

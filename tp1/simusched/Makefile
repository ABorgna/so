export LC_ALL=C
CXXFLAGS= -O3 -Wall -Wextra -pedantic -g -ggdb -std=c++14
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_sjf.o sched_rsjf.o sched_mfq.o
MAIN=simusched

OUT_DIR=out

EJERCICIOS_N = 1 2 3 4 5 6 7 8 9
EJERCICIOS = $(EJERCICIOS_N:%=ejercicio%)

.PHONY: all clean new $(EJERCICIOS)
all: $(OUT_DIR) $(MAIN)

ejercicios: $(EJERCICIOS)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ejercicio1: $(MAIN) tasks/ej1.tsk
	./simusched tasks/ej1.tsk 1 1 1 SchedFCFS \
		| python2 ./graphsched.py > $(OUT_DIR)/ej1.png

ejercicio2: $(MAIN) tasks/ej2.tsk
	./simusched tasks/ej2.tsk 1 1 2 SchedFCFS \
		| python2 ./graphsched.py > $(OUT_DIR)/ej2.1.png
	./simusched tasks/ej2.tsk 2 1 2 SchedFCFS \
		| python2 ./graphsched.py > $(OUT_DIR)/ej2.2.png
	./simusched tasks/ej2.tsk 4 1 2 SchedFCFS \
		| python2 ./graphsched.py > $(OUT_DIR)/ej2.4.png

ejercicio3: $(MAIN) tasks/ej3.tsk
	./simusched tasks/ej3.tsk 1 1 1 SchedFCFS \
		| python2 ./graphsched.py > $(OUT_DIR)/ej3.png

ejercicio4: $(MAIN) tasks/ej4.tsk
	./simusched tasks/ej4.tsk 1 1 1 SchedRR 4 \
		| python2 ./graphsched.py > $(OUT_DIR)/ej4.png

ejercicio5: $(MAIN)
	@echo "No implementado"
	@exit 1

ejercicio6: $(MAIN)
	@echo "No implementado"
	@exit 1

ejercicio7: $(MAIN)
	@echo "No implementado"
	@exit 1

ejercicio8: $(MAIN)
	@echo "No implementado"
	@exit 1

ejercicio9: $(MAIN)
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

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

ejercicio1: $(OUT_DIR)/ej1.png
$(OUT_DIR)/ej1.png: tasks/ej1.tsk $(MAIN)
	./simusched $< 1 1 1 SchedFCFS \
		| python2 ./graphsched.py > $@

ejercicio2: $(OUT_DIR)/ej2-1.png $(OUT_DIR)/ej2-2.png $(OUT_DIR)/ej2-4.png
$(OUT_DIR)/ej2-1.png: tasks/ej2.tsk $(MAIN)
	./simusched $< 1 2 2 SchedFCFS \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej2-2.png: tasks/ej2.tsk $(MAIN)
	./simusched $< 2 2 2 SchedFCFS \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej2-4.png: tasks/ej2.tsk $(MAIN)
	./simusched $< 4 2 2 SchedFCFS \
		| python2 ./graphsched.py > $@

ejercicio3: $(OUT_DIR)/ej3.png
$(OUT_DIR)/ej3.png: tasks/ej3.tsk $(MAIN)
	./simusched $< 1 1 1 SchedFCFS \
		| python2 ./graphsched.py > $@

ejercicio4: $(OUT_DIR)/ej4.png
$(OUT_DIR)/ej4.png: tasks/ej4.tsk $(MAIN)
	./simusched $< 1 1 1 SchedRR 4 \
		| python2 ./graphsched.py > $@

ejercicio5: $(OUT_DIR)/ej5-2.png $(OUT_DIR)/ej5-5.png $(OUT_DIR)/ej5-10.png
$(OUT_DIR)/ej5-2.png: tasks/ej5.tsk $(MAIN)
	./simusched $< 1 2 1 SchedRR 2 \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej5-5.png: tasks/ej5.tsk $(MAIN)
	./simusched $< 1 2 1 SchedRR 5 \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej5-10.png: tasks/ej5.tsk $(MAIN)
	./simusched $< 1 2 1 SchedRR 10 \
		| python2 ./graphsched.py > $@

ejercicio6: $(MAIN)

ejercicio7: $(OUT_DIR)/ej7-sjf.png $(OUT_DIR)/ej7-rsjf.png
$(OUT_DIR)/ej7-sjf.png: tasks/ej7.tsk $(MAIN)
	./simusched $< 1 1 1 SchedSJF 10 9 2 \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej7-rsjf.png: tasks/ej7.tsk $(MAIN)
	./simusched $< 1 1 1 SchedRSJF 4 10 9 2 \
		| python2 ./graphsched.py > $@

ejercicio8: $(MAIN) $(OUT_DIR)/ej8-cpu-rr.png $(OUT_DIR)/ej8-cpu-rr-m.png \
					$(OUT_DIR)/ej8-cpu-fcfs.png $(OUT_DIR)/ej8-cpu-fcfs-m.png \
					$(OUT_DIR)/ej8-cpu-sjf.png $(OUT_DIR)/ej8-cpu-sjf-m.png \
					$(OUT_DIR)/ej8-cpu-rsjf.png $(OUT_DIR)/ej8-cpu-rsjf-m.png
$(OUT_DIR)/ej8-cpu-rr.png: tasks/ej8-cpu.tsk $(MAIN)
	./simusched $< 1 1 2 SchedRR 4 \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej8-cpu-rr-m.png: tasks/ej8-cpu.tsk $(MAIN)
	./simusched $< 2 1 2 SchedRR 4 4 \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej8-cpu-fcfs.png: tasks/ej8-cpu.tsk $(MAIN)
	./simusched $< 1 1 2 SchedFCFS \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej8-cpu-fcfs-m.png: tasks/ej8-cpu.tsk $(MAIN)
	./simusched $< 2 1 2 SchedFCFS \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej8-cpu-sjf.png: tasks/ej8-cpu.tsk $(MAIN)
	./simusched $< 1 1 2 SchedSJF 10 20 5 5 5 \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej8-cpu-sjf-m.png: tasks/ej8-cpu.tsk $(MAIN)
	./simusched $< 2 1 2 SchedSJF 10 20 5 5 5 \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej8-cpu-rsjf.png: tasks/ej8-cpu.tsk $(MAIN)
	./simusched $< 1 1 2 SchedRSJF 4 10 20 5 5 5 \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej8-cpu-rsjf-m.png: tasks/ej8-cpu.tsk $(MAIN)
	./simusched $< 2 1 2 SchedRSJF 4 4 10 20 5 5 5 \
		| python2 ./graphsched.py > $@

ejercicio9: $(OUT_DIR)/ej9-1.png $(OUT_DIR)/ej9-2.png

$(OUT_DIR)/ej9-1.png: tasks/ej9-1.tsk $(MAIN)
	./simusched $< 1 1 1 SchedMFQ 2 4 6 \
		| python2 ./graphsched.py > $@
$(OUT_DIR)/ej9-2.png: tasks/ej9-2.tsk $(MAIN)
	./simusched $< 2 1 1 SchedMFQ 2 3 4 \
		| python2 ./graphsched.py > $@

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

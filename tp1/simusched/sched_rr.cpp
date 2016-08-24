#include "sched_rr.h"
#include <iostream>
#include <queue>
#include <vector>
#include "basesched.h"

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
    // Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
    int cpus = argn[0];

    quantum_total.reserve(cpus);
    quantum_restante.reserve(cpus);

    for(int i=0; i<cpus; i++) {
        quantum_total.push_back(argn[i+1]);
        quantum_restante.push_back(0);
    }
}

SchedRR::~SchedRR() {}

void SchedRR::load(int pid) {
    q.push(pid);
}

void SchedRR::unblock(int pid) {
    q.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
    int pid = current_pid(cpu);

    // Si es un tick, disminuye quantum
    if (m == TICK) {
        quantum_restante[cpu]--;
        if (quantum_restante[cpu] > 0) {
            return pid;
        }
        if(q.empty()) {
            quantum_restante[cpu] = quantum_total[cpu];
            return pid;
        }
    }

    // Si no hay otra tarea a la que saltar sigo
    if (m == BLOCK && q.empty()) {
        return pid;
    }

    // Si estoy corriendo alguna tarea, la encolo
    // un EXIT o un BLOCK no tiene que agregarla
    if (m == TICK && pid != IDLE_TASK) {
        q.push(pid);
    }

    // Sched no tiene a nadie para asignarle al cpu actual
    if (q.empty()) {
        return IDLE_TASK;
    }

    // Saco un elemento de la cola y reinicio quantums
    int nuevo_pid = q.front();
    q.pop();
    quantum_restante[cpu] = quantum_total[cpu];

    return nuevo_pid;
}

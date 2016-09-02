#include "sched_rsjf.h"

using namespace std;

SchedRSJF::SchedRSJF(vector<int> argn) {
    // Recibe la cantidad de cores y sus cpu_quantum por parámetro
    /* llenar */
    int cant_cpus = argn[0];

    quantum_total.reserve(cant_cpus);
    quantum_restante.reserve(cant_cpus);

    for (int i = 1; i <= cant_cpus; i++) {
        quantum_total[i - 1] = argn[i];
        quantum_restante[i - 1] = 0;
    }

    for (int i = cant_cpus + 1; (unsigned)i < argn.size(); i++)
        tiempos[i - (cant_cpus + 1)] = argn[i];
}

SchedRSJF::~SchedRSJF() { /* llenar */
}

void SchedRSJF::load(int pid) {
    int tiempo_pid = tiempos[pid];
    espera.push({tiempo_pid, pid});
}

void SchedRSJF::unblock(
    __attribute__((unused)) int pid) { /* //Por enunciado m != BLOCK */
}

int SchedRSJF::tick(int core, const enum Motivo m) {
    // Por enunciado m != BLOCK

    int pid = current_pid(core);

    // Si es un tick, disminuye quantum
    if (m == TICK) {
        quantum_restante[core]--;
        tiempos[pid]--;
        if (quantum_restante[core] > 0) {
            return pid;
        }
        if (espera.empty() && pid != IDLE_TASK) {
            quantum_restante[core] = quantum_total[core];
            return pid;
        }
    }

    // Si estoy corriendo alguna tarea, la encolo
    // un EXIT no tiene que agregarla
    if (m == TICK && pid != IDLE_TASK) {
        espera.push({tiempos[pid], pid});
    }

    // Sched no tiene a nadie para asignarle al cpu actual
    if (espera.empty()) {
        return IDLE_TASK;
    }

    // Saco el minimo (head) del set<tiempo, pid> y reinicio quantums
    auto menor_tiempo = espera.top();
    espera.pop();

    quantum_restante[core] = quantum_total[core];

    return menor_tiempo.second;
}

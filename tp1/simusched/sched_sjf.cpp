#include "sched_sjf.h"
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

SchedSJF::SchedSJF(vector<int> argn) {
    // Recibe la cantidad de cores
    /* llenar */
    // arg[0] cant cores
    // arg[1..argn.size()] duracion de pid [0..argn.size())

    for (int i = 1; (unsigned)i < argn.size(); i++) tiempos[i - 1] = argn[i];
}

SchedSJF::~SchedSJF() { /* llenar */
}

void SchedSJF::load(int pid) {
    int tiempo_pid = tiempos[pid];
    espera.push({tiempo_pid, pid});
}

void SchedSJF::unblock(__attribute__((unused)) int pid) { /* llenar */
}

int SchedSJF::tick(int cpu, const enum Motivo m) {
    // Por enunciado m != BLOCK

    if (m == EXIT && espera.empty()) {
        return IDLE_TASK;
    } else if (m == TICK) {
        if(current_pid(cpu) != IDLE_TASK) {
            return current_pid(cpu);
        } else if(espera.empty()) {
            return IDLE_TASK;
        }
    }

    auto menor_tiempo = espera.top();
    espera.pop();
    return menor_tiempo.second;
}

#include "sched_rr.h"
#include <iostream>
#include <queue>
#include <vector>
#include "basesched.h"

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
    // Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
    quantum_total = argn;
    quantum_restante = argn;

    for (int i = 0; (unsigned)i < argn.size() ; i++) {
      vacios.insert(i);
    }
}

void SchedRR::load(int pid) {
    q.push(pid);
}

void SchedRR::unblock(int pid) {
    q.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {

    //Si no hay otra tarea a la que saltar sigo
    if ((m == BLOCK || m == TICK) && q.empty()){
      return current_pid(cpu);
    }

    //Si es un tick y hay otras tareas, disminuye quantum
    if (m == TICK && !q.empty()){
      quantum_restante[cpu]--;
      if (quantum_restante[cpu] > 0) return current_pid(cpu);
    }

    //Si estoy corriendo alguna tarea, la encolo
    if(current_pid(cpu) != IDLE_TASK){
      q.push(current_pid(cpu));
    }

    //Sched no tiene a nadie para asignarle al cpu actual
    if(q.empty()) {
      vacios.insert(cpu);
      return IDLE_TASK;
    }

    //Saco un elemento de la cola y reinicio quantums
    int nuevo_pid = q.front();
    q.pop();
    quantum_restante[cpu] = quantum_total[cpu];

    //Si cargué una tarea a un core, lo saco de vacíos
    auto itVacio = vacios.find(cpu);
    if(itVacio == vacios.end()) {
      vacios.erase(itVacio);
    }

    return nuevo_pid;
}

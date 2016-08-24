#include "sched_rr.h"
#include <iostream>
#include <queue>
#include <vector>
#include "basesched.h"

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
    // Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
}

void SchedRR::load(int pid) {
    q.push(pid);
}

void SchedRR::unblock(int pid) {
    q.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
    if ((m == BLOCK || m == TICK) && q.empty()){
      return current_pid();
    }
    
    if(current_pid() != IDLE_TASK) q.push(current_pid());
    
    if(q.empty()) {
      vacios.insert(cpu);
      return IDLE_TASK;
    }
    
    int nuevo_pid = q.pop();
    
    auto itVacio = vacios.find(cpu);
    if(itVacio == vacios.end()) {
      vacios.erase(itVacio);
    }
      
    return nuevo_pid;
}

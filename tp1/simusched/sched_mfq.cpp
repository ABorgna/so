#include "sched_mfq.h"
#include <queue>
#include <vector>
#include "basesched.h"

using namespace std;

// Funciones Auxiliares

// Devuelvo si estan todas las colas vacias o no
bool colasVacias(QueueArray colas) {
    for (unsigned int i = 0; i < colas.size(); i++) {
        if (!colas[i].empty())
            return false;
    }
    return true;
}

// Devuelvo en que cola estuvo por ultimo vez pid
int cualCola(int pid, SetArray laUltimaColaVisitada) {
    for (unsigned int i = 0; i < laUltimaColaVisitada.size(); i++) {
        std::set<int>::iterator it = laUltimaColaVisitada[i].find(pid);
        if (it != laUltimaColaVisitada[i].end()) {
            return i;
        }
    }
    return -1;
}

// Devuelvo la primer cola que no este vacia
int primerColaNoVacia(QueueArray colas) {
    for (unsigned int i = 0; i < colas.size(); i++) {
        if (!colas[i].empty()) {
            return i;
        }
    }
    return -1;
}

SchedMFQ::SchedMFQ(vector<int> argn) {
    // MFQ recibe la cantidad de cores y luego los quantums de las pilas por
    // parámetro
    int cantColas = argn.size() - 1;
    int cantCores = argn[0];
    colas.reserve(cantColas);
    quantums.reserve(cantColas);

    quantumsRestantes = std::vector<int>(cantCores, 0);

    for (int i = 0; i < cantColas; i++) {
        quantums.push_back(argn[i + 1]);
        colas.push_back(std::queue<int>());
        laUltimaColaVisitada.push_back(std::set<int>());
    }
}

SchedMFQ::~SchedMFQ() {}

void SchedMFQ::load(int pid) { colas[0].push(pid); }

void SchedMFQ::unblock(int pid) {
    int colaPid = cualCola(pid, laUltimaColaVisitada);

    colas[max(0, colaPid - 1)].push(pid);

    laUltimaColaVisitada[colaPid].erase(pid);
}

int SchedMFQ::tick(int core, const enum Motivo m) {
    int pid = current_pid(core);
    int colaPid = -1;
    int quantumPid = 1;

    if (pid != IDLE_TASK) {
        colaPid = cualCola(pid, laUltimaColaVisitada);
        quantumPid = quantums[colaPid];
    }

    // Si es un tick, disminuye quantum
    // Si es IDLE_TASK pero no hay mas tareas, seguimos con ella
    if (m == TICK) {
        quantumsRestantes[core]--;
        if (quantumsRestantes[core] > 0) {
            return pid;
        }
        if (colasVacias(colas)) {
            quantumsRestantes[core] = quantumPid;
            if(pid != IDLE_TASK){
                laUltimaColaVisitada[colaPid].erase(pid);
                laUltimaColaVisitada[min(colaPid+1,(int)laUltimaColaVisitada.size()-1)].insert(pid);
            }
            return pid;

        }
    }

    // Si no hay otra tarea a la que saltar sigo
    if (m == BLOCK && colasVacias(colas)) {
        return pid;
    }

    // Si estoy corriendo alguna tarea, la encolo
    // un EXIT o un BLOCK no tiene que agregarla
    if (m == TICK && pid != IDLE_TASK) {
        laUltimaColaVisitada[colaPid].erase(pid);
        colas[min((int)colas.size() - 1, colaPid + 1)].push(pid);
    }

    // Sched no tiene a nadie para asignarle al core actual
    if (colasVacias(colas)) {
        return IDLE_TASK;
    }

    // Saco un elemento de la cola y reinicio quantums
    int colaDelPid = primerColaNoVacia(colas);
    int nuevoPid = colas[colaDelPid].front();
    colas[colaDelPid].pop();
    laUltimaColaVisitada[colaDelPid].insert(nuevoPid);
    quantumsRestantes[core] = quantums[colaDelPid];

    return nuevoPid;
}

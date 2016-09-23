#include "tasks.h"
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

void TaskCPU(int pid, vector<int> params) {  // params: n
    uso_CPU(pid, params[0] - 1);             // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) {  // params: ms_pid, ms_io,
    uso_CPU(pid, params[0]);                // Uso el CPU ms_pid milisegundos.
    uso_IO(pid, params[1]);                 // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid,
                 vector<int> params) {  // params: ms_pid, ms_io, ms_pid, ...
    for (int i = 0; i < (int)params.size(); i++) {
        if (i % 2 == 0)
            uso_CPU(pid, params[i] - 1);
        else
            uso_IO(pid, params[i]);
    }
}

void TaskConsola(int pid, vector<int> params) {  // params: n, bmin, bmax
    int n = params[0], bmin = params[1], bmax = params[2];
    for (int i = 0; i < n; i++) {
        int t = bmin + rand() % (bmax - bmin);
        uso_IO(pid, t);
        uso_CPU(pid, 1);
    }
}

void TaskBatch(int pid, vector<int> params) {  // params: total_cpu, cant_bloqueos
    int time = params[0], bloqueos = params[1];

    // El proceso siempre consume un tiempo al terminar
    if(bloqueos >= time) return;

    set<int> tiempos;

    for(int i=0; i<bloqueos; i++) {
        int t;
        do {
            t = rand() % (time-1);
        } while(tiempos.find(t) != tiempos.end());
        tiempos.insert(t);
    }

    int timeCounter = 0;
    for(auto it=tiempos.begin(); it != tiempos.end(); it++) {
        if(timeCounter < *it) {
            uso_CPU(pid, *it - timeCounter);
            timeCounter = *it;
        }
        uso_IO(pid, 2);
        timeCounter++;
    }

    if(timeCounter < time-1) {
        uso_CPU(pid, time-1-timeCounter);
    }
}

void tasks_init(void) {
    /* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
     * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
     * como un vector de enteros, o -1 para una cantidad de parámetros variable.
     */
    register_task(TaskCPU, 1);
    register_task(TaskIO, 2);
    register_task(TaskAlterno, -1);
    register_task(TaskConsola, 3);
    register_task(TaskBatch, 2);
}

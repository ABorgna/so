#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
}

SchedRR::~SchedRR() {
/* completar */
}


void SchedRR::load(int pid) {
/* completar */
}

void SchedRR::unblock(int pid) {
/* completar */
}

int SchedRR::tick(int cpu, const enum Motivo m) {
/* completar */
	return 0;
}

#ifndef __SIMU_H__
#define __SIMU_H__

#include <string>
#include <vector>
#include "basesched.h"
#include "basetask.h"

class Settings {
   public:
    std::string tasks_file;
    unsigned int switch_cost;
    unsigned int migrate_cost;
    std::string sched_class;
    std::vector<int> sched_args;
    bool verbose;
    std::string output_log;
    unsigned int num_cores;
};

void simulate(SchedBase& sch, std::vector<ptsk>& lote,
              const Settings& settings);

#endif

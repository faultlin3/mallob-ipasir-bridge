
#ifndef DOMPASCH_MALLOB_IPASIR_HPP
#define DOMPASCH_MALLOB_IPASIR_HPP

#include <string>
#include <vector>
#include <set>
#include <unistd.h>

#ifndef MALLOB_BASE_DIRECTORY
#define MALLOB_BASE_DIRECTORY "."
#endif

#ifndef MALLOB_API_INDEX
#define MALLOB_API_INDEX "0"
#endif

class MallobIpasir {

private:
    std::string _api_directory;
    pid_t _pid;

    std::vector<int> _formula;
    std::vector<int> _assumptions;
    int _num_vars;
    int _num_cls;
    int _revision;

    int (*_terminate_callback) (void*) = nullptr;
    void* _terminate_data;

    std::vector<int> _model;
    std::set<int> _failed_assumptions;

    std::string formulaFilename;

public:
    MallobIpasir() :
        _api_directory(MALLOB_BASE_DIRECTORY + std::string("/.api/jobs.") + MALLOB_API_INDEX + std::string("/")),
        _num_vars(0),
        _num_cls(0),
        _revision(0) {}
    
    void addLiteral(int lit) {
        _formula.push_back(lit);
        if (lit == 0) {
            _num_cls++;
        } else {
            _num_vars = std::max(_num_vars, std::abs(lit));
        }
    }
    void addAssumption(int lit) {
        _assumptions.push_back(lit);
        _num_vars = std::max(_num_vars, std::abs(lit));
    }

    int solve();

    void destruct();

    int getValue(int lit) {
        return (lit < 0 ? -1 : 1) * _model[std::abs(lit)];
    }
    bool isAssumptionFailed(int lit) {
        return _failed_assumptions.count(lit);
    }
    void setTerminateCallback(void * data, int (*terminate)(void * data)) {
        _terminate_callback = terminate;
        _terminate_data = data;
    }
    std::string getJobName(int revision) {
        return "job-" + std::to_string(getpid()) + "-" + std::to_string(revision);
    }
};

#endif

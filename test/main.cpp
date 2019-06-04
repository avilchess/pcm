#include <cstdlib>
#include <iostream>
#include <cpucounters.h>

int main() {
    std::cout << "Lets read some counters ...!" << std::endl;

    PCM * m = PCM::getInstance();
    m->resetPMU();
    PCM::ErrorCode status = m->program();

    switch (status)
    {
        case PCM::Success:
            break;
        case PCM::MSRAccessDenied:
            std::cerr << "Access to Processor Counter Monitor has denied (no MSR or PCI CFG space access)." << std::endl;
            exit(EXIT_FAILURE);
        case PCM::PMUBusy:
            std::cerr << "Access to Processor Counter Monitor has denied (Performance Monitoring Unit is occupied by other application). Try to stop the application that uses PMU." << std::endl;
            std::cerr << "Alternatively you can try running PCM with option -r to reset PMU configuration at your own risk." << std::endl;
            exit(EXIT_FAILURE);
        default:
            std::cerr << "Access to Processor Counter Monitor has denied (Unknown error)." << std::endl;
            exit(EXIT_FAILURE);
    }

    std::vector<CoreCounterState> cstates1, cstates2;
    std::vector<SocketCounterState> sktstate1, sktstate2;
    SystemCounterState sstate1, sstate2;

    m->getAllCounterStates(sstate1, sktstate1, cstates1);

    float total = 0.0;
    // Do some computation
    for(int i=0; i<1000; i++){
        std::cout << "." ;
        for(int j=0; j<100000; j++){
            total = total + j*i;
        }
    }
    std::cout << std::endl;
    std::cout << total << std::endl;

    m->getAllCounterStates(sstate2, sktstate2, cstates2);

    std::cerr
         << getPP0ConsumedJoules(sktstate1[0], sktstate2[0]) << "\t" << getPP1ConsumedJoules(sktstate1[0], sktstate2[0]) << "\t"
         << getConsumedJoules(sktstate1[0], sktstate2[0]) - getPP0ConsumedJoules(sktstate1[0], sktstate2[0]) - getPP1ConsumedJoules(sktstate1[0], sktstate2[0]) << "\t"
         <<  getConsumedJoules(sstate1, sstate2) << "\t" << getDRAMConsumedEnergy(sktstate1[0], sktstate2[0]) << "\t"
         << getL2CacheHits(sktstate1[0], sktstate2[0]) << "\t" << getL2CacheMisses(sktstate1[0], sktstate2[0]) << "\t" << getL2CacheHitRatio(sktstate1[0], sktstate2[0]) <<"\t"
         << getL3CacheHits(sktstate1[0], sktstate2[0]) << "\t" << getL3CacheMisses(sktstate1[0], sktstate2[0]) << "\t" << getL3CacheHitRatio(sktstate1[0], sktstate2[0]) <<"\t"
         << getCyclesLostDueL3CacheMisses(sstate1, sstate2)
         << std::endl;

    return 0;
}
#include <cstdlib>
#include <iostream>
#include <cpucounters.h>

int main() {
    //Energy Counters
    PCM * pcm;
    std::vector<CoreCounterState> cstates1, cstates2;
    std::vector<SocketCounterState> sktstate1, sktstate2;
    SystemCounterState sstate1, sstate2;

    /*This function prints lot of information*/
    pcm = PCM::getInstance();
    pcm->resetPMU();
    if (pcm->program() != PCM::Success){
        std::cerr << "Error in PCM library initialization" << std::endl;
        exit(-1);
    }

    pcm->getAllCounterStates(sstate1, sktstate1, cstates1);
    float total = 0.0;
    // Do some computation
    for(int i=0; i<10000; i++){
        std::cout << "iter: " << i << std::endl;
        for(int j=0; j<10000; j++){
            total = total + j*i;
        }
    }
    std::cout << total << std::endl;

    pcm->getAllCounterStates(sstate2, sktstate2, cstates2);

    std::cerr
         << getPP0ConsumedJoules(sstate1, sstate2) << "\t" << getPP1ConsumedJoules(sstate1, sstate2) << "\t"
         << getConsumedJoules(sstate1, sstate2) - getPP0ConsumedJoules(sstate1, sstate2) - getPP1ConsumedJoules(sstate1, sstate2) << "\t" <<  getConsumedJoules(sstate1, sstate2) << "\t"
         << getL2CacheHits(sktstate1[0], sktstate2[0]) << "\t" << getL2CacheMisses(sktstate1[0], sktstate2[0]) << "\t" << getL2CacheHitRatio(sktstate1[0], sktstate2[0]) <<"\t"
         << getL3CacheHits(sktstate1[0], sktstate2[0]) << "\t" << getL3CacheMisses(sktstate1[0], sktstate2[0]) << "\t" << getL3CacheHitRatio(sktstate1[0], sktstate2[0]) <<"\t"
         << getCyclesLostDueL3CacheMisses(sstate1, sstate2) << std::endl;

    std::cout << "Hello, World!" << std::endl;

    return 0;
}
#include "parallelcircuit.h"
#include "seriescircuit.h"

RandomParallelCircuit::RandomParallelCircuit(int stages, int level){
    bool final = false;
    int sorted_stages = (rand() % (stages-1)) + 2;
    for (int i = 0; i < sorted_stages; i++){
        if(level == 0){
            this->addComponent(new RandomResistor);
        } else {
            if(rand() % 2 && !final){
                this->addComponent(new RandomSeriesCircuit(stages, --level));
                final = true;
            } else {
                this->addComponent(new RandomResistor);
            }
        }
        
    }
}
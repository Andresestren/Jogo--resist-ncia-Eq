#include "seriescircuit.h"
#include "parallelcircuit.h"

RandomSeriesCircuit::RandomSeriesCircuit(int stages, int level){   //CHEGA A SOLOCITAÇÃO E ELE GERA CONFORMA SOLICIDADO
    bool final = false;
    int sorted_stages = (rand() % (stages-1)) + 2;
    for (int i = 0; i < sorted_stages; i++){
        if(level == 0){
            this->addComponent(new RandomResistor);
        } else {
            if(rand() % 2 && !final){
                this->addComponent(new RandomParallelCircuit(stages, --level));  //CHAMA RANDOMPARALELCIRCUIT
                final = true;
            } else {
                this->addComponent(new RandomResistor);
            }
        }
        
    }
}
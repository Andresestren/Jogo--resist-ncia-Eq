#ifndef ABSTRACTCIRCUIT_H
#define ABSTRACTCIRCUIT_H

#pragma once

#include <iostream>
#include <sstream>

#include <vector> // P/ RECEBER O VALOR DOS RESIS INICIAIS

using namespace std;

class AbstractCircuit {
public:
    virtual double getResistance() const = 0;
    virtual void dumpCircuit(bool showResistance, int level = 0) const = 0; // DUMPCIRCUIT NÃO É USADA, POIS ELA DA COUT
    virtual vector<AbstractCircuit*> getBaseResistors() = 0;
protected:
    string getSpacer(int level) const {    //USADO PRA DAR O DUMP DO CIRCUITO NO COUT TAMBÉM NÃO USADO
        stringstream tabs;
        while (level-- > 0)
            tabs << "   ";
        return tabs.str();
    }
};

#endif
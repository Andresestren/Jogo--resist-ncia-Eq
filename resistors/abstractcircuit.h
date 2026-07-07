#ifndef ABSTRACTCIRCUIT_H
#define ABSTRACTCIRCUIT_H

#pragma once

#include <iostream>
#include <sstream>

using namespace std;

class AbstractCircuit {
public:
	virtual double getResistance() const = 0;
    virtual void dumpCircuit(bool showResistance, int level = 0) const = 0;

protected:
    string getSpacer(int level) const {
        stringstream tabs;
        while (level-- > 0)
            tabs << "   ";
        return tabs.str();
    }
};

#endif
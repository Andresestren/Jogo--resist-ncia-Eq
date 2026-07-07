#ifndef PARALLELCIRCUIT_H
#define PARALLELCIRCUIT_H

#pragma once

#include "abstractcircuit.h"
#include "resistor.h"
#include <vector>
#include <sstream>

using namespace std;

class ParallelCircuit: public AbstractCircuit {
public:
	//SeriesCircuit(vector<AbstractCircuit*> &comps) : _components(comps) {}
    std::vector<AbstractCircuit*> getComponents() const { return _components; }

	void addComponent(AbstractCircuit* c0){
		_components.push_back(c0);
	}

	double getResistance() const override {
		double rEquiv = 0.0;
		for(auto component : _components){
			if(component->getResistance() > 0.0)
				rEquiv += 1.0 / component->getResistance();
		}
		if (rEquiv > 0.0){
			rEquiv = 1.0 / rEquiv;
		}
		return rEquiv;
	}

    void dumpCircuit(bool showResistance, int level = 0) const override {
		int next_level = level + 1;
		string spacer = getSpacer(level);
        cout << spacer << "Parallel(" << _components.size() << ") {" << endl;
        for(auto component: _components){
			component->dumpCircuit(showResistance, next_level);
        }
        cout << spacer << "}" << endl;
    }

private:
	vector<AbstractCircuit *> _components;
};

class RandomParallelCircuit: public ParallelCircuit {
public:
    RandomParallelCircuit(int stages, int level);
};

#endif
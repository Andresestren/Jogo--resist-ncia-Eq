#ifndef SERIESCIRCUIT_H
#define SERIESCIRCUIT_H
#pragma once

#include "abstractcircuit.h"
#include "resistor.h"
#include <vector>
#include <sstream>

using namespace std;

class SeriesCircuit: public AbstractCircuit {
public:

	//SeriesCircuit(vector<AbstractCircuit*> &comps) : _components(comps) {}

	void addComponent(AbstractCircuit* c0){
		_components.push_back(c0);
	}

	double getResistance() const override {
		double rEquiv = 0.0;
		for(auto component : _components){
			rEquiv += component->getResistance();
		}
		return rEquiv;
	}

	void dumpCircuit(bool showResistance, int level = 0) const override {
		int next_level = level + 1;
		string spacer = getSpacer(level);
        cout << spacer << "Series(" << _components.size() << ") {" << endl;
        for(auto component: _components){
			component->dumpCircuit(showResistance, next_level);
        }
        cout << spacer << "}" << endl;
    }


    // Ensina a Série a devolver suas peças----------------------------------------------------
    vector<AbstractCircuit*> getBaseResistors() override {
        vector<AbstractCircuit*> listaCompleta;

        // Passa por cada componente guardado dentro desta série
        for(auto component : _components){
            // Pede as peças para o componente filho
            vector<AbstractCircuit*> subLista = component->getBaseResistors();

            // Adiciona as peças recebidas na nossa lista principal
            listaCompleta.insert(listaCompleta.end(), subLista.begin(), subLista.end());
        }
        return listaCompleta;
    }





private:
	vector<AbstractCircuit *> _components;
};

class RandomSeriesCircuit: public SeriesCircuit {
public:
	RandomSeriesCircuit(int stages, int level);
};

#endif
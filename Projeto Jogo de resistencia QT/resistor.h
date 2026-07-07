#ifndef RESISTOR_H
#define RESISTOR_H
#pragma once

#include <iostream>
#include <sstream>
#include "abstractcircuit.h"

using namespace std;

class Resistor: public AbstractCircuit {
public:
	Resistor(double value){
		_resistance = value;
	}

	double getResistance() const override {
		return _resistance;
	}

    void dumpCircuit(bool showResistance, int level = 0) const override {
		cout << getSpacer(level);	
        if(showResistance)
            cout << "R(" << _resistance << ")" << endl;
        else
            cout << "R(***)" << endl;
    }
private:
	double _resistance;
};

class RandomResistor: public Resistor {
public:
	RandomResistor(): Resistor(VALUES[rand()%VCOUNT]) {
		cout << getResistance() << " ohms resistor created !" << endl;
	}

private:
	static const double VALUES[];
	static const int VCOUNT;
};

#endif
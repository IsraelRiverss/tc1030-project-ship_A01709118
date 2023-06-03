// =========================================================
// File: heavy.h
// Author: Fernando Israel Rios Garcia
// Date: 06/02/2023
// Description:
// =========================================================
#ifndef HEAVY_H
#define HEAVY_H

#include "container.h"

class HeavyContainer : public Container {
public:
    HeavyContainer(int id, int weight);
    HeavyContainer(const HeavyContainer& other);

    double getConsumption() const;
};

HeavyContainer::HeavyContainer(int id, int weight) : Container(id, weight, HEAVY) {
    // Invoca al constructor de la clase superior (Container) con el tipo de contenedor correcto (HEAVY).
}

HeavyContainer::HeavyContainer(const HeavyContainer& other) : Container(other) {
    // Invoca al constructor de la clase superior (Container) para realizar una copia del contenedor existente.
}

double HeavyContainer::getConsumption() const {
    // El consumo de combustible por llevar este tipo de contenedor es 3 veces el peso del mismo.
    return 3.0 * getWeight();
}
#endif
// =========================================================
// File: light.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef LIGHT_H
#define LIGHT_H

#include "container.h"

class LightContainer : public Container {
public:
    LightContainer(int id, int weight);
    LightContainer(const LightContainer& other);

    double getConsumption() const;
};

LightContainer::LightContainer(int id, int weight) : Container(id, weight, LIGHT) {
    // Se invoca al constructor de la clase base (Container) para inicializar el id, peso y tipo del contenedor.
}

LightContainer::LightContainer(const LightContainer& other) : Container(other) {
    // Se invoca al constructor de copia de la clase base (Container) para realizar una copia profunda de los miembros de datos.
}

double LightContainer::getConsumption() const {
    return 2.5 * getWeight(); // El consumo de combustible es 2.5 veces el peso del contenedor.
}
#endif
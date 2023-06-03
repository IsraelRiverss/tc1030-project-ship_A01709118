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

    double getConsumption() const override;
};

LightContainer::LightContainer(int id, int weight) : Container(id, weight >= 0 ? weight : 0, LIGHT) {
    // Invoca al constructor de la clase superior (Container) con el tipo de contenedor correcto (LIGHT).
    // Si el peso es negativo, se establece en 0 en su lugar.
}

LightContainer::LightContainer(const LightContainer& other) : Container(other) {
    // Se invoca al constructor de copia de la clase base (Container) para realizar una copia profunda de los miembros de datos.
}

double LightContainer::getConsumption() const {
    return 2.5 * getWeight(); // El consumo de combustible es 2.5 veces el peso del contenedor.
}
#endif
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
    HeavyContainer(int id, int weight, ContainerType type);
    HeavyContainer(const HeavyContainer& other);

    double getConsumption() const;
};

HeavyContainer::HeavyContainer(int id, int weight) : Container(id, weight, HEAVY) {
    // Invokes the constructor of the base class (Container) with the correct container type (HEAVY).
}

HeavyContainer::HeavyContainer(int id, int weight, ContainerType type) : Container(id, weight, type) {
    // Invokes the constructor of the base class (Container) with the specified container type.
}

HeavyContainer::HeavyContainer(const HeavyContainer& other) : Container(other) {
    // Invokes the copy constructor of the base class (Container) to copy the existing container.
}

double HeavyContainer::getConsumption() const {
    // The fuel consumption for carrying this type of container is 3 times its weight.
    return 3.0 * getWeight();
}
#endif
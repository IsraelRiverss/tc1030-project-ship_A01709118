// =========================================================
// File: liquid.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef LIQUID_H
#define LIQUID_H

#include "heavy.h"

class LiquidContainer : public HeavyContainer {
public:
    LiquidContainer(int id, int weight);
    LiquidContainer(const LiquidContainer& other);

    double getConsumption() const;
};

LiquidContainer::LiquidContainer(int id, int weight) : HeavyContainer(id, weight, LIQUID) {
    // Invokes the constructor of the base class (HeavyContainer) with the correct container type (LIQUID).
}

LiquidContainer::LiquidContainer(const LiquidContainer& other) : HeavyContainer(other) {
    // Invokes the constructor of the base class (HeavyContainer) to copy the existing container.
}

double LiquidContainer::getConsumption() const {
    // The fuel consumption for carrying this type of container is 4 times its weight.
    return 4.0 * getWeight();
}

#endif

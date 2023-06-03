// =========================================================
// File: refrigerated.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef REFRIGERATED_H
#define REFRIGERATED_H

#include "heavy.h"

class RefrigeratedContainer : public HeavyContainer {
public:
  RefrigeratedContainer(int id, int weight);
  RefrigeratedContainer(const RefrigeratedContainer& other);

  double getConsumption() const;
};

RefrigeratedContainer::RefrigeratedContainer(int id, int weight) : HeavyContainer(id, weight, REFRIGERATED) {}

RefrigeratedContainer::RefrigeratedContainer(const RefrigeratedContainer& other) : HeavyContainer(other) {}

double RefrigeratedContainer::getConsumption() const {
    return 5 * getWeight();
}
#endif

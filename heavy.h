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
  HeavyContainer(int, int);
  HeavyContainer(int, int, ContainerType);
  HeavyContainer(const HeavyContainer&);

  double getConsumption() const;
};

#endif

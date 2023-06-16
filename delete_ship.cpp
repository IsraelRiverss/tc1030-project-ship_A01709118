#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include "container.h"
#include "light.h"
#include "heavy.h"
#include "refrigerated.h"
#include "liquid.h"
#include "simpleship.h"
#include "port.h"

using namespace std;

class Ship : public SimpleShip
{
private:
  int currentWeight, totalWeight;
  int currentNumberOfAllContainers, maxNumberOfAllContainers;                   // ALL
  int currentNumberOfHeavyContainers, maxNumberOfHeavyContainers;               // Heavys
  int currentNumberOfRefrigeratedContainers, maxNumberOfRefrigeratedContainers; // Refrigerated
  int currentNumberOfLiquidContainers, maxNumberOfLiquidContainers;             // Liquidos
  double fuel, fuelConsumptionPerKM;                                            // GAS
  Port *currentPort;
  std::list<Container *> containers;

public:
  // Current weight, totalweight, fuel
  Ship(int ID, Port *puerto_actual, int peso_total, int containers_maximos, int pesados_maximos,
       int refrigerados_maximos, int liquidos_maximos, double consumoKM) : SimpleShip(ID)
  {
    currentPort = puerto_actual;
    totalWeight = peso_total;
    maxNumberOfAllContainers = containers_maximos;
    maxNumberOfHeavyContainers = pesados_maximos;
    maxNumberOfRefrigeratedContainers = refrigerados_maximos;
    maxNumberOfLiquidContainers = liquidos_maximos;
    fuelConsumptionPerKM = consumoKM;
    currentNumberOfAllContainers = 0;
    fuel = 0;
    currentWeight = 0;
    currentNumberOfHeavyContainers = 0;
    currentNumberOfLiquidContainers = 0;
    currentNumberOfRefrigeratedContainers = 0;
  } // Constructor original

  Ship(const Ship &copia) : SimpleShip(copia.id)
  {
    currentPort = copia.currentPort;
    totalWeight = copia.totalWeight;
    maxNumberOfAllContainers = copia.maxNumberOfAllContainers;
    maxNumberOfHeavyContainers = copia.maxNumberOfHeavyContainers;
    maxNumberOfRefrigeratedContainers = copia.maxNumberOfRefrigeratedContainers;
    maxNumberOfLiquidContainers = copia.maxNumberOfLiquidContainers;
    fuelConsumptionPerKM = copia.fuelConsumptionPerKM;
    currentNumberOfAllContainers = copia.currentNumberOfAllContainers;
    currentNumberOfHeavyContainers = copia.currentNumberOfHeavyContainers;
    currentNumberOfLiquidContainers = copia.currentNumberOfLiquidContainers;
    currentNumberOfRefrigeratedContainers = copia.currentNumberOfRefrigeratedContainers;
    fuel = copia.fuel;
    currentWeight = copia.currentWeight;
  }

  // Getters
  int getId() const
  {
    return id;
  }
  int getCurrentWeight() const
  {
    return currentWeight;
  }

  int getTotalWeight() const
  {
    return totalWeight;
  }
  int getCurrentNumberOfAllContainers() const
  {
    return currentNumberOfAllContainers;
  }

  int getMaxNumberOfAllContainers() const
  {
    return maxNumberOfAllContainers;
  }

  int getCurrentNumberOfHeavyContainers() const
  {
    return currentNumberOfHeavyContainers;
  }

  int getMaxNumberOfHeavyContainers() const
  {
    return maxNumberOfHeavyContainers;
  }

  int getCurrentNumberOfRefrigeratedContainers() const
  {
    return currentNumberOfRefrigeratedContainers;
  }

  int getMaxNumberOfRefrigeratedContainers() const
  {
    return maxNumberOfRefrigeratedContainers;
  }

  int getCurrentNumberOfLiquidContainers() const
  {
    return currentNumberOfLiquidContainers;
  }

  int getMaxNumberOfLiquidContainers() const
  {
    return maxNumberOfLiquidContainers;
  }

  double getFuel() const
  {
    return fuel;
  }

  double getFuelConsumptionPerKM() const
  {
    return fuelConsumptionPerKM;
  }

  Port *getCurrentPort() const
  {
    return currentPort;
  }

  std::list<Container *> getCurrentContainers() const
  {
    return containers;
  }


  void remove(Container *cont)
  {
    containers.remove(cont);
  }

  bool contains(Container *cont)
  {
    if (find(containers.begin(), containers.end(), cont) != containers.end())
    {
      return true;
    }
    else
      return false;
  }

  bool sailTo(Port *port)
  {
    double consumoTotal;
    double consumo_de_containers = 0;
    double distance = port->getDistance(currentPort);
    for (Container *container : containers)
    {
      consumo_de_containers += container->getConsumption();
    }
    consumoTotal = (fuelConsumptionPerKM * distance) + consumo_de_containers;
    std::cout << "consumo total = " << consumoTotal << " fuel = " << fuel << "\n";
    if (fuel <= consumoTotal)
    {
      return false;
    }
    else
    {
      fuel = fuel - consumoTotal;
      std::cout << "consumo total = " << consumoTotal << " fuel = " << fuel << "\n";
      currentPort->outgoingShip(this);
      port->incomingShip(this);
      currentPort = port;
      return true;
    }
  }

  void reFuel(double charge)
  {
    if (charge < 0)
    {
      charge = 0;
    }
    fuel = +charge;
  }

  bool unLoad(Container *comandar)
  {
    bool encontrado = contains(comandar);
    if (encontrado == true)
    {
      remove(comandar);
      currentNumberOfAllContainers = currentNumberOfAllContainers - 1;
      currentPort->add(comandar);
      currentWeight = currentWeight - comandar->getWeight();
      if (comandar->getType() == LIQUID)
      {
        currentNumberOfLiquidContainers = currentNumberOfLiquidContainers - 1;
        return true;
      }
      else if (comandar->getType() == HEAVY)
      {
        currentNumberOfHeavyContainers = currentNumberOfHeavyContainers - 1;
        return true;
      }
      else if (comandar->getType() == REFRIGERATED)
      {
        currentNumberOfRefrigeratedContainers = currentNumberOfRefrigeratedContainers - 1;
        return true;
      }
      else if (comandar->getType() == LIGHT)
      {
        return true;
      }
    }
    return false;
  }

  bool load(Container *container)
  {
    if ((currentPort->contains(container) == false) )
    {
      return false;
    }

    if (currentNumberOfAllContainers + 1 > maxNumberOfAllContainers)
    {
      return false;
    }

    if (currentWeight + container->getWeight() > totalWeight)
    {
      return false;
    }

    ContainerType tipo = container->getType();
    if (tipo == HEAVY && currentNumberOfHeavyContainers <= maxNumberOfHeavyContainers)
    {
      currentPort->remove(container);
      containers.push_back(container);
      currentNumberOfAllContainers += 1;
      currentNumberOfHeavyContainers += 1;
      currentWeight = currentWeight + container->getWeight();
      return true;
    }
    else if (tipo == LIQUID && currentNumberOfLiquidContainers <= maxNumberOfLiquidContainers)
    {
      currentPort->remove(container);
      containers.push_back(container);
      currentNumberOfAllContainers += 1;
      currentNumberOfLiquidContainers += 1;
      currentWeight = currentWeight + container->getWeight();
      return true;
    }
    else if (tipo == REFRIGERATED && currentNumberOfRefrigeratedContainers <= maxNumberOfRefrigeratedContainers)
    {
      currentPort->remove(container);
      containers.push_back(container);
      currentNumberOfAllContainers += 1;
      currentNumberOfRefrigeratedContainers += 1;
      currentWeight = currentWeight + container->getWeight();
      return true;
    }
    else if (tipo == LIGHT)
    {
      currentPort->remove(container);
      containers.push_back(container);
      currentNumberOfAllContainers += 1;
      currentWeight = currentWeight + container->getWeight();
      return true;
    }
    else
      return false;
  }

  std::string toString() const
  {
    std::stringstream e[6];
    std::stringstream exe;

    e[0] << "\n Ship " << id << ":  " << totalWeight;
    e[1] << "\n     Light Containers: ";
    e[2] << "\n     Heavy Containers: ";
    e[3] << "\n     Refrigerated Containers: ";
    e[4] << "\n     Liquid Containers: ";

    for (Container *container : containers)
    {
      if (container->getType() == LIGHT)
        e[1] << container->getId();

      else if (container->getType() == HEAVY)
        e[2] << container->getId();

      else if (container->getType() == REFRIGERATED)
        e[3] << container->getId();

      else if (container->getType() == LIQUID)
        e[4] << container->getId();
    }

    e[1] << "\n ";
    e[2] << "\n ";
    e[3] << "\n ";
    e[4] << "\n ";

    exe << e[0].str() << e[1].str() << e[2].str() << e[3].str() << e[4].str();

    return exe.str();
  }
  };
#endif
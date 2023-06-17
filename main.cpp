#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "container.h"
#include "light.h"
#include "heavy.h"
#include "refrigerated.h"
#include "liquid.h"
#include "simpleship.h"
#include "ship.h"
#include "port.h"

using namespace std;

int main(int argc, char* argv[]) {
  ifstream inputFile;
  ofstream outputFile;

  vector<Container*> containers;
  vector<Ship*> ships;
  vector<Port*> ports;

  int idContainer, idShip, idPort;
  idContainer = idShip = idPort = 0;
  
  if (argc != 3) {
    cout << "usage: " << argv[0] << " input_file output_file\n";
    return -1;
  }

  inputFile.open(argv[1]);
  if (!inputFile.is_open()) {
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  outputFile.open(argv[2]);

  int containerSize, shipSize, portSize, events;
  inputFile >> containerSize >> shipSize >> portSize >> events;
  
  int actualShip;
  int actualContainer;
  int actualPort;
  double actualFuel;

  containers.resize(containerSize);
  ships.resize(shipSize);
  ports.resize(portSize);
    
  int var1;

  for (int i = 0; i < events; i++)
  {
    
    inputFile >> var1;
    

    switch (var1)
    {
    case 1:
      int actualPort;
      int actualWheight;
      char actualTYPE_Container;
      inputFile >> actualPort >> actualWheight >> actualTYPE_Container;
        
      switch (actualTYPE_Container)
      {
      case 'L':
        containers[idContainer] = new LiquidContainer(idContainer, actualWheight);
        break;

      case 'B':
        if(actualWheight <= 3000){
          containers[idContainer] = new LightContainer(idContainer, actualWheight);
        }
        else{
          containers[idContainer] = new HeavyContainer(idContainer, actualWheight);
        }
        break;
      
      case 'R':
        containers[idContainer] = new RefrigeratedContainer(idContainer, actualWheight);
        break;

      default:
        break;
      }

      ports[actualPort]->add(containers[idContainer]);
      idContainer++;
      break;

    case 2:

      int startPort;
      int maxWeight;
      int maxContainers;
      int maxHeavy;
      int maxRefrigerated;
      int maxLiquid;
      double fuelPerKM;

      inputFile >> startPort >> maxWeight >> maxContainers >> maxHeavy >> maxRefrigerated >> maxLiquid >> fuelPerKM;

      ships[idShip] = new Ship(idShip, ports[startPort], maxWeight, maxContainers, maxHeavy, maxRefrigerated, maxLiquid, fuelPerKM);
      ports[startPort]->incomingShip(ships[idShip]);
      idShip++;
      break;

    case 3:
      double port_x;
      double port_y;
      inputFile >> port_x >> port_y;


      ports[idPort] = new Port(idPort, port_x, port_y);

      idPort++;

      break;

    case 4:

      
      inputFile >> actualShip >> actualContainer;

      ships[actualShip]->load(containers[actualContainer]);
      break;

    case 5:

      
      inputFile >> actualShip >> actualContainer;

      ships[actualShip]->unLoad(containers[actualContainer]);
      break;

    case 6:
      inputFile >> actualShip >> actualPort;

      ships[actualShip]->sailTo(ports[actualPort]);

      break;
    case 7:     
      inputFile >> actualShip >> actualFuel;

      ships[actualShip]->reFuel(actualFuel);
      break;

    default:
      break;
    }
    
  }
    for (int i = 0; i < ports.size(); i++)
  {
    outputFile << ports[i]->toString();

    outputFile << endl;

  }

  inputFile.close();
  outputFile.close();
  return 0;
  
}
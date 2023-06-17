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

  // TO DO
  

  //Read the file
  int containerSize, shipSize, portSize, events;
  inputFile >> containerSize >> shipSize >> portSize >> events;
  

  
  int shipazo;
  int contenedorazo;
  int puertoazo;
  double fuelazo;

  //Cambiamos tamaño de los vectores
  containers.resize(containerSize);
  ships.resize(shipSize);
  ports.resize(portSize);
  
  //checar el tipo de evento
  
  int evencito;

  

  for (int i = 0; i < events; i++)
  {
    
    inputFile >> evencito;
    

    switch (evencito)
    {
    case 1:
      //Crear un contenedor 
      int puertecito;
      int pesito;
      char tipecito;
      inputFile >> puertecito >> pesito >> tipecito;
        
      switch (tipecito)
      {
      case 'L':
        //Crear un contenedor liquido
        containers[idContainer] = new LiquidContainer(idContainer, pesito);
        break;

      case 'B':
        //Crear un contenedor heavy o light
        if(pesito <= 3000){
          containers[idContainer] = new LightContainer(idContainer, pesito);
        }
        else{
          containers[idContainer] = new HeavyContainer(idContainer, pesito);
        }
        break;
      
      case 'R':
        //Crear un contenedor refrigerado
        containers[idContainer] = new RefrigeratedContainer(idContainer, pesito);
        break;

      default:
        break;
      }

      //Agregar el contenedor al puerto
      ports[puertecito]->add(containers[idContainer]);
      idContainer++;
      break;

    case 2:
      //Add ship

      int puertoInicial;
      int maxWeight;
      int maxContainers;
      int maxHeavy;
      int maxRefrigerated;
      int maxLiquid;
      double fuelPerKM;

      inputFile >> puertoInicial >> maxWeight >> maxContainers >> maxHeavy >> maxRefrigerated >> maxLiquid >> fuelPerKM;

      ships[idShip] = new Ship(idShip, ports[puertoInicial], maxWeight, maxContainers, maxHeavy, maxRefrigerated, maxLiquid, fuelPerKM);
      ports[puertoInicial]->incomingShip(ships[idShip]);
      idShip++;
      break;

    case 3:
      //Add port
      double puertoX;
      double puertoY;
      inputFile >> puertoX >> puertoY;


      ports[idPort] = new Port(idPort, puertoX, puertoY);

      idPort++;

      break;

    case 4:

      
      inputFile >> shipazo >> contenedorazo;

      ships[shipazo]->load(containers[contenedorazo]);
      break;

    case 5:

      
      inputFile >> shipazo >> contenedorazo;

      ships[shipazo]->unLoad(containers[contenedorazo]);
      break;

    case 6:
      //Move ship to another port

      inputFile >> shipazo >> puertoazo;

      ships[shipazo]->sailTo(ports[puertoazo]);

      break;
    case 7:
      //Cargar combustible
      
      inputFile >> shipazo >> fuelazo;

      ships[shipazo]->reFuel(fuelazo);
      break;

    default:
      break;
    }
    
  }
  
  //Print the output
  for (int i = 0; i < ports.size(); i++)
  {
    outputFile << ports[i]->toString();

    outputFile << endl;

  }

  inputFile.close();
  outputFile.close();
  return 0;
  
}
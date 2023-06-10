// =========================================================
// File: container.h
// Author: Fernando Israel Rios Garcia
// Date: 30/05/2023
// Description:
/*
 * La clase `Container` es una clase que representa un contenedor en un sistema de gestión portuaria. Esta clase tiene la responsabilidad de almacenar información relevante sobre el contenedor, como su identificador, peso y tipo.

La clase `Container` cuenta con los siguientes miembros de datos:

- `id`: Un entero que representa el identificador del contenedor.
- `weight`: Un entero que indica el peso del contenedor.
- `type`: Una enumeración `ContainerType` que define el tipo del contenedor, que puede ser "ligero", "pesado", "refrigerado" o "líquido".

Además de los miembros de datos, la clase `Container` también proporciona los siguientes métodos:

- Constructor: Un constructor que recibe tres parámetros: el identificador, el peso y el tipo del contenedor. Este constructor se encarga de inicializar los miembros de datos correspondientes con los valores proporcionados.
- Constructor de copia: Un constructor que crea una nueva instancia de `Container` a partir de otra instancia existente. Este constructor realiza una copia profunda de los miembros de datos de la instancia original.
- Métodos de acceso: Métodos para obtener los valores de los miembros de datos individuales, como `getId()`, `getWeight()` y `getType()`. Estos métodos permiten acceder de forma segura a los datos almacenados en el contenedor.
- Sobrecarga de operadores: La clase `Container` sobrecarga los operadores de igualdad (`==`) y menor que (`<`). Estas sobrecargas permiten comparar dos contenedores en función de su identificador, peso y tipo.
- Método virtual puro: La clase `Container` define un método virtual puro `getConsumption()`, que debe ser implementado en las clases derivadas. Este método calcula el consumo específico del contenedor y debe ser implementado según las necesidades específicas de cada tipo de contenedor.

En resumen, la clase `Container` proporciona una representación básica de un contenedor en un sistema de gestión portuaria, con métodos para acceder y comparar sus atributos. Esta clase sirve como base para la implementación de clases derivadas que representan tipos específicos de contenedores, como contenedores refrigerados o contenedores líquidos.
 */
// =========================================================
#ifndef CONTAINER_H
#define CONTAINER_H

typedef enum{LIGHT, HEAVY, REFRIGERATED, LIQUID} ContainerType;
/*
 * Container class that contains 3 parameters, contains the methods to
 * get id, weight and overrides operators
 *
 * @parameters int id
 * @parameters int weight
 */
class Container {
protected:
  int id, weight;
  ContainerType type;

public:
  Container(int, int, ContainerType);
  Container(const Container&);

  ContainerType getType() const;
  int getId() const;
  int getWeight() const;

  bool operator==(const Container*);
  bool operator==(const Container&);
  bool operator<(const Container*);
  bool operator<(const Container&);

  virtual double getConsumption() const = 0;
};
Container::Container(int id, int weight, ContainerType type) {
    this->id = id;
    if (weight <= 0) {
        this -> weight = 0;
    }
    if (weight >= 0) {
        this -> weight = weight;
    }
    this->type = type;
}

Container::Container(const Container& other) {
    this->id = other.id;
    this->weight = other.weight;
    this->type = other.type;
}

int Container::getId() const {
    return id;//Retornamos id
}

int Container::getWeight() const {
    return weight;//Retornamos weight
}

ContainerType Container::getType() const {
    return type;
}
bool Container::operator==(const Container *right) {
    return (id==right->id && weight==right->weight && type==right->type);
}
bool Container::operator==(const Container &right) {
    return (id==right.id && weight==right.weight && type==right.type);
}
bool Container::operator<(const Container &right) {
    if (type == right.type) {
        return id < right.id;
    } else {
        return type < right.type;
    }
}
bool Container::operator<(const Container *right) {
    if (type == right->type) {
        return id < right->id;
    } else {
        return type < right->type;
    }
}
#endif

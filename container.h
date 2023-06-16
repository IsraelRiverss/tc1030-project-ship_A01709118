// =========================================================
// File: container.h
// Author: Fernando Israel Rios Garcia
// Date: 30/05/2023
// Description:
// =========================================================
#ifndef CONTAINER_H
#define CONTAINER_H

typedef enum{LIGHT, HEAVY, REFRIGERATED, LIQUID} ContainerType;

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

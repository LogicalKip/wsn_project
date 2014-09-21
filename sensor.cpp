#include "sensor.h"
#include "exceptions.h"


int Sensor::nextIdToSet = 0;

Sensor::Sensor(int x, int y, int batteries, bool solarCells)
{
    this->x = x;
    this->y = y;
    this->energy = batteries;
    this->id = nextIdToSet++;
    this->usingSolarEnergy = solarCells;
}

int Sensor::getX() {
    return this->x;
}

int Sensor::getY() {
    return this->y;
}

int Sensor::getId() {
    return this->id;
}

list<Sensor*> Sensor::getNeighbors() {
    return this->neighbors;
}

int Sensor::getEnergy() {
    return this->energy;
}

void Sensor::removeEnergy(int amount) {
    if (this->energy - amount < 0) {
        throw NegativeResultException("Sensor", "removeEnergy");
    }
    int actualAmount = amount;
    if (this->usingSolarEnergy) {
        actualAmount /= 2;
    }
    this->energy -= actualAmount;
}

void Sensor::addNeighbor(Sensor* neighbor) {
    this->neighbors.push_back(neighbor);
}

void Sensor::removeNeighbor(Sensor* neighborToRemove) {
    this->neighbors.remove(neighborToRemove);
}

bool Sensor::equals(Sensor const& otherSensor) const {
    return this->id == otherSensor.id;
}

bool operator==(Sensor const& a, Sensor const& b) {
    return a.equals(b);
}

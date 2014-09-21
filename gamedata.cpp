#include "gamedata.h"

#include "exceptions.h"

#include <sstream>
#include <cstdlib>
#include <algorithm>


GameData::GameData(int startingPoints, int startingDetectionRange, int startingCommunicationRange) :
    sink(GameConstants::SINK_X, GameConstants::SINK_Y)
{
    this->points = startingPoints;
    this->detectionRange = startingDetectionRange;
    this->communicationRange = startingCommunicationRange;
}


int GameData::getPoints() {
    return this->points;
}


int GameData::getDetectionRange() {
    return this->detectionRange;
}

int GameData::getCommunicationRange() {
    return this->communicationRange;
}

int GameData::getNbSensors() {
    return this->allSensors.size();
}

int GameData::getDetecRangeImprovCost() {
    return GameConstants::DETEC_RANGE_IMPROV_COST;
}

int GameData::getIncrSensorNbCost() {
    return GameConstants::SENSOR_COST;
}

int GameData::getSolarCellCost() {
    return GameConstants::SOLAR_CELLS_COST;
}

int GameData::getMapHeight() {
    return GameConstants::MAP_HEIGHT;
}

int GameData::getMapWidth() {
    return GameConstants::MAP_WIDTH;
}

list <Sensor*> GameData::getAllSensors() {
    return this->allSensors;
}

Coordinates GameData::getSink() {
    return this->sink;
}

bool GameData::isDetected(int xa, int ya) {
    for (std::list<Sensor*>::iterator sensor = this->allSensors.begin() ;
        sensor != this->allSensors.end() ; sensor++) {

        // a is the thing to detect and b the current sensor
        int xb = (*sensor)->getX(), yb = (*sensor)->getY();

        double distance = GameConstants::distance(xa, ya, xb, yb);

        if (distance <= detectionRange) {
            return isLinkedToSink(*sensor);//FIXME if close enough to detect but not linked, will return false even if the next sensor would have been close enough AND linked
        }
    }

    return false;
}

bool isInList(Sensor* s, list<Sensor*> l) {
    return std::find(l.begin(), l.end(), s) != l.end();
}

bool GameData::isLinkedToSink(Sensor* s) {
    list<Sensor*> sensorsChecked;

    return META_isLinkedToSink(s, sensorsChecked);
}

bool GameData::META_isLinkedToSink(Sensor* s, list<Sensor*> sensorsChecked) {
    sensorsChecked.push_back(s);

    if (GameConstants::distance(sink.getX(), sink.getY(), s->getX(), s->getY()) <= this->communicationRange) {
        return true;
    }
    else {
        list<Sensor*> neighbors = s->getNeighbors();

        // For each neighbor
        for (std::list<Sensor*>::iterator currNeighbor = neighbors.begin() ; currNeighbor != neighbors.end() ; currNeighbor++) {
            // If neighbor is not checked
            if (! isInList(*currNeighbor, sensorsChecked)) {
                if (META_isLinkedToSink(*currNeighbor, sensorsChecked)) {
                    return true;
                }
            }
        }

        return false;
    }
}



void GameData::addPoints(int x) {
    if (this->points + x < 0) {
        throw NegativeResultException("GameData", "addPoints");
    }
    this->points += x;
}

void GameData::removePoints(int x) {
    if (this->points - x < 0) {
        throw NegativeResultException("GameData", "removePoints");
    }
    this->addPoints(-x);
}

void GameData::enhanceDetectionRange(int x) {
    if (x <= 0) {
        std::stringstream info;
        info << "Enhancing range by " << x << " isn't really enhancing !";
        throw NegativeResultException("GameData", "enhanceDetectionRange", info.str());
    }
    this->detectionRange += x;
}

void GameData::addNewSensor(bool solarTechnology) {
    int newX = rand() % getMapWidth(),
        newY = rand() % getMapHeight();
    Sensor* newSensor = new Sensor(newX, newY, 100, solarTechnology);//FIXME when should do the delete ? Should even do it ? destr from gameData called from game called from mainwindow ?
    for (list<Sensor*>::iterator currSensor = this->allSensors.begin() ; currSensor != this->allSensors.end() ; currSensor++) {
        if (GameConstants::distance((*currSensor)->getX(), (*currSensor)->getY(), newX, newY) <= this->getCommunicationRange()) {
            (*currSensor)->addNeighbor(newSensor);

            newSensor->addNeighbor(*currSensor);
        }
    }
    this->allSensors.push_back(newSensor);
}

list<Sensor*>::iterator GameData::removeSensor(list<Sensor*>::iterator& sensorToRemove) {
    list<Sensor*> neighbors = (*sensorToRemove)->getNeighbors();
    for (list<Sensor*>::iterator currNeighbor = neighbors.begin() ; currNeighbor != neighbors.end() ; currNeighbor++) {
        (*currNeighbor)->removeNeighbor(*sensorToRemove);
    }

    list<Sensor*>::iterator res = this->allSensors.erase(sensorToRemove); //FIXME Calls destructor ?

    delete *sensorToRemove;

    return res;
}

void GameData::decreaseBatteries(int amount) {
    list<Sensor*>::iterator currentSensor = this->allSensors.begin();
    while (currentSensor != this->allSensors.end()) {
        if ((*currentSensor)->getEnergy() - amount <= 0) {
            currentSensor = this->removeSensor(currentSensor);
        }
        else {
            (*currentSensor)->removeEnergy(amount);
            currentSensor++;
        }
    }
}

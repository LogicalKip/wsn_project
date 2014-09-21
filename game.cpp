#include "game.h"
#include "drawfield.h"
#include "gameconstants.h"

#include <cstdlib>


Game::Game() {
    this->gameData = new GameData(GameConstants::STARTING_POINTS, GameConstants::STARTING_DETECTION_RANGE, GameConstants::STARTING_COMMUNICATION_RANGE);
    this->usingSolarCellTechnology = false;
}


void Game::improveDetectionRange() {
    int cost = this->gameData->getDetecRangeImprovCost();
    if (this->gameData->getPoints() >= cost) {
        this->gameData->enhanceDetectionRange(GameConstants::DETECTION_RANGE_IMPROVEMENT);
        this->gameData->removePoints(cost);
    }
}

void Game::buySensor() {
    int cost = this->gameData->getIncrSensorNbCost();
    if (this->gameData->getPoints() >= cost) {
        this->gameData->addNewSensor(this->usingSolarCellTechnology);
        this->gameData->removePoints(cost);
    }
}

void Game::useSolarCells() {
    int cost = this->gameData->getSolarCellCost();
    if (this->gameData->getPoints() >= cost && !this->usingSolarCellTechnology) {
        this->usingSolarCellTechnology = true;
        this->gameData->removePoints(cost);
    }
}

Coordinates* Game::potentialRandomFire() {
    Coordinates* res = NULL;
    if (rand() % 100 <= GameConstants::PROB_FIRE_APPEARS * 100) {
        int x = rand() % (getMapWidth()),
            y = rand() % (getMapHeight());
        if (this->gameData->isDetected(x, y)) {
            this->gameData->addPoints(GameConstants::POINTS_FOR_PREVENTING_FIRE);
        }
        res = new Coordinates(x, y);
    }

    return res;
}

void Game::decreaseBatteries() {
    this->gameData->decreaseBatteries(2);
}

int Game::getPoints() {
    return this->gameData->getPoints();
}

int Game::getDetectionRange() {
    return this->gameData->getDetectionRange();
}

int Game::getCommunicationRange() {
    return this->gameData->getCommunicationRange();
}

int Game::getNbSensors() {
    return this->gameData->getNbSensors();
}

int Game::getDetecRangeImprovCost() {
    return this->gameData->getDetecRangeImprovCost();
}

int Game::getIncrSensorNbCost() {
    return this->gameData->getIncrSensorNbCost();
}

int Game::getSolarCellCost() {
    return this->gameData->getSolarCellCost();
}

int Game::getMapHeight() {
    return this->gameData->getMapHeight();
}

int Game::getMapWidth() {
    return this->gameData->getMapWidth();
}

bool Game::getUsingSolarCellTechnology() {
    return this->usingSolarCellTechnology;
}

list <Sensor*> Game::getAllSensors() {
    return this->gameData->getAllSensors();
}

Coordinates Game::getSink() {
    return this->gameData->getSink();
}

#ifndef GAME_H
#define GAME_H

#include "gamedata.h"
#include "coordinates.h"

class Game
{
public:
    Game();

private:
    GameData* gameData;

    bool usingSolarCellTechnology;

public :
    /**
     * @brief improveDetectionRange Pay the required amount of points, if possible,
     * to globally improve the sensors' detection range
     */
    void improveDetectionRange();

    /**
     * @brief buySensor Pay the required amount of points, if possible,
     * to get another sensor
     */
    void buySensor();

    /**
     * @brief useSolarCells Pay the required amount of points, if possible, to use solar cell technology from now on (on new sensors), reducing battery consumption
     */
    void useSolarCells();

    /**
     * @brief potentialRandomFire May or may not start a fire -which should be detected by the sensors (if the player did well)-
     * in a random location on the map.
     * Earns points if detected by sensors.
     * @return the coordinates of the fire, or NULL if no fire occured
     */
    Coordinates* potentialRandomFire();

    void decreaseBatteries();

    int getPoints();

    int getDetectionRange();

    int getCommunicationRange();

    int getNbSensors();

    int getDetecRangeImprovCost();

    int getIncrSensorNbCost();

    int getSolarCellCost();

    int getMapHeight();

    int getMapWidth();

    bool getUsingSolarCellTechnology();

    Coordinates getSink();

    list <Sensor*> getAllSensors();
};

#endif // GAME_H

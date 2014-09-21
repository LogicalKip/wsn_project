#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <list>

#include "sensor.h"
#include "coordinates.h"
#include "gameconstants.h"

using std::list;

class GameData
{
public:
    GameData(int startingPoints,
             int startingDetectionRange = GameConstants::STARTING_DETECTION_RANGE,
             int startingCommunicationRange = GameConstants::STARTING_COMMUNICATION_RANGE);

private:
    /**
     * @brief detectionRange Radius of the circle representing how far a sensor can sense.
     */
    int detectionRange;

    /**
     * @brief communicationRange Radius of the circle representing how far a sensor can relay messages to other sensors
     */
    int communicationRange;

    /**
     * @brief points Number of points left for the player to spend.
     * The player may earn more later.
     */
    int points;

    /**
     * @brief allSensors List of all the sensors currently in the game
     */
    list<Sensor*> allSensors;

    /**
     * @brief sink Location of the sink, to whom the sensors must be linked to be useful.
     */
    Coordinates sink;

    /**
     * @brief isLinkedToSink allows to know if an information can be sent to the sink
     * @param s The sensor that maybe can communicate with the sink
     * @return true if the sensor is either in communication range of the sink, or with another sensor that isLinkedToSink
     */
    bool isLinkedToSink(Sensor* s);

    /**
     * @brief META_isLinkedToSink Recursive function called first by isLinkedToSink()
     * @param s the current sensor to link
     * @param sensorsChecked list of the sensors that should not be looked upon, to avoid infinite loops
     * @return
     */
    bool META_isLinkedToSink(Sensor* s, list<Sensor*> sensorsChecked);


public:
    int getPoints();

    int getDetectionRange();

    int getCommunicationRange();

    int getNbSensors();

    int getDetecRangeImprovCost();

    int getIncrSensorNbCost();

    int getSolarCellCost();

    int getMapHeight();

    int getMapWidth();

    Coordinates getSink();

    list<Sensor*> getAllSensors();

    /**
     * @brief isDetected allows to know if a given point is in the zone made of all
     * the sensors' detection zones combined.
     * @param x The location of the point on the X axis
     * @param y The location of the point on the Y axis
     * @return true if the given location is in range of at least one sensor
     */
    bool isDetected(int xa, int ya);

    /**
     * @brief addPoints Add x points to the current amount.
     * @param x the amount of points added to the current amount.
     * A negative number will decrease the amount.
     */
    void addPoints(int x); // THROWS NegativeResultException

    /**
     * @brief removePoints Remove x points from the total amount of points
     * @param x the amount of points substracted to the current amount.
     * A negative number will increase the amount.
     */
    void removePoints(int x); // THROWS NegativeResultException

    /**
     * @brief enhanceDetectionRange Improve the sensors' detection range by x (adds)
     * @param x Must not be < 0
     */
    void enhanceDetectionRange(int x); // THROWS NegativeResultException

    void addNewSensor(bool solarTechnology);

    /**
     * @brief decreaseBatteries Remove amount energy from all sensors.
     * TODO and remove those whose energy is now <= 0
     * @param amount
     */
    void decreaseBatteries(int amount);

    /**
     * @brief removeSensor Remove the sensor from the game
     * @param sensorToRemove
     * @return the sensor in the list that is after the one removed
     */
    list<Sensor*>::iterator removeSensor(list<Sensor*>::iterator& sensorToRemove);
};

#endif // GAMEDATA_H

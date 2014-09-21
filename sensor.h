#ifndef SENSOR_H
#define SENSOR_H

#include <list>

using std::list;

/**
 * @brief The Sensor class
 * An actual sensor and its specifications
 */
class Sensor
{
public:
    Sensor(int x, int y, int batteries, bool solarCells);

    int getX();

    int getY();

    int getId();

    list<Sensor*> getNeighbors();

    int getEnergy();

    void removeEnergy(int amount); // THROwS NegativeResultException

    void addNeighbor(Sensor* neighbor);

    void removeNeighbor(Sensor* neighborToRemove);

    bool equals(Sensor const& otherSensor) const;

private:
    /**
     * @brief nextIdToSet Value to set to this.id next time constructor is called
     */
    static int nextIdToSet;

    /**
     * @brief id Unique ID given to each sensor
     */
    int id;

    /**
     * @brief x Sensor's location on the x axis
     */
    int x;

    /**
     * @brief y Sensor's location on the y axis
     */
    int y;

    /**
     * @brief neighbors Sensors close enough to communicate with. The sensor itself isn't one of its neighbors.
     */
    list<Sensor*> neighbors;

    /**
     * @brief battery How much energy is left in the batteries
     */
    int energy;

    /**
     * @brief usingSolarEnergy Power consumption is reduced if using solar cells
     */
    bool usingSolarEnergy;

};


bool operator==(Sensor const& a, Sensor const& b);

#endif // SENSOR_H

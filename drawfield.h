#ifndef DRAWFIELD_H
#define DRAWFIELD_H

#include <QWidget>
#include <list>

#include "game.h"
#include "coordinates.h"

using std::list;

class DrawField : public QWidget
{
    Q_OBJECT

private:
    Game* game;

    /**
     * @brief fires FIFO list of the fires to display. New fires must be pushed_back.
     * The first one is removed when it has been displayed long enough.
     */
    list<Coordinates> fires;


public:
    static const int SENSOR_DIAMETER = 5;

    static const int FIRE_DIAMETER = 10;

    static const int SINK_SIZE = 16;

    static const int ENERGY_HEIGHT = 7;

    static const int MS_DISPLAYING_FIRE = 3500;

    explicit DrawField(Game* game, QWidget *parent = 0);

    void paintEvent(QPaintEvent* event);

    /**
     * @brief displayFire Display the fire on given coordinates for a limited amount of time.
     * @param fire the coordinates of the fire on the map
     */
    void displayFire(Coordinates* fire);

signals:

private slots:
    /**
     * @brief removeFire Remove the first fire from the fifo list, and updates, removing it from the screen.
     * @param fire
     */
    void removeFire();

};

#endif // DRAWFIELD_H

#include "drawfield.h"
#include "gameconstants.h"

#include <list>
#include <QPainter>
#include <Qt>
#include <QTimer>


DrawField::DrawField(Game* game, QWidget *parent) :
    QWidget(parent)
{
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
    setFixedSize(game->getMapWidth(), game->getMapHeight());
    this->game = game;
}

void DrawField::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    list <Sensor*> sensors = this->game->getAllSensors();

    // For each sensor
    for(list<Sensor*>::iterator currSensor = sensors.begin() ; currSensor != sensors.end() ; currSensor++) {
        // Foreach neighbor
        list<Sensor*> neighbors = (*currSensor)->getNeighbors();
        for (list<Sensor*>::iterator currNeighbor = neighbors.begin() ; currNeighbor != neighbors.end() ; currNeighbor++) {
            // Draw communication with neighbor
            painter->drawLine((*currSensor)->getX(), (*currSensor)->getY(), // Will draw twice, but who cares ?
                             (*currNeighbor)->getX(),
                             (*currNeighbor)->getY());
        }

        painter->setBrush(Qt::NoBrush);
        // Draw communication with sink
        if (GameConstants::distance((*currSensor)->getX(), (*currSensor)->getY(), this->game->getSink().getX(), this->game->getSink().getY()) <= game->getCommunicationRange())
            painter->drawLine((*currSensor)->getX(), (*currSensor)->getY(), this->game->getSink().getX(), this->game->getSink().getY());

        // Draw detection range
        int range = this->game->getDetectionRange();
        painter->drawEllipse((*currSensor)->getX() - range,
                             (*currSensor)->getY() - range,
                             range * 2, range * 2);

        // Draw sensor
        painter->setBrush(Qt::blue);
        painter->drawEllipse((*currSensor)->getX() - (DrawField::SENSOR_DIAMETER/2),
                             (*currSensor)->getY() - (DrawField::SENSOR_DIAMETER/2),
                             DrawField::SENSOR_DIAMETER, DrawField::SENSOR_DIAMETER);

        // Draw energy
        painter->setBrush(Qt::green);
        painter->drawRect((*currSensor)->getX() - (*currSensor)->getEnergy()/2,
                          (*currSensor)->getY() + SENSOR_DIAMETER/2,
                          (*currSensor)->getEnergy(), ENERGY_HEIGHT);
    }

    // Draw fires
    painter->setBrush(Qt::red);
    for(list<Coordinates>::iterator currFire = this->fires.begin() ; currFire != this->fires.end() ; currFire++) {
        painter->drawEllipse(currFire->getX(), currFire->getY(), DrawField::FIRE_DIAMETER, DrawField::FIRE_DIAMETER);
    }

    // Draw sink
    painter->setBrush(Qt::yellow);
    int sinkX = this->game->getSink().getX(),
        sinkY = this->game->getSink().getY();
    painter->drawRect(sinkX - (SINK_SIZE/2), sinkY - (SINK_SIZE/2), SINK_SIZE, SINK_SIZE);
}

void DrawField::displayFire(Coordinates* fire) {
    this->fires.push_back(*fire);
    QTimer::singleShot(DrawField::MS_DISPLAYING_FIRE, this, SLOT(removeFire()));

    this->update();
}

/* SLOT function */
void DrawField::removeFire() {
    this->fires.erase(this->fires.begin());// Remove the first one
    //It seems that erase() deletes the object on its own (it was newed in game/potentialRandomFire)

    this->update();
}

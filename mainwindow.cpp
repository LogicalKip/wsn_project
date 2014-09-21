#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawfield.h"
#include "gameconstants.h"
#include "macros.h"
#include "exceptions.h"
#include "coordinates.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QTimer>


MainWindow::MainWindow(Game* game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->game = game;

    this->setUpArchitecture();

    this->setUpInterfaceCommunication();
}

MainWindow::~MainWindow() {
    delete ui;
    delete this->fireTimer;
    delete this->batteriesTimer;

    // What about other attributes ?
}


void MainWindow::setUpArchitecture() {
    this->pointsLabel    = new QLabel(this);
    this->rangeLabel     = new QLabel(this);
    this->nbSensorLabel  = new QLabel(this);
    this->update(this->rangeLabel);
    this->update(this->pointsLabel);
    this->update(this->nbSensorLabel);


    this->improveRangeButton = new QPushButton;
    this->getMoreSensorsButton = new QPushButton;
    this->solarCellsButton = new QPushButton;
    this->update(this->improveRangeButton);
    this->update(this->getMoreSensorsButton);
    this->update(this->solarCellsButton);


    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(pointsLabel, 0, 1);
    gridLayout->addWidget(rangeLabel, 2, 0);
    gridLayout->addWidget(nbSensorLabel, 3, 0);
    gridLayout->addWidget(improveRangeButton, 2, 1);
    gridLayout->addWidget(getMoreSensorsButton, 3, 1);
    gridLayout->addWidget(solarCellsButton, 4, 1);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    this->drawfield = new DrawField(game);
    mainLayout->addWidget(this->drawfield);
    mainLayout->addLayout(gridLayout);

    QWidget* mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
}


void MainWindow::setUpInterfaceCommunication() {
    connect(this->improveRangeButton, SIGNAL(clicked()), this, SLOT(improveRange()));
    connect(this->getMoreSensorsButton, SIGNAL(clicked()), this, SLOT(buySensor()));
    connect(this->solarCellsButton, SIGNAL(clicked()), this, SLOT(useSolarCells()));

    this->fireTimer = new QTimer(this);//FIXME non-pointer ?
    connect(fireTimer, SIGNAL(timeout()), this, SLOT(potentialFire()));
    fireTimer->start(GameConstants::MS_BETWEEN_POTENTIAL_FIRES);

    this->batteriesTimer = new QTimer(this);//FIXME see up there
    connect(batteriesTimer, SIGNAL(timeout()), this, SLOT(decreaseBatteries()));
    batteriesTimer->start(GameConstants::MS_BETWEEN_BATTERY_DECREASING);
}

void MainWindow::update(QPushButton* b) {
    if (b == this->improveRangeButton) {
        this->improveRangeButton->setText(tr(GameConstants::IMPROVE_DETEC_RANGE_BUTTON_TEXT) + INT_TO_QSTR(this->game->getDetecRangeImprovCost()));
    }
    else if (b == this->getMoreSensorsButton) {
        this->getMoreSensorsButton->setText(tr(GameConstants::INCREASE_SENSOR_NB_BUTTON_TEXT) + INT_TO_QSTR(this->game->getIncrSensorNbCost()));
    }
    else if (b == this->solarCellsButton) {
        this->solarCellsButton->setText(tr(GameConstants::SOLAR_CELLS_BUTTON_TEXT) + INT_TO_QSTR(this->game->getSolarCellCost()));
    }
    else {
        throw UnhandledCaseException("MainWindow", "update(QPushButton)");
    }
}


void MainWindow::update(QLabel* l) {
   if (l == this->pointsLabel) {
       this->pointsLabel->setText(tr(GameConstants::POINTS_LABEL_TEXT) + QString::number(this->game->getPoints()));
   }
   else if (l == this->rangeLabel) {
       this->rangeLabel->setText(tr(GameConstants::DETECTION_RANGE_LABEL_TEXT) + QString::number(this->game->getDetectionRange()));
   }
   else if (l == this->nbSensorLabel) {
       this->nbSensorLabel->setText(tr(GameConstants::SENSOR_NUMBER_LABEL_TEXT) + QString::number(this->game->getNbSensors()));
   }
   else {
       throw UnhandledCaseException("MainWindow", "update(QLabel)");
   }

}

void MainWindow::setClickable(QPushButton* button, int cost) {
    int points = this->game->getPoints();
    bool enable = true;

    if (points < cost) {
        enable = false;
    }
    button->setEnabled(enable);
}

//TODO maybe on a paintevent ? call to super and then that ? Would be more efficient and clean than calling at each paying/earning function ?
void MainWindow::setClickableForAll() {
    this->setClickable(this->improveRangeButton, this->game->getDetecRangeImprovCost());
    this->setClickable(this->getMoreSensorsButton, this->game->getIncrSensorNbCost());
    this->setClickable(this->solarCellsButton, this->game->getSolarCellCost());
    if (this->game->getUsingSolarCellTechnology()) {
        this->solarCellsButton->setEnabled(false);
    }
}


/* SLOT function */
void MainWindow::improveRange() {
    this->game->improveDetectionRange();
    this->update(this->pointsLabel);
    this->update(this->rangeLabel);
    this->drawfield->update();
    this->setClickableForAll();
}


/* SLOT function */
void MainWindow::buySensor() {
    this->game->buySensor();
    this->update(this->pointsLabel);
    this->update(this->nbSensorLabel);
    this->drawfield->update();
    this->setClickableForAll();
}


/* SLOT function */
void MainWindow::potentialFire() {
    Coordinates* fire = this->game->potentialRandomFire();
    if (fire != NULL) {
        this->drawfield->displayFire(fire);
    }
    this->update(this->pointsLabel);
    this->setClickableForAll();
}

/* SLOT function */
void MainWindow::decreaseBatteries() {
    this->game->decreaseBatteries();
    this->drawfield->update();
}

/* SLOT function */
void MainWindow::useSolarCells() {
    this->game->useSolarCells();
}

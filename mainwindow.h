#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTimer>


#include "game.h"
#include "drawfield.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param game must be initialized and ready
     * @param parent
     */
    explicit MainWindow(Game* game, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Game* game;

    QLabel* pointsLabel;
    QLabel* rangeLabel;
    QLabel* nbSensorLabel;

    QPushButton* improveRangeButton;
    QPushButton* getMoreSensorsButton;
    QPushButton* solarCellsButton;

    DrawField* drawfield;

    QTimer* fireTimer;

    QTimer* batteriesTimer;


    /**
     * @brief setUpArchitecture Called in constructor to create the widgets
     */
    void setUpArchitecture();

    /**
     * @brief setUpInterfaceCommunication Called in constructor to deal with SIGNALS and SLOTS
     */
    void setUpInterfaceCommunication();

    /**
     * @brief update set the widget's text to what it should be, based on
     * game values the widget is depending on.
     * @param b
     */
    void update(QPushButton* b); // THROWS UnhandledCaseException

    /**
     * @brief update set the widget's text to what it should be, based on
     * the game values it's depending on.
     * @param l
     */
    void update(QLabel* l); // THROWS UnhandledCaseException

    /**
     * @brief setClickable Make a button clickable if there are enough points to use it, or unclickable otherwise.
     * @param button The button to set
     * @param cost The number that must be inferior or equal to the current amount of points for the button to be clickable
     */
    void setClickable(QPushButton* button, int cost);

    /**
     * @brief setClickableForAll Make all buttons either clickable or unclickable, depending on their "cost" and the points remaining
     */
    void setClickableForAll();

private slots :
    /**
     * @brief improveRange Improve the detection range and substracts the cost,
     * if there are enough points.
     */
    void improveRange();

    /**
     * @brief buySensor Create another sensor and substracts the cost,
     * if there are enough points.
     */
    void buySensor();

    void potentialFire();

    void decreaseBatteries();

    void useSolarCells();
};

#endif // MAINWINDOW_H

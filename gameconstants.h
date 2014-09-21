#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

#include <cmath>


class GameConstants {

public :
    static double distance(int x1, int y1, int x2, int y2) {
        return   sqrt(
                     pow(x2 - x1, 2)
                             +
                     pow(y2 - y1, 2)
                 );
     }



/*----------STARTING GAME VALUES----------*/
    /**
     * @brief STARTING_POINTS Default value for points when starting a game
     */
    static const int STARTING_POINTS =
    #ifdef DEBUG_MODE
         15
    #else
         20
    #endif
         ;

    /**
     * @brief STARTING_DETECTION_RANGE Default value for the sensors' detection range when starting a game
     */
    static const int STARTING_DETECTION_RANGE = 30;

    /**
     * @brief STARTING_COMMUNICATION_RANGE Default value for the sensors' communication range when starting a game
     */
    static const int STARTING_COMMUNICATION_RANGE = 150;

/*----------POINTS----------*/
    /**
     * @brief DETEC_RANGE_IMPROV_COST How much it costs to improve detection range (at first...)
     */
    static const int DETEC_RANGE_IMPROV_COST = 2;

    /**
     * @brief SENSOR_COST How much it costs to buy another sensor
     */
    static const int SENSOR_COST = 1;

    /**
     * @brief SOLAR_CELLS_COST How much it costs to use solar cell technology
     */
    static const int SOLAR_CELLS_COST = 5;

    /**
     * @brief POINTS_FOR_PREVENTING_FIRE How much the player earns when he detected a fire thanks to the sensors.
     */
    static const int POINTS_FOR_PREVENTING_FIRE = 3;

/*----------IMPROVEMENT----------*/
    /**
     * @brief DETECTION_RANGE_IMPROVEMENT Amount that will be added to the sensors' detection range when improved
     */
    static const int DETECTION_RANGE_IMPROVEMENT = 5;

/*----------LABELS----------*/
    /**
     * @brief POINTS_LABEL_TEXT The text that will be displayed to show the current amount of points.
     * Does not include the actual number, and must be added right after.
     */
    static const char POINTS_LABEL_TEXT[];

    /**
     * @brief SENSOR_NUMBER_LABEL_TEXT The text that will be displayed to show the current number of sensors.
     * Does not include the actual number, and must be added right after.
     */
    static const char SENSOR_NUMBER_LABEL_TEXT[];

    /**
     * @brief DETECTION_RANGE_LABEL_TEXT The text that will be displayed to show the current detection range of the sensors.
     * Does not include the actual number, and must be added right after.
     */
    static const char DETECTION_RANGE_LABEL_TEXT[];

/*----------BUTTONS----------*/
    /**
     * @brief IMPROVE_DETEC_RANGE_BUTTON_TEXT Text on the button used to improve detection range.
     * Cost is intended to be added right after.
     * e.g "Improve : "
     */
    static const char IMPROVE_DETEC_RANGE_BUTTON_TEXT[];

    /**
     * @brief INCREASE_SENSOR_NB_BUTTON_TEXT Text on the button used to get more sensors.
     * Cost is intended to be added right after.
     * e.g "Get more : "
     */
    static const char INCREASE_SENSOR_NB_BUTTON_TEXT[];

    /**
     * @brief SOLAR_CELLS_BUTTON_TEXT Text on the button to use solar technology
     * Cost is intended to be added right after.
     * e.g "Get solar cells : "
     */
    static const char SOLAR_CELLS_BUTTON_TEXT[];

/*----------MAPPING----------*/
    /**
     * @brief MAP_HEIGHT Size of the map on the Y axis.
     */
    static const int MAP_HEIGHT = 500;

    /**
     * @brief MAP_WIDTH Size of the map on the X axis
     */
    static const int MAP_WIDTH = 500;

    /**
     * @brief SINK_X Location of the sink on the X axis.
     */
    static const int SINK_X = MAP_HEIGHT/2;

    /**
     * @brief SINK_Y Location of the sink on the Y axis.
     */
    static const int SINK_Y = SINK_X;


/*----------ENVIRONMENT----------*/
    /**
     * @brief MS_BETWEEN_BATTERY_DECREASING Time passes, decreasing the sensors' energy, every MS_BETWEEN_BATTERY_DECREASING.
     */
    static const int MS_BETWEEN_BATTERY_DECREASING = 300;
    /**
     * @brief MS_BETWEEN_POTENTIAL_FIRES Milliseconds between each "Will a fire suddenly start up ?" test.
     */
    static const int MS_BETWEEN_POTENTIAL_FIRES = 1000;

    /**
     * @brief PROB_FIRE_APPEARS Chances that a fire starts somewhere. The test is done every MS_BETWEEN_POTENTIAL_FIRES ms.
     */
    static const double PROB_FIRE_APPEARS = 0.3;
};


#endif // GAMECONSTANTS_H

//
// Created by jpnsantos on 21/03/24.
//

#ifndef DA_WATER_SUPPLY_RELIABILITYMENU_H
#define DA_WATER_SUPPLY_RELIABILITYMENU_H

#include "Menu.h"
#include <iostream>
#include <limits>
#include "managers/ReliabilityManager.h"

using namespace std;

class ReliabilityMenu : public Menu {
public:
    void display() override;

private:

    ReliabilityManager reliabilityManager;

    static void backToMain();

    void printFooterOption();

    void showNoAffectingStations();

    void showCitiesAffectedByStation();

    void showAffectingStations();

    void showStationsReliability();

    void showPipelineReliability();

    void showReservoirsReliability();

    void showAffectingPipes();

    void showAffectedCities();

    void sequentialPipeRemoval();

    void sequentialStationRemoval();

    void resetChanges();
};

#endif //DA_WATER_SUPPLY_RELIABILITYMENU_H

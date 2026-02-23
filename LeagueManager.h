#ifndef LEAGUEMANAGER_H
#define LEAGUEMANAGER_H

#include "TeamTrees.h"
#include "Schedule.h"
#include "Scoring.h"
#include <string>

class LeagueManager {

private:
    TeamTrees teams;
    Schedule schedule;
    Scoring scoring;

    std::string leagueName;

    int teamLimit;
    int playersPerTeam;

    bool hasPlayoff;
    int regularSeasonWeeks;
    int playoffWeeks;

    void setupLeague();
    void addTeamSetup();
    void editOrAddLoop();
    void editPlayers();

    void mainMenu();
    void viewSchedule();
    void addScore();
    void viewScores();
    void rankingsStub();
    void clearAll();

    std::string getLineInput();
    int getIntegerInput();
    char getCharInput();
    void pause();

public:
    LeagueManager();
    void run();
};

#endif
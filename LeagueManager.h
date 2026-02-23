#ifndef LEAGUEMANAGER_H
#define LEAGUEMANAGER_H

#include <string>
#include "HashTable.h"
#include "Schedule.h"
#include "Scoring.h"

class LeagueManager {

private:

    // League Info
    std::string leagueName;

    int teamLimit;
    int playersPerTeam;

    bool hasPlayoff;
    int regularSeasonWeeks;
    int playoffWeeks;

    // Core Systems
    HashTable teams;
    Schedule schedule;
    Scoring scoring;

    // Setup
    void setupLeague();
    void addTeamSetup();
    void editPlayers();
    void editOrAddLoop();

    // Main Menu
    void mainMenu();
    void viewSchedule();
    void addScore();
    void editScore();
    void viewScores();
    void rankingsStub();

    // Utility
    void clearAll();

    // Input Helpers
    std::string getLineInput();
    int getIntegerInput();
    char getCharInput();
    void pause();

public:
    LeagueManager();
    void run();
};

#endif
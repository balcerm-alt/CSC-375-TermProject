#include "LeagueManager.h"
#include <iostream>
#include <cstdlib>

//constructor

LeagueManager::LeagueManager()
        : teamLimit(0),
          playersPerTeam(0),
          hasPlayoff(false),
          regularSeasonWeeks(0),
          playoffWeeks(0) {}

void LeagueManager::run() {
    setupLeague();
    mainMenu();
}

//helpers

std::string LeagueManager::getLineInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int LeagueManager::getIntegerInput() {
    while (true) {
        std::string input = getLineInput();
        try {
            return std::stoi(input);
        }
        catch (...) {
            std::cout << "Invalid number. Try again: ";
        }
    }
}

char LeagueManager::getCharInput() {
    std::string input = getLineInput();
    if (!input.empty())
        return input[0];
    return '\0';
}

void LeagueManager::pause() {
    std::cout << "Close Page (press Enter)...";
    getLineInput();
}

//setup

void LeagueManager::setupLeague() {

    std::cout << "\nHello! Welcome to a League of Our Own!\n";

    std::cout << "Please Enter Name of Your League: ";
    leagueName = getLineInput();

    std::cout << "Please Enter Quantity of Teams: ";
    teamLimit = getIntegerInput();

    std::cout << "Please Enter Quantity of Players per Team: ";
    playersPerTeam = getIntegerInput();

    std::cout << "Will There Be a Playoff (Y/N): ";
    char playoffChoice = getCharInput();

    hasPlayoff = (playoffChoice == 'Y' || playoffChoice == 'y');

    if (hasPlayoff) {
        std::cout << "How Many Weeks Played Before Playoff: ";
        regularSeasonWeeks = getIntegerInput();

        std::cout << "How Many Weeks of Playoff: ";
        playoffWeeks = getIntegerInput();
    }
    else {
        regularSeasonWeeks = 0;
        playoffWeeks = 0;
    }

    for (int i = 0; i < teamLimit; i++)
        addTeamSetup();

    editOrAddLoop();

    std::cout << "Generate Schedule? (Y/N): ";
    char generateChoice = getCharInput();

    if (generateChoice == 'Y' || generateChoice == 'y')
        schedule.generate(teams, regularSeasonWeeks);
}

void LeagueManager::addTeamSetup() {

    std::cout << "\nAdd Team Name: ";
    std::string teamName = getLineInput();

    Teams newTeam(teamName);

    std::cout << "Add Players:\n";

    for (int i = 0; i < playersPerTeam; i++) {
        std::cout << "Player " << i + 1 << ": ";
        std::string playerName = getLineInput();
        newTeam.addPlayer(Player(playerName));
    }

    teams.insert(teamName, newTeam);
}

void LeagueManager::editOrAddLoop() {

    while (true) {
        std::cout << "\nWould You Like To Add Teams or Edit Players (Y/N): ";
        char choice = getCharInput();

        if (choice == 'N' || choice == 'n')
            break;

        std::cout << "1. Add Teams\n";
        std::cout << "2. Edit Players\n";
        std::cout << "Select Option: ";

        int option = getIntegerInput();

        if (option == 1)
            addTeamSetup();
        else if (option == 2)
            editPlayers();
    }
}

void LeagueManager::editPlayers() {

    teams.displayAll();

    std::cout << "Enter Team Name To Edit: ";
    std::string teamName = getLineInput();

    Teams* team = teams.search(teamName);

    if (team == nullptr) {
        std::cout << "Team not found.\n";
        return;
    }

    team->displayRoster();

    std::cout << "Select Player To Edit (number): ";
    int selection = getIntegerInput();

    Player* player = team->getPlayer(selection - 1);

    if (player != nullptr) {
        std::cout << "Enter New Player Name: ";
        std::string newName = getLineInput();
        *player = Player(newName);
        std::cout << "Player Updated.\n";
    }
}

// ================= MAIN MENU =================

void LeagueManager::mainMenu() {

    while (true) {

        std::cout << "\n===== " << leagueName << " =====\n";
        std::cout << "1. Edit Setup\n";
        std::cout << "2. View Schedule\n";
        std::cout << "3. Add Score\n";
        std::cout << "4. Edit Score\n";
        std::cout << "5. View Scores\n";
        std::cout << "6. Rankings\n";
        std::cout << "7. Clear\n";
        std::cout << "8. Close Application\n";
        std::cout << "Select Option: ";

        int choice = getIntegerInput();

        switch (choice) {

            case 1: setupLeague(); break;
            case 2: viewSchedule(); break;
            case 3: addScore(); break;
            case 4: editScore(); break;
            case 5: viewScores(); break;
            case 6: rankingsStub(); break;
            case 7: clearAll(); break;

            case 8: {
                std::cout << "Would You Like To Close (Y/N): ";
                char closeChoice = getCharInput();
                if (closeChoice == 'Y' || closeChoice == 'y') {
                    std::cout << "\nApplication Closed.\n";
                    std::exit(0);
                }
                break;
            }

            default:
                std::cout << "Invalid Option.\n";
        }
    }
}

// ================= MENU ACTIONS =================

void LeagueManager::viewSchedule() {
    schedule.displayGames();
    pause();
}

void LeagueManager::addScore() {

    schedule.displayGames();

    std::cout << "\nSelect Week Number: ";
    int week = getIntegerInput();
    int weekIndex = week - 1;

    std::cout << "Select Game Number: ";
    int selection = getIntegerInput();

    int gameCounter = 0;
    Game* selectedGame = nullptr;

    for (int i = 0; i < 20; i++) {

        Game* g = schedule.getGame(weekIndex, i);
        if (g == nullptr)
            break;

        if (!g->isByeGame()) {
            gameCounter++;
            if (gameCounter == selection) {
                selectedGame = g;
                break;
            }
        }
    }

    if (selectedGame == nullptr) {
        std::cout << "Invalid selection.\n";
        return;
    }

    scoring.updateGameScore(*selectedGame);
}

void LeagueManager::editScore() {
    std::cout << "Edit Score Not Implemented Yet.\n";
    pause();
}

void LeagueManager::viewScores() {
    teams.displayAll();
    pause();
}

void LeagueManager::rankingsStub() {
    std::cout << "Rankings Not Implemented Yet.\n";
    pause();
}

void LeagueManager::clearAll() {

    std::cout << "Would You Like To Clear (Y/N): ";
    char choice = getCharInput();

    if (choice == 'Y' || choice == 'y') {

        teams = HashTable();
        schedule = Schedule();
        scoring = Scoring();

        leagueName = "";
        teamLimit = 0;
        playersPerTeam = 0;
        regularSeasonWeeks = 0;
        playoffWeeks = 0;
        hasPlayoff = false;

        std::cout << "\nSystem Cleared.\n";

        setupLeague();
    }
}
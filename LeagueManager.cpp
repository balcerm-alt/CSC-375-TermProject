#include "LeagueManager.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

LeagueManager::LeagueManager()
    : teamLimit(0),
      playersPerTeam(0),
      hasPlayoff(false),
      regularSeasonWeeks(0),
      playoffTeamCount(0)
{
}

void LeagueManager::run()
{
    while (true)
    {
        setupLeague();
        mainMenu();
    }
}

std::string LeagueManager::getLineInput()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::string LeagueManager::getRequiredLineInput()
{
    while (true)
    {
        std::string input = getLineInput();
        bool hasRealText = false;

        for (int i = 0; i < static_cast<int>(input.length()); i++)
        {
            if (input[i] != ' ' && input[i] != '\t')
            {
                hasRealText = true;
                break;
            }
        }

        if (hasRealText)
            return input;

        std::cout << "Input cannot be blank. Try again: ";
    }
}

int LeagueManager::getIntegerInput()
{
    while (true)
    {
        std::string input = getLineInput();

        if (input.empty())
        {
            std::cout << "Invalid number. Try again: ";
            continue;
        }

        try
        {
            return std::stoi(input);
        }
        catch (...)
        {
            std::cout << "Invalid number. Try again: ";
        }
    }
}

int LeagueManager::getPositiveIntegerInput()
{
    while (true)
    {
        int value = getIntegerInput();

        if (value > 0)
            return value;

        std::cout << "Enter a number greater than 0: ";
    }
}

char LeagueManager::getCharInput()
{
    while (true)
    {
        std::string input = getLineInput();

        if (input.length() == 1)
        {
            char c = input[0];
            if (c == 'Y' || c == 'y' || c == 'N' || c == 'n')
                return c;
        }

        std::cout << "Please enter Y or N: ";
    }
}

void LeagueManager::pause()
{
    std::cout << "Close Page (press Enter)...";
    getLineInput();
}

bool LeagueManager::isValidPlayoffSize(int size)
{
    if (size == 2 && teamLimit >= 2)
        return true;
    if (size == 4 && teamLimit >= 4)
        return true;
    if (size == 8 && teamLimit >= 8)
        return true;

    return false;
}

void LeagueManager::printValidPlayoffOptions()
{
    std::cout << "How many teams in playoff (";

    bool first = true;

    if (teamLimit >= 2)
    {
        std::cout << "2";
        first = false;
    }

    if (teamLimit >= 4)
    {
        if (!first)
            std::cout << ", ";
        std::cout << "4";
        first = false;
    }

    if (teamLimit >= 8)
    {
        if (!first)
            std::cout << ", ";
        std::cout << "8";
    }

    std::cout << "): ";
}

void LeagueManager::rebuildHashTable()
{
    Teams* arr[100];
    int count = 0;

    teams.fillArray(arr, count);
    teamTable.clear();

    for (int i = 0; i < count; i++)
        teamTable.insert(arr[i]->getName(), arr[i]);
}

void LeagueManager::setupLeague()
{
    teams.clear();
    schedule.clear();
    teamTable.clear();
    playoff.clear();
    playoffTeamCount = 0;

    std::cout << "\nHello! Welcome to a League of Our Own!\n";

    std::cout << "\nPlease Select League Setup:\n";
    std::cout << "1. Manual Setup\n";
    std::cout << "2. Load Teams from File\n";
    std::cout << "Select Option: ";

    int setupChoice = getIntegerInput();

    if (setupChoice == 2)
    {
        loadTeamsFromFile();

        Teams* tempArray[100];
        int count = 0;
        teams.fillArray(tempArray, count);
        teamLimit = count;

        if (teamLimit == 0)
        {
            std::cout << "No teams loaded. Switching to manual setup.\n";
            setupChoice = 1;
        }
        else
        {
            std::cout << "\nLoaded " << teamLimit << " teams.\n";
            if (count > 0)
                playersPerTeam = tempArray[0]->getPlayerCount();
        }
    }

    if (setupChoice == 1)
    {
        std::cout << "Please Enter Name of Your League: ";
        leagueName = getRequiredLineInput();

        while (true)
        {
            std::cout << "Please Enter Quantity of Teams (max 10): ";
            teamLimit = getPositiveIntegerInput();

            if (teamLimit > 10)
            {
                std::cout << "Maximum teams allowed is 10.\n";
                continue;
            }

            if (teamLimit < 2)
            {
                std::cout << "You need at least 2 teams.\n";
                continue;
            }

            break;
        }

        while (true)
        {
            std::cout << "Please Enter Quantity of Players per Team (max 6): ";
            playersPerTeam = getPositiveIntegerInput();

            if (playersPerTeam > 6)
            {
                std::cout << "Maximum players per team is 6.\n";
                continue;
            }

            break;
        }

        for (int i = 0; i < teamLimit; i++)
            addTeamSetup();
    }
    else
    {
        std::cout << "Please Enter Name of Your League: ";
        leagueName = getRequiredLineInput();
    }

    int maxRegularSeasonWeeks = teamLimit - 1;

    std::cout << "Will There Be a Playoff (Y/N): ";
    char playoffChoice = getCharInput();
    hasPlayoff = (playoffChoice == 'Y' || playoffChoice == 'y');

    if (hasPlayoff)
    {
        while (true)
        {
            std::cout << "How Many Weeks In Regular Season (max " << maxRegularSeasonWeeks << "): ";
            regularSeasonWeeks = getPositiveIntegerInput();

            if (regularSeasonWeeks > maxRegularSeasonWeeks)
            {
                std::cout << "Maximum regular season weeks is " << maxRegularSeasonWeeks
                          << " so each team only plays each other once.\n";
                continue;
            }

            break;
        }

        while (true)
        {
            printValidPlayoffOptions();
            playoffTeamCount = getPositiveIntegerInput();

            if (!isValidPlayoffSize(playoffTeamCount))
            {
                std::cout << "Invalid playoff size. Try again.\n";
                continue;
            }

            break;
        }
    }
    else
    {
        while (true)
        {
            std::cout << "How Many Weeks in Season (max " << maxRegularSeasonWeeks << "): ";
            regularSeasonWeeks = getPositiveIntegerInput();

            if (regularSeasonWeeks > maxRegularSeasonWeeks)
            {
                std::cout << "Maximum season weeks is " << maxRegularSeasonWeeks
                          << " so each team only plays each other once.\n";
                continue;
            }

            break;
        }

        playoffTeamCount = 0;
    }

    rebuildHashTable();

    while (true)
    {
        std::cout << "Generate Schedule? (Y/N): ";
        char generateChoice = getCharInput();

        if (generateChoice == 'Y' || generateChoice == 'y')
        {
            schedule.generate(teams, regularSeasonWeeks);
            break;
        }

        editOrAddLoop();
    }
}

void LeagueManager::addTeamSetup()
{
    std::cout << "\nAdd Team Name: ";
    std::string teamName = getRequiredLineInput();

    Teams newTeam(teamName);

    std::cout << "Add Players:\n";

    for (int i = 0; i < playersPerTeam; i++)
    {
        std::cout << "Player " << i + 1 << ": ";
        std::string playerName = getRequiredLineInput();
        newTeam.addPlayer(Player(playerName));
    }

    teams.insert(newTeam);
    rebuildHashTable();
}

void LeagueManager::editOrAddLoop()
{
    while (true)
    {
        std::cout << "\n1. Add Teams\n";
        std::cout << "2. Edit Players\n";
        std::cout << "3. Back\n";
        std::cout << "Select Option: ";

        int option = getIntegerInput();

        if (option == 1)
            addTeamSetup();
        else if (option == 2)
            editPlayers();
        else if (option == 3)
            return;
        else
            std::cout << "Invalid Option.\n";
    }
}

void LeagueManager::editPlayers()
{
    rebuildHashTable();
    teams.displayAll();

    std::cout << "Enter Team Name To Edit: ";
    std::string teamName = getRequiredLineInput();

    Teams* team = teamTable.get(teamName);

    if (team == nullptr)
    {
        std::cout << "Team not found.\n";
        return;
    }

    team->displayRoster();

    std::cout << "Select Player To Edit (number): ";
    int selection = getPositiveIntegerInput();

    Player* player = team->getPlayer(selection - 1);

    if (player != nullptr)
    {
        std::cout << "Enter New Player Name: ";
        std::string newName = getRequiredLineInput();
        player->setName(newName);
        std::cout << "Player Updated.\n";
    }
    else
    {
        std::cout << "Invalid selection.\n";
    }
}

void LeagueManager::mainMenu()
{
    while (true)
    {
        if (playoff.isFinished())
        {
            showChampionScreen();
            continue;
        }

        std::cout << "\n===== " << leagueName << " =====\n";
        std::cout << "1. View Schedule\n";

        if (!playoff.isGenerated())
        {
            std::cout << "2. Add Score (Manual)\n";
            std::cout << "3. Load Scores from File\n";
            std::cout << "4. View Stats\n";
            std::cout << "5. Rankings\n";
            std::cout << "6. Predictions\n";
        }
        else
        {
            std::cout << "2. View Stats\n";
            std::cout << "3. Rankings\n";
            std::cout << "4. Predictions\n";
        }

        if (hasPlayoff)
        {
            if (!playoff.isGenerated())
            {
                std::cout << "7. Playoffs\n";
                std::cout << "8. Clear\n";
                std::cout << "9. Close Application\n";
            }
            else
            {
                std::cout << "5. Playoffs\n";
                std::cout << "6. Clear\n";
                std::cout << "7. Close Application\n";
            }
        }
        else
        {
            if (!playoff.isGenerated())
            {
                std::cout << "7. Clear\n";
                std::cout << "8. Close Application\n";
            }
            else
            {
                std::cout << "5. Clear\n";
                std::cout << "6. Close Application\n";
            }
        }

        std::cout << "Select Option: ";
        int choice = getIntegerInput();

        if (hasPlayoff)
        {
            if (!playoff.isGenerated())
            {
                switch (choice)
                {
                    case 1: viewSchedule(); break;
                    case 2: addRegularSeasonScore(); break;
                    case 3: loadScoresFromFile(); break;
                    case 4: viewScores(); break;
                    case 5: rankingsMenu(); break;
                    case 6: viewPredictions(); break;
                    case 7: playoffMenu(); break;
                    case 8: clearAll(); break;
                    case 9:
                    {
                        std::cout << "Would You Like To Close (Y/N): ";
                        char c = getCharInput();
                        if (c == 'Y' || c == 'y')
                            std::exit(0);
                        break;
                    }
                    default:
                        std::cout << "Invalid Option.\n";
                }
            }
            else
            {
                switch (choice)
                {
                    case 1: viewSchedule(); break;
                    case 2: viewScores(); break;
                    case 3: rankingsMenu(); break;
                    case 4: viewPredictions(); break;
                    case 5: playoffMenu(); break;
                    case 6: clearAll(); break;
                    case 7:
                    {
                        std::cout << "Would You Like To Close (Y/N): ";
                        char c = getCharInput();
                        if (c == 'Y' || c == 'y')
                            std::exit(0);
                        break;
                    }
                    default:
                        std::cout << "Invalid Option.\n";
                }
            }
        }
        else
        {
            if (!playoff.isGenerated())
            {
                switch (choice)
                {
                    case 1: viewSchedule(); break;
                    case 2: addRegularSeasonScore(); break;
                    case 3: loadScoresFromFile(); break;
                    case 4: viewScores(); break;
                    case 5: rankingsMenu(); break;
                    case 6: viewPredictions(); break;
                    case 7: clearAll(); break;
                    case 8:
                    {
                        std::cout << "Would You Like To Close (Y/N): ";
                        char c = getCharInput();
                        if (c == 'Y' || c == 'y')
                            std::exit(0);
                        break;
                    }
                    default:
                        std::cout << "Invalid Option.\n";
                }
            }
            else
            {
                switch (choice)
                {
                    case 1: viewSchedule(); break;
                    case 2: viewScores(); break;
                    case 3: rankingsMenu(); break;
                    case 4: viewPredictions(); break;
                    case 5: playoffMenu(); break;
                    case 6: clearAll(); break;
                    case 7:
                    {
                        std::cout << "Would You Like To Close (Y/N): ";
                        char c = getCharInput();
                        if (c == 'Y' || c == 'y')
                            std::exit(0);
                        break;
                    }
                    default:
                        std::cout << "Invalid Option.\n";
                }
            }
        }
    }
}

void LeagueManager::viewSchedule()
{
    schedule.display();
    pause();
}

void LeagueManager::addRegularSeasonScore()
{
    schedule.display();

    std::cout << "\nSelect Week Number: ";
    int week = getPositiveIntegerInput();
    int weekIndex = week - 1;

    std::cout << "Select Game Number: ";
    int selection = getPositiveIntegerInput();

    int realGameCounter = 0;
    Game* selectedGame = nullptr;

    for (int i = 0; i < 50; i++)
    {
        Game* g = schedule.getGame(weekIndex, i);

        if (g == nullptr)
            break;

        if (!g->isByeGame())
        {
            realGameCounter++;

            if (realGameCounter == selection)
            {
                selectedGame = g;
                break;
            }
        }
    }

    if (selectedGame == nullptr)
    {
        std::cout << "Invalid selection.\n";
        return;
    }

    scoring.updateGame(selectedGame, false);
}

void LeagueManager::viewScores()
{
    teams.displayAll();
    pause();
}

void LeagueManager::viewPredictions()
{
    prediction.displayPrediction(teams, schedule, regularSeasonWeeks);
    pause();
}

void LeagueManager::rankingsMenu()
{
    rankings.display(teams);
    pause();
}

bool LeagueManager::regularSeasonComplete()
{
    for (int week = 0; week < regularSeasonWeeks; week++)
    {
        for (int gameIndex = 0; gameIndex < 50; gameIndex++)
        {
            Game* game = schedule.getGame(week, gameIndex);

            if (game == nullptr)
                break;

            if (!game->isByeGame() && !game->isPlayed())
                return false;
        }
    }

    return true;
}

void LeagueManager::playoffMenu()
{
    if (!hasPlayoff)
        return;

    if (!regularSeasonComplete())
    {
        std::cout << "Playoffs have not been established yet.\n";
        pause();
        return;
    }

    if (!playoff.isGenerated())
    {
        std::cout << "Generate Playoffs (Y/N): ";
        char choice = getCharInput();

        if (choice == 'Y' || choice == 'y')
            playoff.generate(teams, playoffTeamCount);
        else
            return;
    }

    playoff.display(prediction, teams, schedule, regularSeasonWeeks);

    if (playoff.isFinished())
    {
        pause();
        return;
    }

    std::cout << "\nSelect Game: ";
    int choice = getPositiveIntegerInput();
    playoff.scoreSelectedGame(choice, scoring);
    pause();
}

Player* LeagueManager::getMVP()
{
    Teams* arr[100];
    int count = 0;
    teams.fillArray(arr, count);

    Player* best = nullptr;

    for (int i = 0; i < count; i++)
    {
        Player* teamBest = arr[i]->getHighestTotalPointPlayer();

        if (teamBest == nullptr)
            continue;

        if (best == nullptr || teamBest->getTotalPoints() > best->getTotalPoints())
            best = teamBest;
    }

    return best;
}

void LeagueManager::showChampionScreen()
{
    Teams* champ = playoff.getChampion();
    Player* mvp = getMVP();

    std::cout << "\n=== Congratulations "
              << ((champ != nullptr) ? champ->getName() : "Champion")
              << " ===\n";
    std::cout << "=== MVP "
              << ((mvp != nullptr) ? mvp->getName() : "N/A")
              << " ===\n";

    std::cout << "1. Clear\n";
    std::cout << "2. Close Application\n";
    std::cout << "Select Option: ";

    int choice = getIntegerInput();

    if (choice == 1)
        clearAll();
    else if (choice == 2)
        std::exit(0);
    else
        std::cout << "Invalid Option.\n";
}

void LeagueManager::clearAll()
{
    teams.clear();
    schedule.clear();
    teamTable.clear();
    playoff.clear();
    hasPlayoff = false;
    regularSeasonWeeks = 0;
    playoffTeamCount = 0;

    std::cout << "\nSystem Cleared.\n";
    setupLeague();
}

void LeagueManager::loadTeamsFromFile()
{
    std::cout << "\nEnter filename (e.g., teams.txt): ";
    std::string filename = getRequiredLineInput();

    if (TeamsFile(filename))
        std::cout << "Teams loaded successfully!\n";
    else
        std::cout << "Failed to load teams from file.\n";
}

bool LeagueManager::TeamsFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Error: Could not open file " << filename << "\n";
        return false;
    }

    std::string line;
    Teams* currentTeam = nullptr;
    int teamsLoaded = 0;

    while (std::getline(file, line))
    {
        line = clean(line);

        if (line.empty() || line[0] == '/' || line[0] == '#')
            continue;

        if (startsWith(line, "TEAM:"))
        {
            if (currentTeam != nullptr)
            {
                teams.insert(*currentTeam);
                delete currentTeam;
                teamsLoaded++;
            }

            std::string currentTeamName = clean(line.substr(5));
            currentTeam = new Teams(currentTeamName);

            std::cout << "Loading team: " << currentTeamName << "\n";
        }
        else if (currentTeam != nullptr)
        {
            Player newPlayer(line);
            currentTeam->addPlayer(newPlayer);
            std::cout << "  Added player: " << line << "\n";
        }
    }

    if (currentTeam != nullptr)
    {
        teams.insert(*currentTeam);
        delete currentTeam;
        teamsLoaded++;
    }

    file.close();
    rebuildHashTable();

    std::cout << "Loaded " << teamsLoaded << " teams.\n";
    return true;
}

void LeagueManager::loadScoresFromFile()
{
    if (teamLimit == 0)
    {
        std::cout << "No teams loaded. Please set up the league first.\n";
        pause();
        return;
    }

    std::cout << "\n=== Load Scores from File ===\n";
    std::cout << "Enter filename (e.g., scores.txt): ";
    std::string filename = getRequiredLineInput();

    if (ScoresFile(filename))
    {
        std::cout << "\nScores loaded successfully!\n";
        std::cout << "All player points updated\n";
        std::cout << "Team records updated\n";
        std::cout << "Schedule games updated\n";
    }
    else
    {
        std::cout << "Failed to load scores from file.\n";
    }

    pause();
}

Game* LeagueManager::findScheduledGameFlexible(int weekIndex, const std::string& teamA, const std::string& teamB, bool& fileOrderMatchesSchedule)
{
    fileOrderMatchesSchedule = true;

    for (int i = 0; i < 50; i++)
    {
        Game* game = schedule.getGame(weekIndex, i);

        if (game == nullptr)
            break;

        if (game->isByeGame())
            continue;

        std::string scheduledHome = game->getHomeTeam()->getName();
        std::string scheduledAway = game->getAwayTeam()->getName();

        if (scheduledHome == teamA && scheduledAway == teamB)
        {
            fileOrderMatchesSchedule = true;
            return game;
        }

        if (scheduledHome == teamB && scheduledAway == teamA)
        {
            fileOrderMatchesSchedule = false;
            return game;
        }
    }

    return nullptr;
}

void LeagueManager::applyPlayerPointsFromLine(Teams* team, const std::string& line)
{
    if (team == nullptr)
        return;

    std::string playersLine = clean(line.substr(line.find(':') + 1));
    std::stringstream ss(playersLine);
    std::string playerEntry;

    while (std::getline(ss, playerEntry, ','))
    {
        playerEntry = clean(playerEntry);
        size_t colonPos = playerEntry.find(':');

        if (colonPos != std::string::npos)
        {
            std::string playerName = clean(playerEntry.substr(0, colonPos));
            int points = std::stoi(clean(playerEntry.substr(colonPos + 1)));

            bool found = false;

            for (int i = 0; i < team->getPlayerCount(); i++)
            {
                Player* player = team->getPlayer(i);

                if (player != nullptr && player->getName() == playerName)
                {
                    player->addRegularPoints(points);
                    found = true;
                    std::cout << "  " << playerName << " +" << points << " points\n";
                    break;
                }
            }

            if (!found)
            {
                std::cout << "Warning: Player '" << playerName
                          << "' not found on team '" << team->getName() << "'\n";
            }
        }
    }
}

bool LeagueManager::ScoresFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Error: Could not open file " << filename << "\n";
        return false;
    }

    std::string line;
    int currentWeek = -1;
    std::string fileTeamA = "";
    std::string fileTeamB = "";
    int fileScoreA = 0;
    int fileScoreB = 0;
    std::string homePlayersLine = "";
    std::string awayPlayersLine = "";
    int gamesLoaded = 0;

    while (std::getline(file, line))
    {
        line = clean(line);

        if (line.empty() || line[0] == '/' || line[0] == '#')
            continue;

        if (startsWith(line, "WEEK:"))
        {
            currentWeek = std::stoi(clean(line.substr(5))) - 1;
        }
        else if (startsWith(line, "GAME:"))
        {
            std::string gameLine = clean(line.substr(5));
            size_t vsPos = gameLine.find(" vs ");

            if (vsPos != std::string::npos)
            {
                fileTeamA = clean(gameLine.substr(0, vsPos));
                fileTeamB = clean(gameLine.substr(vsPos + 4));
            }
        }
        else if (startsWith(line, "SCORE:"))
        {
            std::string scoreLine = clean(line.substr(6));
            size_t dashPos = scoreLine.find('-');

            if (dashPos != std::string::npos)
            {
                fileScoreA = std::stoi(clean(scoreLine.substr(0, dashPos)));
                fileScoreB = std::stoi(clean(scoreLine.substr(dashPos + 1)));
            }
        }
        else if (startsWith(line, "HOME_PLAYERS:"))
        {
            homePlayersLine = line;
        }
        else if (startsWith(line, "AWAY_PLAYERS:"))
        {
            awayPlayersLine = line;

            if (currentWeek < 0)
            {
                std::cout << "Warning: Invalid week for game "
                          << fileTeamA << " vs " << fileTeamB << "\n";
                continue;
            }

            bool fileOrderMatchesSchedule = true;
            Game* scheduledGame = findScheduledGameFlexible(currentWeek, fileTeamA, fileTeamB, fileOrderMatchesSchedule);

            if (scheduledGame == nullptr)
            {
                std::cout << "Warning: Scheduled game not found for week "
                          << currentWeek + 1 << ": "
                          << fileTeamA << " vs " << fileTeamB << "\n";
                continue;
            }

            if (scheduledGame->isPlayed())
            {
                std::cout << "Warning: Game already scored for week "
                          << currentWeek + 1 << ": "
                          << scheduledGame->getHomeTeam()->getName() << " vs "
                          << scheduledGame->getAwayTeam()->getName() << "\n";
                continue;
            }

            Teams* scheduledHome = scheduledGame->getHomeTeam();
            Teams* scheduledAway = scheduledGame->getAwayTeam();

            int scheduledHomeScore;
            int scheduledAwayScore;

            if (fileOrderMatchesSchedule)
            {
                scheduledHomeScore = fileScoreA;
                scheduledAwayScore = fileScoreB;

                applyPlayerPointsFromLine(scheduledHome, homePlayersLine);
                applyPlayerPointsFromLine(scheduledAway, awayPlayersLine);
            }
            else
            {
                scheduledHomeScore = fileScoreB;
                scheduledAwayScore = fileScoreA;

                applyPlayerPointsFromLine(scheduledHome, awayPlayersLine);
                applyPlayerPointsFromLine(scheduledAway, homePlayersLine);
            }

            scheduledGame->setScore(scheduledHomeScore, scheduledAwayScore);

            scheduledHome->addPoints(scheduledHomeScore, scheduledAwayScore);
            scheduledAway->addPoints(scheduledAwayScore, scheduledHomeScore);

            if (scheduledHomeScore > scheduledAwayScore)
            {
                scheduledHome->addWin();
                scheduledAway->addLoss();
            }
            else if (scheduledAwayScore > scheduledHomeScore)
            {
                scheduledAway->addWin();
                scheduledHome->addLoss();
            }
            else
            {
                scheduledHome->addTie();
                scheduledAway->addTie();
            }

            gamesLoaded++;

            homePlayersLine = "";
            awayPlayersLine = "";
        }
    }

    file.close();
    std::cout << "Loaded " << gamesLoaded << " games.\n";
    return true;
}

std::string LeagueManager::clean(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\r\n");

    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

bool LeagueManager::startsWith(const std::string& str, const std::string& prefix)
{
    if (str.length() < prefix.length())
        return false;

    return str.compare(0, prefix.length(), prefix) == 0;
}
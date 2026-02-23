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

void LeagueManager::run() //entry point
{
    while (true)
    {
        setupLeague(); //asks setup questions
        mainMenu(); //enters main interface loop
    }
}

std::string LeagueManager::getLineInput() //gathering user input
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int LeagueManager::getIntegerInput() //gathers user input integer form
{
    while (true)
    {
        std::string input = getLineInput();
        try
        {
            return std::stoi(input);
        }
        catch (...)
        {
            std::cout << "Invalid number. Try again: "; //handles invalid responses
        }
    }
}

char LeagueManager::getCharInput() //Gathers input for (Y/N)
{
    std::string input = getLineInput();
    if (!input.empty())
        return input[0];
    return '\0';
}

void LeagueManager::pause() //recieves input for pressing enter to close the page
{
    std::cout << "Close Page (press Enter)...";
    getLineInput();
}

void LeagueManager::setupLeague() //configuration of the league
{

    std::cout << "\nHello! Welcome to a League of Our Own!\n";

    std::cout << "Please Enter Name of Your League: ";
    leagueName = getLineInput(); //names the league off user input

    std::cout << "Please Enter Quantity of Teams: ";
    teamLimit = getIntegerInput(); //enters the amount of teams the league will have

    std::cout << "Please Enter Quantity of Players per Team: ";
    playersPerTeam = getIntegerInput(); //enters the amount of players on a team

    std::cout << "Will There Be a Playoff (Y/N): ";
    char playoffChoice = getCharInput(); //allows user to decide if they would like a playoff or not

    hasPlayoff = (playoffChoice == 'Y' || playoffChoice == 'y');

    if (hasPlayoff) //if there is a playoff there will be a seperate prompt
    {
        std::cout << "How Many Weeks In Regular Season: ";
        regularSeasonWeeks = getIntegerInput();
        std::cout << "How Many Weeks of Playoff: ";
        playoffWeeks = getIntegerInput();
    }
    else //if theres no playoff the standard question for weeks
    {
        std::cout << "How Many Weeks in Season: ";
        regularSeasonWeeks = getIntegerInput();
        playoffWeeks = 0;
    }

    for (int i = 0; i < teamLimit; i++) //calls add team setup for limit of teams
        addTeamSetup();

    while (true)
    {

        editOrAddLoop(); //calls the edit or add loop

        std::cout << "Generate Schedule? (Y/N): ";//will generate schedule unless user wants to go back
        char generateChoice = getCharInput();

        if (generateChoice == 'Y' || generateChoice == 'y')
        {
            schedule.generate(teams, regularSeasonWeeks);
            break;
        }
    }
}

void LeagueManager::addTeamSetup()
{

    std::cout << "\nAdd Team Name: ";//user input for team name
    std::string teamName = getLineInput();

    Teams newTeam(teamName);

    std::cout << "Add Players:\n";

    for (int i = 0; i < playersPerTeam; i++)
    {
        std::cout << "Player " << i + 1 << ": "; //asks for user name and assigns number
        std::string playerName = getLineInput();
        newTeam.addPlayer(Player(playerName));
    }

    teams.insert(newTeam); //adds team/players
}

void LeagueManager::editOrAddLoop() //loop to add teams or edit players
{

    std::cout << "\nWould You Like To Add Teams or Edit Players (Y/N): ";
    char choice = getCharInput();

    if (choice == 'N' || choice == 'n')
        return;

    std::cout << "1. Add Teams\n";
    std::cout << "2. Edit Players\n";
    std::cout << "Select Option: ";

    int option = getIntegerInput(); //gathers input

    if (option == 1)
        addTeamSetup();
    else if (option == 2)
        editPlayers();
}

void LeagueManager::editPlayers()
{

    teams.displayAll(); //displays teams

    std::cout << "Enter Team Name To Edit: ";//search for team to edit player
    std::string teamName = getLineInput();

    Teams* team = teams.search(teamName);

    if (team == nullptr) //validation
    {
        std::cout << "Team not found.\n";
        return;
    }

    team->displayRoster(); //displays roster with name and assigned number

    std::cout << "Select Player To Edit (number): ";
    int selection = getIntegerInput();

    Player* player = team->getPlayer(selection - 1);

    if (player != nullptr)
    {
        std::cout << "Enter New Player Name: ";
        std::string newName = getLineInput();
        player->setName(newName); //changed player name
        std::cout << "Player Updated.\n";
    }
}

void LeagueManager::mainMenu() //main interface for league
{

    while (true)
    {

        std::cout << "\n===== " << leagueName << " =====\n";
        std::cout << "1. View Schedule\n";
        std::cout << "2. Add Score\n";
        std::cout << "3. View Scores\n";
        std::cout << "4. Rankings\n";
        std::cout << "5. Clear\n";
        std::cout << "6. Close Application\n";
        std::cout << "Select Option: ";

        int choice = getIntegerInput(); //gathers input for what user would like to do in interface

        switch (choice) //assigns numbers to interface for user selection
        {

            case 1: viewSchedule(); break; //views the generated schedule
            case 2: addScore(); break; //sends to page to assigns scores to team and player
            case 3: viewScores(); break; //views scores
            case 4: rankingsStub(); break; //ranking NOT SET UP YET
            case 5: clearAll(); break; //clears application

            case 6: //closes application
            {
                std::cout << "Would You Like To Close (Y/N): ";
                char c = getCharInput();
                if ( c == 'Y' || c =='y');
                std::exit(0);
            }

            default:
                std::cout << "Invalid Option.\n"; //validation
        }
    }
}

void LeagueManager::viewSchedule() //shows generated schedule
{
    schedule.display();
    pause();
}

void LeagueManager::addScore() //interface to add score to team and player by week
{

    schedule.display();

    std::cout << "\nSelect Week Number: "; //select the week number you would like to add score to
    int week = getIntegerInput();
    int weekIndex = week - 1;

    std::cout << "Select Game Number: "; //select which game that week you will be adding score to
    int selection = getIntegerInput();

    int realGameCounter = 0; //counts real game
    Game* selectedGame = nullptr;

    for (int i = 0; i < 50; i++)
    {

        Game* g = schedule.getGame(weekIndex, i); //retrieves game stored at selected

        if (g == nullptr) //stop the loop
            break;

        if (!g->isByeGame()) //ignores bye
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
        std::cout << "Invalid selection.\n"; //validation
        return;
    }

    scoring.updateGame(selectedGame);//updates the score
}

void LeagueManager::viewScores() //shows team and player scores
{
    teams.displayAll();
    pause();
}

void LeagueManager::rankingsStub() //shows rankings NOT DONE YET
{
    std::cout << "Rankings Not Implemented Yet.\n";
    pause();
}

void LeagueManager::clearAll() //clears all stored info back to beginning
{

    std::cout << "Would You Like To Clear (Y/N): "; //validation so you dont accidentally clear everything

    char choice = getCharInput();
    if (choice == 'Y' || choice == 'y')
    {
        teams.clear();
        schedule.clear();
        std::cout << "\nSystem Cleared.\n";
        setupLeague();
    }
}
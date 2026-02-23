cmake_minimum_required(VERSION 4.0)
project(Term_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Term_Project main.cpp
        Teams.cpp
        Teams.h
        Schedule.cpp
        Schedule.h
        Scoring.cpp
        Scoring.h
        Ranking.cpp
        Ranking.h
        LeagueManager.cpp
        LeagueManager.h
        Player.cpp
        Player.h
        HashTable.cpp
        HashTable.h
        Game.cpp
        Game.h
        TeamTrees.cpp
        TeamTrees.h)

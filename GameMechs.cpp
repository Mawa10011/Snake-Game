#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    //init board sizes
    boardSizeX = boardX;
    boardSizeY = boardY;

    //init flags
    exitFlag = false;
    loseFlag = false;
    score = 0;

    speedMultiplier = 1;
}

// do you need a destructor?
//NO. not using heap

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input; 
}

int GameMechs::getScore() const
{
    
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here

void GameMechs::setSpeedMultiplier(int multiplier)
{
    speedMultiplier = multiplier;
}
int GameMechs::getSpeedMultiplier() const
{
    return speedMultiplier;
}
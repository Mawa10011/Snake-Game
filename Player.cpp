#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* food) // constructor
{
    mainGameMechsRef = thisGMRef; // ref to gamemech
    foodPointer = food; // ref to food obj
    myDir = STOP; // initial dir is STOP

    // allocate list for snake body
    playerPosList = new objPosArrayList();

    // create starting position
    objPos headStart;
    headStart.setObjPos(
        mainGameMechsRef->getBoardSizeX() / 2,
        mainGameMechsRef->getBoardSizeY() / 2,
        '*'
    );

    // add it to the list
    playerPosList->insertHead(headStart);
}
    



Player::~Player() // destructor
{
    // free snake body's memory
    delete playerPosList;
    playerPosList = nullptr;
}


objPosArrayList* Player::getPlayerPos() const // pointer to snake's pos
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
        char input_dir = mainGameMechsRef->getInput(); // latest input key

        if (input_dir <= 'Z' && input_dir >= 'A') // turns capitals into lowercase using ASCII
        {
            input_dir += 32;
        }

        switch(input_dir) // make myDir match current direction, no 180 degree direction switch
        {
            case 'w': 
                if (myDir != DOWN)
                {
                    myDir = UP;
                }
                break;
            case 's':
                if (myDir != UP)
                {
                   myDir = DOWN;
                }
                break;
            case 'a':
                if (myDir != RIGHT)
                {
                   myDir = LEFT;
                }
                break;
            case 'd':
                if (myDir != LEFT)
                {
                    myDir = RIGHT;
                }
                break;
        }
               
}

// move the player one
void Player::movePlayer()
{
    if (mainGameMechsRef == nullptr) // safety
    {
        return;
    }

    objPos head = playerPosList->getHeadElement(); // get head position

    // dimensions of board
    int board_X = mainGameMechsRef->getBoardSizeX();
    int board_Y = mainGameMechsRef->getBoardSizeY();

    // move head based on current direction, employ wrap around
    switch(myDir)
    {
        case UP:
            head.pos->y--; // y value decrease, go up
            if (head.pos->y == 0) // top wrap around
            {
                head.pos->y = board_Y - 2; 
            }
            break;

        case DOWN:
            head.pos->y++; // y value increase, go down
            if (head.pos->y == board_Y - 1) // bottom wrap around
            {
                head.pos->y = 1; 
            }
            break;

        case LEFT:
            head.pos->x--; // x value decrease, go left
            if (head.pos->x == 0) // left wrap around
            {
                head.pos->x = board_X - 2; 
            }
            break;

        case RIGHT:
            head.pos->x++; // x value increase, go right
            if (head.pos->x == board_X - 1) // right wrap around
            {
                head.pos->x = 1;
            }
            break;

        case STOP:
            break;
    }

    // head-body collision detector
    if(checkSelfCollision(head))
    {
        mainGameMechsRef->setLoseFlag(); // lose flag
        mainGameMechsRef->setExitTrue(); // exit game
        return;
    }

    // head-food collision detector 
    bool Food_eat = false;
    objPosArrayList* foodList = foodPointer->getFoodBucket(); // all food items
    int i = 0;
    for (i=0; i< foodList->getSize(); i++) // go through all the food
    {
        objPos current_Food = foodList->getElement(i); 
        if (head.pos->x == current_Food.pos->x && head.pos-> y == current_Food.pos->y) // if snake = food pos
        {
            Food_eat = true; // if true, dont loop through more
            break;
        }
    }

    playerPosList->insertHead(head); // new head 

    if (Food_eat == true)
    {
        objPos consumedFood = foodList->getElement(i);
        
        if (consumedFood.getSymbol() == 'X'){
            
            //score bonus +5
            for (int j = 0; j < 5; j++) {
                mainGameMechsRef->incrementScore(); 
            }
            
            //speed halved & snake wont grow
            mainGameMechsRef->setSpeedMultiplier(2);
            playerPosList->removeTail();
        }
        
        else { //normal food consumption (o)
            mainGameMechsRef->incrementScore(); // increment every time you eat something
            mainGameMechsRef->setSpeedMultiplier(1);
        }

        foodPointer->generateFood(*playerPosList); // gen new food, not on snake's body
    
    }
    
    else { // move like normal
        
        playerPosList->removeTail(); // remove tail
    }

}

bool Player::checkSelfCollision(const objPos &newHead) const // head-body collision detector
{
    int i = 1;
    for (i = 1; i < playerPosList->getSize(); i++) // skip head, increment through snake
    {
        objPos segment = playerPosList->getElement(i);
        if (segment.isPosEqual(&newHead)) // collision
        {
            return true; 
        }
    }
    return false; // no collision
}
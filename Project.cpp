#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h" 
#include "Food.h" 

using namespace std;
#define DELAY_CONST 100000 // loop delay 

GameMechs* GM; //global pointer to GameMechs object
Player* player; //global pointer to Player object
Food* food; // global pointer to Food object

// function prototypes
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize(); // game setup

    // main game loop 
    while(GM->getExitFlagStatus() == false) // loops while exit flag is true
    {
        GetInput(); // capture input
        RunLogic(); // update game state
        DrawScreen(); // draw screen
        LoopDelay(); // delay before looping again
    }

    // print if game over (snake ran into body)
    if (GM->getLoseFlagStatus())
    {
        MacUILib_printf("\n          G A M E O V E R");
        MacUILib_printf("\nYou lost! Your score is %d\n", GM->getScore());
        MacUILib_Delay(500000); 
        MacUILib_printf(".");
        MacUILib_Delay(500000); 
        MacUILib_printf(" .");
        MacUILib_Delay(500000); 
        MacUILib_printf(" .");
        MacUILib_Delay(500000); 
        MacUILib_printf("\n\nMaybe you can beat that score one day...? ");

    }
    else // print if exited manually 
    {
        MacUILib_printf("\nGame exited.\n\n");
    }

    MacUILib_printf("Click space to close.\n");

    // wait for space key to exit
    char exit_key = 0;
    do
    {
        if (MacUILib_hasChar())
        {
            exit_key = MacUILib_getChar();
        }
    } while (exit_key != ' ');

    CleanUp(); // clean up and free mem

}


void Initialize(void)
{
    MacUILib_init(); 
    MacUILib_clearScreen();

    srand(time(NULL)); // random generator for food 

    // create game board, food object, and player on HEAP
    GM = new GameMechs(30, 15); 
    food = new Food(GM);
    player = new Player(GM, food);

    // snake starting pos
    objPosArrayList* snakeBody = player->getPlayerPos(); 
    objPos playerHead = snakeBody->getHeadElement(); 
    
    // make food, block off player head location
    food->generateFood(*snakeBody);
}

void GetInput(void)
{
    // capture input if key was pressed
   if (MacUILib_hasChar() != 0)
   { 
        GM->setInput(MacUILib_getChar());
   }
}

void RunLogic(void)
{
    //get recent input from game mechs (set by getinput)
    char currentInput = GM->getInput();
    
    // exit game if user enters q
    if (currentInput != 0)
    { 
        if (currentInput == 'q')
        {
            GM->setExitTrue();
        }
    }

    // if player exists
    if (player != nullptr) 
    {
        //update player's dir based on most recent input
        player->updatePlayerDir();

        //move player in that dir
        player->movePlayer();
    }

    GM->clearInput(); // clear for next iteration
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  
    
    if (GM == nullptr) //safety
    {
        return; 
    }

    //get board sizes
    int boardX = GM->getBoardSizeX();
    int boardY = GM->getBoardSizeY();

    objPos wall(0, 0, '#'); //border chars

    //get pointer to food n snake
    objPosArrayList* foodList = food->getFoodBucket();
    objPosArrayList* snakeBody = player->getPlayerPos();
    objPos currentSegment; 
    objPos currentFood;

    //ppa2 drawing board code (w/ getters from gameMech & objPos objects)
    for (int y = 0; y < boardY; y++) 
    {
        for (int x = 0; x < boardX; x++) 
        {
            bool isDrawn = false; //tracking if char's been printed

            if (y == 0 || y == boardY - 1 || x == 0 || x == boardX - 1) // draw the border
            {
                MacUILib_printf("%c", wall.getSymbol());
                isDrawn = true;
            }

            //checking for game objects. food then snake
            if (!isDrawn) {

                //checking food items
                for (int i = 0; i < foodList->getSize(); i++){
                    currentFood = foodList->getElement(i);

                    if (x == currentFood.pos->x && y == currentFood.pos->y){
                        MacUILib_printf("%c", currentFood.getSymbol());
                        isDrawn = true;
                        break; // Stop checking food list
                    }
                }
            }

            //check for snake  
            //only if nothign drawn in food = no overlap
            if (!isDrawn) {
                for (int i = 0; i < snakeBody->getSize(); i++){
                    currentSegment = snakeBody->getElement(i);

                    if (x == currentSegment.pos->x && y == currentSegment.pos->y){
                        MacUILib_printf("%c", currentSegment.getSymbol());
                        isDrawn = true;
                        break; // Stop checking snake list
                    }
                }
            }

            //no food or snake = empty space
            if (!isDrawn){
                MacUILib_printf(" ");
            }
            
        }
        MacUILib_printf("\n"); // next row
    }

    // input menu on screen for user's convenience 
    MacUILib_printf("\n");
    MacUILib_printf("Directions:---------------------------");
    MacUILib_printf("\n|                (W) up                |");
    MacUILib_printf("\n|    (A) left             (D) right    |\n");
    MacUILib_printf("|               (S) down               |\n");
    MacUILib_printf("--------------------------------------");
    MacUILib_printf("\n");
    MacUILib_printf("Score:  %d             Press 'q' to EXIT\n", GM->getScore());
    MacUILib_printf("\nEat the magic gourd (X) for +5 points, slower speed, and unchanged length!");

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST * GM->getSpeedMultiplier()); // 0.1s delay is normal
    //special food = delay*2 = slower
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    // delete heap stuff so no memory leak
    
    if (GM != nullptr) // delete game mech pointer
    {
        delete GM;
        GM = nullptr;
    }

    if (player != nullptr) // delete player pointer
    {
        delete player;
        player = nullptr;
    }

    if (food != nullptr) // delete player pointer
    {
        delete food;
        food = nullptr;
    }
    

    MacUILib_uninit(); // shut down 
    
}

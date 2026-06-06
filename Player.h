#ifndef PLAYER_H // if not defined
#define PLAYER_H // define player header file

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* food); // constructor
        ~Player(); // destructor

        objPosArrayList* getPlayerPos() const; // Upgrade this in iteration 3. *updated, returning whole list      
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here
        bool checkSelfCollision(const objPos &newHead) const;

    private:
        objPosArrayList* playerPosList; // Upgrade this in iteration 3.       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

        Food* foodPointer;
};

#endif
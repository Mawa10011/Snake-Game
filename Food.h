#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h" //need for getting board dim again

class Food
{
    public:
        //contructor has pointer to gameMech
        Food(GameMechs* gameMechanicsPointer);
        ~Food();

        //generates food, block off snake head position
        void generateFood(const objPosArrayList &playerBody);
        
        //food object position getter
        objPos getFoodPosition() const; 

       //new getter to return list pointer for drawing/collision loop
        objPosArrayList* getFoodBucket() const;

    private:
        objPosArrayList* foodBucket; //list to hold multiple food items
        GameMechs* gameMechanicsReference;
};

#endif
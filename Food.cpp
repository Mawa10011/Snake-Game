#include "Food.h"

//constructor
Food::Food(GameMechs* gameMechanicsPointer)
{
    gameMechanicsReference = gameMechanicsPointer;
    //'position' (objPos member) will calls its own constructor

    //allocate on heap
    foodBucket = new objPosArrayList();
}

Food::~Food()
{
    if (foodBucket != nullptr) //deallocate
    {
        delete foodBucket;
        foodBucket = nullptr;
    }
}

objPosArrayList* Food::getFoodBucket() const
{
    return foodBucket;
}

void Food::generateFood(const objPosArrayList &playerBody)
{
    //clear old items and generate new ones
    while (foodBucket->getSize() > 0)
    {
        foodBucket->removeTail();
    }

    int numFoodItems = 3; //generate 3 fodo items
    
    for (int k = 0; k < numFoodItems; k++){
        int boardX = gameMechanicsReference->getBoardSizeX();
        int boardY = gameMechanicsReference->getBoardSizeY();
        int foodX, foodY;
        bool overlap;
        
        //using rand() fro random coordinates
        do {
            overlap = false;

            foodX = (rand() % (boardX - 2)) + 1;
            foodY = (rand() % (boardY - 2)) + 1;
            
            objPos tempFood(foodX, foodY, 'o');

            int i;
            for (i = 0; i < playerBody.getSize(); i++)
            {
                objPos snakeSegment = playerBody.getElement(i);
                if (snakeSegment.isPosEqual(&tempFood))
                {
                    overlap = true;
                    break;
                }
            }
            
            //loop through the existing foodBucket to ensure no overlap
            for (int i = 0; i < foodBucket->getSize(); i++)
            {
                objPos existingFood = foodBucket->getElement(i);

                if (existingFood.isPosEqual(&tempFood))
                {
                    overlap = true;
                    break;
                }
            }
            
        //loop continues if food position is equal to the snake's head position
        } while (overlap); 

        //is this special food
        char foodSymbol = 'o'; //default
        
        if (k == 0) { //make 1st item special
            foodSymbol = 'X';
        }

        objPos newFood(foodX, foodY, foodSymbol);
        foodBucket->insertTail(newFood); //add to  bin
    }
    
}

objPos Food::getFoodPosition() const
{
    return foodBucket->getHeadElement();
}
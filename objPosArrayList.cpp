#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    // initialize cap + size, allocate mem for object positions
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[arrayCapacity];

}

objPosArrayList::~objPosArrayList()
{
  // free any allocated memory
  if (aList != nullptr)
  {
    delete [] aList;
    aList = nullptr;
  }
}

int objPosArrayList::getSize() const
{
  return listSize; // return num of elements in the list
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // full list check
    if (listSize >= arrayCapacity)
    {
      return;
    }

    // shift index one position to the right
    // ex.
    // [S, S ,  ,  ]
    // [S, S, S,   ]

    int i = listSize;
    while (i > 0)
    {
      aList[i] = aList[i-1]; // previous index to current index 
      i--;
    }

    aList[0] = thisPos; // put new element at head

    listSize++; // increase num of valid elements

}

void objPosArrayList::insertTail(objPos thisPos)
{
    // full list check
    if (listSize >= arrayCapacity)
    {
      return;
    }

    // new element at tail
    aList[listSize] = thisPos;

    // increase list size to account for tail
    listSize++;
}

void objPosArrayList::removeHead()
{
  // empty list check
  if (listSize == 0)
  {
    return;
  }

  // shift left
  int i = 0;
  while (i < listSize - 1)
  {
    aList[i] = aList[i+1];
    i++;
  }

  // decrease valid elements
  listSize--;

}

void objPosArrayList::removeTail()
{
    // empty list check
    if (listSize == 0)
    {
      return;
    }

    // remove last element to get rid of the tail
    // still exists in mem, program ignores it
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    // empty list check
    if (listSize == 0)
    {
      return objPos();
    }

    return aList[0]; // head at element 0
}

objPos objPosArrayList::getTailElement() const
{
    // empty list check
    if (listSize == 0)
    {
      return objPos();
    }

    return aList[listSize - 1]; // tail in last element
}

objPos objPosArrayList::getElement(int index) const
{
    // out of range safeguard
    if (index < 0 || index >= listSize)
    {
      return objPos();
    }

    return aList[index];
}
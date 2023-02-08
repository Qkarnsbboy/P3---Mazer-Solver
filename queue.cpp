/*
queue.cpp
*/

#include "queue.h"

//Constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
Queue::Queue(int maxlen) {
    head = 0;
    tail = 0;
    // *** You complete **** CHECKPOINT 3
    // need storage!!
    contents = new Location[maxlen]; //new array of locations with maxlength of (maxlen)

}

//Destructor. releases resources. C++ will call it automatically.
Queue::~Queue() {
    // *** You complete **** CHECKPOINT 3
  delete[] contents; //deletes the queue
}

//Insert a new Location at the end/back of our list
void Queue::add_to_back(Location loc) {

    // *** You complete **** CHECKPOINT 3
  contents[tail] = loc; //sets location at tail to input
  tail++; //iterates tail


}

//Return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {

    // *** You complete **** CHECKPOINT 3
  head++; //iterate head
  return contents[head-1]; //return location of front (can't return it before you iterate it so -1)


}

//Is this Queue empty? (did we extract everything added?)
//This is complete, you don't need to change it.
bool Queue::is_empty() {
    return head == tail; //if head = tail then return true, otherwise false
}


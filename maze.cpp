/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// Add other prototypes here for any functions you wish to use
bool isInBounds(Location, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, result;
    char** mymaze=NULL;
    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }

    mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1

    // For checkpoint 2 you should check the validity of the maze
    // You may do so anywhere you please and can abstract that
    // operation with a function or however you like.

    //check for valid file
    if (mymaze == NULL) //invalid file 
    {
        cout << invalid_maze_message << endl;
        return 1;
    }
    
    //check for invalid characters
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {   
            //invalid character
            if ( (mymaze[i][j] != 'S') && (mymaze[i][j] != 'F') && (mymaze[i][j] != '.') && (mymaze[i][j] != '#') )
            {
              cout << invalid_char_message << endl;
              cout << mymaze[i][j];

              for (int i = 0; i < rows; i++)
              {
                  delete[] mymaze[i];
              }
              delete[] mymaze;

              return 0;
            }
        }
    }



    //================================
    // When working on Checkpoint 4, you will need to call maze_search
    // and output the appropriate message or, if successful, print
    // the maze.  But for Checkpoint 1, we print the maze, regardless.
    result = maze_search(mymaze, rows, cols);
    
    if (result == 1) //succesful
    {
      print_maze(mymaze, rows, cols);

    }
    else if (result == -1) //bad format
    {
      cout << invalid_maze_message << endl;

      for (int i = 0; i < rows; i++)
      {
        delete[] mymaze[i];
      }
      delete[] mymaze;

      return 1;

    }
    else if (result == 0) //no path found
    {
      cout << no_path_message << endl;

      for (int i = 0; i < rows; i++)
      {
        delete[] mymaze[i];
      }
      delete[] mymaze;

      return 1;
    }
    

    //================================
    // ADD CODE BELOW 
    // to delete all memory that read_maze allocated: CHECKPOINT 2

    //delete inner arrays
    for (int i = 0; i < rows; i++)
    {
      delete[] mymaze[i];
    }

    //delete outer array
    delete[] mymaze;

    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
    // *** You complete **** CHECKPOINT 4
  
  //1. check if correctly formatted --> return -1 if not valid (find start and finish cells)
  int startRow = 0;
  int startCol = 0;
  int finishRow = 0;
  int finishCol = 0;

  int Fcount = 0;
  int Scount = 0;
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      if (maze[i][j] == 'S') //check if S
      {
        Scount++;

        startRow = i;
        startCol = j;
      }   
      else if (maze[i][j] == 'F') //check if F
      {
        Fcount++;

        finishRow = i;
        finishCol = j;
      }
    }
  }
  if ( (Fcount != 1) || (Scount != 1)) //if not right amount of S and F
  {      
    return -1;
  }

  


  //2. create queue
  Queue queue = Queue(rows*cols);

  //3. Dynamically allocate predecessor and explored arrays (initialize if applicable)

    //explored array
  int** explored = new int*[rows]; 

    //dyac
  for(int i = 0; i < rows; i++)
  {
    explored[i] = new int[cols];
  }

    //initialize all to 0 (0 = not explored, 1 = explored)
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      explored[i][j] = 0;
    }
  }

    //predecessor array
  Location** predecessor = new Location*[rows];

    //dyac
  for(int i = 0; i < rows; i++)
  {
    predecessor[i] = new Location[cols];
  }

    //fill predecessor with empty locations (-1,1)
  Location empty;
  empty.row = -1;
  empty.col = -1;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      predecessor[i][j] = empty;
    }
  }

  //finish location
  Location finish;
  finish.row = finishRow;
  finish.col = finishCol;

  //4. breadth-first-maze_search

    //mark start location as explored
  explored[startRow][startCol] = 1;
    //add start location to queue
  Location start;
  start.row = startRow;
  start.col = startCol;
  queue.add_to_back(start);

  //bool to check if we have finished or not
  bool foundFinish = false;

    //while q is not empty && we have not found found
    while( (!queue.is_empty()) && (!foundFinish) )
    {
      //set loc = extract the item from the front of queue
      Location loc = queue.remove_from_front();

      //for each neighbor (N,W,S,E) of loc 
      Location north;

        //valid index
      if ( (loc.row-1 >= 0) && (loc.row-1 < rows) )
      {
        north.row = loc.row-1;
      }
      else 
      {
        north.row = loc.row;
      }
      north.col = loc.col;

      Location west;
      west.row = loc.row;
        //valid location
      if ( (loc.col-1 >= 0) && (loc.col-1 < cols) )
      {
        west.col = loc.col-1;
      }
      else 
      {
        west.col = loc.col;
      }
      

      Location south;
      if ( (loc.row+1 >= 0) && (loc.row+1 < rows) )
      {
        south.row = loc.row+1;
      }
      else 
      {
        south.row = loc.row;
      }
      south.col = loc.col;

      Location east;
      east.row = loc.row;
      if ( (loc.col+1 >= 0) && (loc.col+1 < cols) )
      {
        east.col = loc.col+1;
      }
      else 
      {
        east.col = loc.col;
      }
      

      //north
      //if neighbor is valid, open, and not explored
      if ( (isInBounds(north, rows, cols)) && //in bounds
          (maze[north.row][north.col] == '.') && //open
          (explored[north.row][north.col] == 0) && //not explored (0 means not explored)
          (!foundFinish) ) //if finish found --> exit
      {
        //mark neighbor as explored
        explored[north.row][north.col] = 1;
        //add neighbor to back of queue
        queue.add_to_back(north);
        //set predecessor of the neighbor = location
        predecessor[north.row][north.col] = loc;
      }
      else if (maze[north.row][north.col] == 'F') //found finish
      {
        predecessor[north.row][north.col] = loc;
        foundFinish = true;
      }

      //west
      if ( (isInBounds(west, rows, cols)) &&
          (maze[west.row][west.col] == '.') &&
          (explored[west.row][west.col] == 0) && 
          (!foundFinish) )
      {
        explored[west.row][west.col] = 1;
        queue.add_to_back(west);
        predecessor[west.row][west.col] = loc;
      }
      else if (maze[west.row][west.col] == 'F')
      {
        predecessor[west.row][west.col] = loc;
        foundFinish = true;
      }

      //south
      if ( (isInBounds(south, rows, cols)) &&
          (maze[south.row][south.col] == '.') &&
          (explored[south.row][south.col] == 0) && 
          (!foundFinish) )
      {
        explored[south.row][south.col] = 1;
        queue.add_to_back(south);
        predecessor[south.row][south.col] = loc;
      }
      else if (maze[south.row][south.col] == 'F')
      {
        predecessor[south.row][south.col] = loc;
        foundFinish = true;
      }

      //east
      if ( (isInBounds(east, rows, cols)) &&
          (maze[east.row][east.col] == '.') &&
          (explored[east.row][east.col] == 0) &&
          (!foundFinish) )
      {
        explored[east.row][east.col] = 1;
        queue.add_to_back(east);
        predecessor[east.row][east.col] = loc;
      }
      else if (maze[east.row][east.col] == 'F')
      {
        predecessor[east.row][east.col] = loc;
        foundFinish = true;
      }
    }
      

  //5. Fill in shortest path (assumed to find the finished location)
  if (foundFinish)
  {
    //step through predecessor array (start with last value in predecessor array)
    Location loc;
    loc.row = finish.row;
    loc.col = finish.col;
    loc = predecessor[loc.row][loc.col];

    while( (loc.row != start.row) || (loc.col != start.col) )
    {
    
    //fill in index as a *
    maze[loc.row][loc.col] = '*';

    //update to current predecessor
    loc = predecessor[loc.row][loc.col];
    }
  
  }
  //6. deallocated used memory
    //explored
  for (int i = 0; i < rows; i++)
  {
    delete[] explored[i];
  }
  delete[] explored;

    //predecessor
  for (int i = 0; i < rows; i++)
  {
    delete[] predecessor[i];
  }
  delete[] predecessor;

  //7. return correct status code
  if (foundFinish)
  {
    return 1;
  }
  else
  {
    return 0;
  }


  // DELETE this stub, it's just for Checkpoint 1 to compile.
}

//function to check if in bounds (not useful since I already checked when determining N,W,S,E)
bool isInBounds(Location loc, int rows, int cols)
{
  int locRow = loc.row;
  int locCol = loc.col;

  //out of bounds
  if ( (locRow < 0) || (locRow > rows))
  {
    return false;
  }
  else if ( (locCol < 0) || (locCol > cols))
  {
    return false;
  }

  return true;
}

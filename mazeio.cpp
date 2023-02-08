/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"
#include <cstring>

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols)
{

    // *** You complete **** CHECKPOINT 1

  int r = 0;
  int c = 0;

  //1. declare filestream
  ifstream ifile (filename);

  //2. check if file can be opened
  if (ifile.fail())
  {
    return NULL; //returns NULL is file cannot be opened

  }

  //3. read in first two numbers into integer pointers //if can't return null
  ifile >> r;
  ifile >> c;

  *rows = r;
  *cols = c;

  if (ifile.fail())
  {
    return NULL;
  }

  //4. dynamically allocated a 2d array --> read in maze

  //dynamically allocate 2d char array
  char** maze = new char*[*rows];

  //dynamically allocate a char array at each index of char**
  for (int i = 0; i < *rows; i++)
  {
    maze[i] = new char[*cols+1]; //new char array at each row index (+1 for null)
  }

  //buffer char array //never above size
  char buffer[*cols+1];

  for (int i = 0; i < *rows; i++) //get input
  {
    ifile >> buffer;
    strcpy(maze[i],buffer); //copies whats in buffer into the char array
  }

  //close file stream
  ifile.close();

  //return pointer to dynamically allocated array
  return maze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols)
{

    // *** You complete **** CHECKPOINT 1
  
  //print dimensions
  cout << rows << " " << cols << endl;

  //actual maze
  for (int i = 0; i < rows; i++) //by row
  {
    cout << maze[i] << endl;
  }


}


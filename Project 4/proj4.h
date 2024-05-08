#ifndef PROJ4_H
#define PROJ4_H

/*
 * The struct grid_t contains a pointer p to a 2D array of 
 * unsigned chars with n rows and n columns stored on
 * the heap of this process. Once this is initialized properly,
 * p[i][j] should be a valid unsigned char for all i = 0..(n-1)
 * and j = 0..(n-1).
 * Do not alter this typedef or struct in any way.
 */
typedef struct grid_t {
  unsigned int n;
  unsigned char ** p;
} grid;


/*
 * Initialize g based on fileName, where fileName
 * is a name of file in the present working directory
 * that contains a valid n-by-n grid of digits, where each
 * digit in the grid is between 1 and 9 (inclusive).
 * Do not alter this function prototype in any way.
 */
void initializeGrid(grid * g, char * fileName);


/*
 * This function will compute all diagonal sums in input that equal s using
 * t threads, where 1 <= t <= 3, and store all of the resulting
 * diagonal sums in output. Each thread should do
 * roughly (doesn't have to be exactly) (100 / t) percent of the 
 * computations involved in calculating the diagonal sums. 
 * This function should call (or call another one of your functions that calls)
 * pthread_create and pthread_join when 2 <= t <= 3 to create additional POSIX
 * thread(s) to compute all diagonal sums. 
 * Do not alter this function prototype in any way.
 */
void diagonalSums(grid * input, unsigned long s, grid * output, int t);


/*
 * Write the contents of g to fileName in the present
 * working directory. If fileName exists in the present working directory, 
 * then this function should overwrite the contents in fileName.
 * If fileName does not exist in the present working directory,
 * then this function should create a new file named fileName
 * and assign read and write permissions to the owner. 
 * Do not alter this function prototype in any way.
 */
void writeGrid(grid * g, char * fileName);

/*
 * Free up all dynamically allocated memory used by g.
 * This function should be called when the program is finished using g.
 * Do not alter this function prototype in any way.
 */
void freeGrid(grid * g);

/*
 * You may add any additional function prototypes and any additional
 * things you need to complete this project below this comment. 
 * Anything you add to this file should be commented. 
 */

/* Used for diagonalSums function. Contains two ** char pointers to 2d arrays. f is
 * initialized to input->p in diagonal sums. d is initialized output->p in diagonal sums.
 * int a is initialized input->n (the rows). int s is initialied to sum specified by user by input->s. 
 */ 
typedef struct find_t{
  unsigned int a;
  unsigned char **f;
  unsigned char **d;
  unsigned int s;
} find;

/* Takes a void * pointer to a struct which contains arguments needed from struct find. Computes a third of the rows 
 * when user specifies three threads. Is called even since it starts at the second row and computes from there.  
 */
void * even(void * arguments);

/* Takes a void * pointer to a struct which contains arguments needed from struct find. Computes a third of the rows 
 * when user specifies three threads. Is called odd since it starts ar third row and computes from there. 
 */
void * odd(void * arguments);

/* Takes a void * pointer to struct which contains arguments needed from struct find. Computes half of the rows of the diagonalSums
 * when user specifies two threads. 
 */
void * sum(void * arguments);


#endif


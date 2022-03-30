/*
 * File: main.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 29-Mar-2022 00:22:52
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "myLU.h"
#include "myLU_terminate.h"

/* Function Declarations */
static void argInit_d10xd10_real_T(double result_data[], int result_size[2]);
static double argInit_real_T(void);
static void main_myLU(void);

/* Function Definitions */
/*
 * Arguments    : double result_data[]
 *                int result_size[2]
 * Return Type  : void
 */
static void argInit_d10xd10_real_T(double result_data[], int result_size[2])
{
  int idx0;
  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result_size[0] = 2;
  result_size[1] = 2;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2; idx0++) {
    for (idx1 = 0; idx1 < 2; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result_data[idx0 + 2 * idx1] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_myLU(void)
{
  double A_data[100];
  double L_data[100];
  double invL_data[100];
  int A_size[2];
  int L_size[2];
  int invL_size[2];

  /* Initialize function 'myLU' input arguments. */
  /* Initialize function input argument 'A'. */
  argInit_d10xd10_real_T(A_data, A_size);

  /* Call the entry-point 'myLU'. */
  myLU(A_data, A_size, L_data, L_size, invL_data, invL_size);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_myLU();

  /* Terminate the application.
     You do not need to do this more than one time. */
  myLU_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */

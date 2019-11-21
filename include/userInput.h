/**
 * @Author: B159973
 * @Date:	15/10/2019
 * @Course: Programming Skills - 2019
 * @University of Edinburgh
*/
#ifndef USERINPUT_H
#define	USERINPUT_H

/***************************************************************************//**
 * The number of input arguments that must be typed in the command line in order
 * of the program to run 
 ******************************************************************************/
#define	 ARGC_SIZE 11

/***************************************************************************//**
 * Gathers user input data and validates them. Each time the fucntion gathers 
 * data, it asks the user before to insert correctly the data. If the user enters a wrong 
 * format (ex: to insert a number instead of a string), it asks the user to enter the 
 * data in the correct format and discards the faulty input. 
 * Furthermore if the user inserts the value that doesn't bound to the limits described,
 * again the function asks the user to enter the value within the limits described. 
 * The data are then stored to the configuration structure. Check validation.h
 * to examine the functions that validate the data.
 * @param con:	A pointer that points to the configuration structure
 *              that user data input will be stored.
 * @param argc: The number of arguments passed to the programm via command line.
 * @param argv: The array which contains the string arguments passed from the command
 				line.
 * @return:		Nothing.
 ******************************************************************************/
void get_input(configure *con, int argc, char **argv);

#endif
/**
 * @Author: B159973
 * @Date:	26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/
#ifndef VALIDATION_H
#define	VALIDATION_H

/***************************************************************************//**
 * The value of the size in characters of the file name.
*******************************************************************************/
#define MAX_FILENAME 15
/***************************************************************************//**
 * The value of the size in characters of the file type.
*******************************************************************************/
#define FILE_TYPE_SIZE 4
/***************************************************************************//**
 * The string of the pgm file type.
*******************************************************************************/
#define PGM_TYPE ".pgm"
/***************************************************************************//**
 * The max size of digits of L.
*******************************************************************************/
#define MAX_L  9
/***************************************************************************//**
 * The max size of digits of density ρ. 
*******************************************************************************/
#define MAX_RHO  9
/***************************************************************************//**
 * The limit which the seed value can be. 
 ******************************************************************************/
#define MAX_RANDOM_SEED 900000000
/***************************************************************************//**
 * The max size of digits of seed.
 ******************************************************************************/
#define MAX_RANDOM_SEED_SZ 9


/***************************************************************************//**
 * Validate the size of the given string, if it's lenght is between 0 and 
 * given integer size. 
 * If the size of the string is between these, return success.
 *
 * @param p_str: A pointer to a byte character memory location.
 *				 This pointer is used to point to the first character of a string.
 * @param size:	 The size of the the lenght to be 
 *				 is 1 byte.
 * @return:		 Integer value 1 if the string provided has the same lenght as size
 				 parameter ,else integer value 0.
 ******************************************************************************/
int valid_size(char *p_str, const int size);

/***************************************************************************//**
 * Check if the string that is given is a positive number without any signs or
 * alphabetic characters. 
 * If the string is a number, return success.
 * @param num: 	 A pointer to a byte character memory location which points to the
 *				 string that contains the potential number.
 * @return:		 Integer value 1 if the string provided is a valid number, 
 *				 else integer value 0.
 ******************************************************************************/
int valid_number(char *num);

/***************************************************************************//**
 * Check if the string that is given is a positive fraction without any signs or
 * alphabetic characters. The fraction integer part and decimal part must be devided
 * by a dot.  
 * If the string consists of a valid fraction return success.
 * @param frac:  A pointer to a byte character memory location which points to the
 *				 string that contains the potential fraction.
 * @return:		 Integer value 1 if the string provided is a valid fraction,
 				 else integer value 0.
 ******************************************************************************/
int valid_fraction(char *frac);

/***************************************************************************//**
 * Check if the string provided by file pointer does not have incompatible characters
 * and can be a valid file name which won't cause filesystem errors. The incompatible 
 * characters are checked are:  "%\\^!~|@*><". After that it compares the four last 
 * characters of the string if they are the same with the string pattern.The string 
 * pattern is a string of a valid file type (ex: .txt , .png,etc).
 *
 * @param p_str: A pointer to a byte character memory location.
 *				 This pointer is used to point to the first character of the potential
 *				 filename string.
 * @param pat:	 A pointer to a byte character memory location.This pointer is used to 
 *				 point to the first character of a pattern string .
 * @return:		 Integer value 1 if the string provided has is a valid file name 
 *				 else integer value 0.
 ******************************************************************************/
int valid_filename(char *file, const char *pat);

#endif
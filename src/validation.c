/**
 * @Author: B159973
 * @Date:   26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/
/*========================== Library Files ===========================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "configuration.h"
#include "allocs.h"
#include "validation.h"
/*====================================================================*/
int valid_number(char *num)
{
    if (num == NULL)
        return 0;
    if ( (*num) == '0') /* if the number starts with 0*/
    {
        printf("\nPlease enter a valid number. Do not enter 0 at the begining.\n");
        return 0;
    }
    while( (*num) != '\0')
    {
        if (!(isdigit(*num))) /* if the character is not a digit*/
        {
            printf("\nPlease enter a valid number with no signs\n");
            return 0;
        }
        num++;
    }
    return 1;
}

int valid_fraction(char *frac)
{
    int dot = 0; /*Count that you only found one dot*/
    if (frac == NULL)
        return 0;
    if ( !( ((*frac) == '0') || ( (*frac) == '1') )) /*If it does not starts with 0 or 1 then return false*/
    {
        return 0;
    }
    while( (*frac) != '\0')
    {
        if ( (*frac) == '.' )
            dot++;
        if (! ((isdigit(*frac)) || ( (*frac) == '.' )  )) /*Check if is a proper fraction, digit or a dot */
        {
            printf("\nPlease enter a valid fraction, from 0 to 1 with no signs!\n");
            return 0;
        }
        frac++;
    }
    if (dot > 1) /* if found more than one dot ,return false*/
        return 0;

    return 1;
}

int valid_size(char *p_str, const int size)
{
    int len = 0;
    /* If no allocation happened return false*/
    if (p_str == NULL)
        return 0;
    /*Count lenght of the string and return false if it is bigger than
    size or if it has value of zero.*/
    while( (*p_str) != '\0')
    {
        len++;
        p_str++;
    }
    if (len == 0)
    {
        return 0;
    }
    if (len > size)
    {
        printf("Exceeded size! Please enter a shorter value.");
        return 0;
    }
    return 1;
}

int valid_filename(char *file, const char *pat)
{
    char *p_ch;
    int i;
    char not_allow[] = "%\\^!~|@*><";
    int allowed_name = 1;
    int correct_type = 1;
    char *type = NULL;

    alloc_str(&type, FILE_TYPE_SIZE);
    type = file + (strlen(file) - FILE_TYPE_SIZE);

    /*Check for invalid characters*/
    for (i = 0 ; i < strlen(not_allow); i++)
    {
        p_ch = strchr(file, not_allow[i]);
        if (p_ch != NULL)
        {
            allowed_name = 0;
            printf("\nFound prohibited characters! Cannot enter ^!~|@*><%% for a filename\n");
        }
    }
    /*Check for correct data type*/
    while ( (*type) != '\0' )
    {
        if ((*pat) != (*type))
        {
            correct_type = 0;
        }
        pat++;
        type++;
    }
    /*Notify for incorrect type*/
    if (!correct_type)
        printf("Found incorrect type");

    if (allowed_name && correct_type && (strlen(file) > 4) )
        return 1;
    else
        return 0;
}
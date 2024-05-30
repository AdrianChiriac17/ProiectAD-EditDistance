#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "choosewords.h"
#define WORD_COUNT 10000

void choose_random_word(char **words, char rule[])
{


    FILE *samplewords = fopen("wordlist.txt","r");
    if( samplewords == NULL)
    {
        printf("the file could not be opened!");
        exit(1);
    }

    int i=0;
    while(fgets(words[i],40,samplewords)!= NULL)
    {
        words[i][strlen(words[i])-1]=0;
        i++;
    }

    int howmanywords=i;

    /*
    printf("iata cateva cuvinte!\n");
    for(i=0; i<howmanywords; i++)
    {
        printf("%s\n",words[i]);
    }
    */

    srand(time(NULL)*getpid());

    //O sa aleg intre 2 si 5 cuvinte
    int sentencelength=rand()%100;

    for(int i=0; i<sentencelength; i++)
    {
       int random_index=rand()%1000;
       strcat(rule, words[random_index]);
       strcat(rule,"_");
    }
    rule[strlen(rule)-1]=0;//eliminates the last '_'
}

char *similar_string_generator(char *source)
{
    size_t length = strlen(source);

    char *similarString = malloc(length + 1);
    if (!similarString)
    {
        exit(1);
    }
    strcpy(similarString, source);

    int num_errors = (rand() % length) + 1;

    for (int i = 0; i < num_errors; i++)
    {
        int error_type = rand() % 3;
        int pos = rand() % length;

        if (error_type == 0 && pos < length - 1)
        {
            char temp = similarString[pos];
            similarString[pos] = similarString[pos + 1];
            similarString[pos + 1] = temp;
        }
        else if (error_type == 1 && length > 1)
        {
            memmove(&similarString[pos], &similarString[pos + 1], length - pos);
            similarString[length - 1] = '\0';
            length--;
        }
        else if (error_type == 2)
        {
            similarString[pos] = 'a' + (rand() % 26);
        }
    }

    return similarString;
}


char** allocate2DArray(int rows, int cols)
{
    char **array;
    int i;

    // Allocate memory for the array of pointers
    array = (char**) calloc(rows, sizeof(char*));

    if (array == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(2);
    }

    // Allocate memory for each row
    for (i = 0; i < rows; i++)
    {
        array[i] = (char*) calloc(cols, sizeof(char));

        if (array[i] == NULL)
        {
            printf("Memory allocation failed.\n");

            // Free previously allocated rows
            while (--i >= 0)
                free(array[i]);
            free(array);
            exit(3);
        }
    }

    return array;
}


void free2DArray(char **array, int rows)
{
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

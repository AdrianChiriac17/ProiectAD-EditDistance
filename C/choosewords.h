#ifndef CHOOSEWORDS_H
#define CHOOSEWORDS_H

void choose_random_word(char **words, char rule[]);
char *similar_string_generator(char *source);
char** allocate2DArray(int rows, int cols);
void free2DArray(char **array, int rows);
#endif // CHOOSEWORDS_H

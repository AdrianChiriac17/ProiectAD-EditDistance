#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "choosewords.h"
#define DIM 200000
#include <string.h>
char rule[DIM], input[DIM];
char *fragment_cod;
int dp[DIM][DIM], distance;

int Min(int a, int b)
{
    return a>b ? b : a;
}

int MinimumNoOperations(char rule[DIM], char code_fragment[DIM], int dp[DIM][DIM], int n, int m)
{
    for(int i=0; i<=n; i++)
    {
        dp[i][0]=i;
    }
    for(int j=0; j<=m; j++)
    {
        dp[0][j]=j;
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(rule[i]==code_fragment[j])
                dp[i+1][j+1]=dp[i][j];
            else
            {
                int insert_cost=dp[i+1][j]+1;
                int delete_cost=dp[i][j+1]+1;
                int replace_cost=dp[i][j]+1;

                if(rule[i-1]==code_fragment[j] && rule[i]==code_fragment[j-1])
                {
                    int swap_cost=dp[i-1][j-1]+1; // bonus operation compared to the original "Edit Distance" problem
                    replace_cost=Min(replace_cost,swap_cost);
                }

                dp[i+1][j+1]=Min(Min(insert_cost,delete_cost), replace_cost);
            }
        }
    }
    return dp[n][m];
}

int main ()
{

    printf("Edit Distance w/ swap:\n");

    while(1)
    {
        printf("\nEnter your choice\n");
        printf("1 for user input\n");
        printf("2 for randomly chosen words\n");
        printf("3 for exiting the program\n\n");

        int choice;
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            printf("\n");
            getchar();
            printf("Please type the rule string:        ");
            fgets(rule, DIM, stdin);
            rule[strlen(rule)-1]=0;

            printf("Please type the user input string:  ");
            fgets(input, DIM, stdin);
            input[strlen(input)-1]=0;

            int len_input = strlen(input);
            int len_rule = strlen(rule);

            distance = MinimumNoOperations(rule, input, dp, len_rule, len_input);

            printf("Minimum number of operations required: %d\n", distance);
            memset(input,0,DIM);
            memset(rule,0,DIM);

            break;

        case 2:
            getchar();
            printf("\n");

            char **words= allocate2DArray(1000, 50);
            if(words==NULL)
            {
                exit(4);
            }

            choose_random_word(words, rule);
            printf("The randomly generated word is: ");
            printf("%s",rule);
            printf("\n\n");
            int n=strlen(rule);
            fragment_cod=similar_string_generator(rule);
            printf("The randomly generated code fragment (but still similar to rule) is: ");
            printf("%s",fragment_cod);
            printf("\n\n");
            int m=strlen(fragment_cod);

            distance = MinimumNoOperations(rule, input, dp, n, m);
            printf("Minimum number of operations required: %d\n", distance);

            free2DArray(words, 1000);
            memset(input,0,DIM);
            memset(rule,0,DIM);

            break;

        case 3:
            return 0;
            break;

        default:
            printf("\nInvalid choice!\n");
            break;
        }

    }
    return 0;
}

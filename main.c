#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
/* Global variables */
#define TRUE 1
#define FALSE -1
int debugMode = 0;

typedef struct Node
{
    int size;  // size of the dynamic array
    int top;   // value at the top of the stack
    char *ptr2Array;  // pointer to the dynamic array
}Node;

/* initializes the values of the stack */
void initializeStack( Node *stack )
{
    /* set the size of the stack */
    stack->size = 2;
    /* initialize top of stack */
    stack->top = 0;
    /* allocate memory for the list */
    char *tmpArray = (char*) malloc (sizeof(char*) * sizeof(stack->size));
    /* create a pointer to point to the dynamic array */
    stack->ptr2Array = tmpArray;
}

/* Debugging only */
/* outputs the contents of the tack */
void outputStack( Node *stack )
{
    int i;
    printf("\nStack contains: ");
    for( i = 0; i < stack->size; i++ )
    {
        printf( "%c ", stack->ptr2Array[i] );
    }
    printf("\n");
}

/* pushes the value of the character symbol into the stack */
void push( Node *stack, char value, int debugMode )
{
    int i;
    /* check if the stack is full */
    if ( stack->top == stack->size )
    {
        /* if full then grow the array by 2 */
        char *tmp = (char*) malloc (( sizeof(char*) * (stack->size)) + 2);

        /* copy the values from original to temp */
        for ( i = 0; i < stack->size; i++ )
        {
            tmp[i] = stack->ptr2Array[i];
        }

        /* set the original array equal to temp */
        stack->ptr2Array = tmp;
        //free(stack->ptrToArr);

        /* Increase the size by 2 */
        stack->size += 2;
    }

    /* put the value inside the stack */
    stack->ptr2Array[stack->top] = value;

    /* increment top value */
    stack->top++;

}

/* pops the value of the symbol off the top of the stack */
void pop( Node *stack, int debugMode )
{
    if ( debugMode == TRUE )
    {
        printf("\nDebugging using: POP function\n");
        printf("Value popped from stack was: %c", stack->ptr2Array[stack->top]);
    }
}

/* checks if the stack is empty */
int empty( Node *stack )
{
    /* check if stack is empty */
    if ( stack->top == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* keeps track of what is at the top of the stack */
char top( Node *stack )
{
    return stack->ptr2Array[(stack->top) - 1];
}

/* clears the contents of the stack */
void clear( Node *stack )
{
    int i;
    for ( i = 0; i < stack->size; i++ )
    {
        stack->ptr2Array[i] = '\0';
    }
}

int main (int argc, char** argv)
{
    char input[301];
    int i, j;
    /* Symbol to be stored */
    char symbol;
    /* Closing symbol expected */
    char expectedSym;
    /* variabled to determine if the symbols are balanced */
    int balance;
    Node stack;

    /* Check for debug mode */
    for ( i = 0; i < argc; i++ )
    {
        if ( strcmp( argv[i], "-d" ) == 0 )
        {
            printf("\nDEBUG MODE IS ON\n");
            debugMode = TRUE;
        }
    }
    
    /* set up an infinite loop */
    while (1)
    {
        /* get line of input from standard input */
        printf ("\nEnter input to check or q to quit\n");
        fgets(input, 300, stdin);
        
        /* remove the newline character from the input */
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0')
        {
            i++;
        }
        input[i] = '\0';
        
        /* check if user enter q or Q to quit program */
        if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
            break;
        
        printf ("%s\n", input);
        
        /* run the algorithm to determine is input is balanced */
        balance = 1;
        
        for ( i = 0; i < strlen(input) - 1; i++ )
        {
            /* add symbol to stack if opening symbol is found */
            if ( input[i] == '{' || input[i] == '[' || input[i] == '(' || input[i] == '<' )
            {
                push(&stack, input[i], debugMode );
            }

            /* check if input is a closing symbol */
            if ( input[i] == '}' || input[i] == ']' || input[i] == ')' || input[i] == '>' )
            {
                if ( input[i] == '}' )
                {
                    symbol = '{';
                }
                else if ( input[i] == ']' )
                {
                    symbol = '[';
                }
                else if ( input[i] == ')' )
                {
                    symbol = '(';
                }
                else if ( input[i] == '>' )
                {
                    symbol = '<';
                }
            }

            /* check if symbol is at the top of the stack */
            if ( top( &stack ) == symbol )
            {
                /* pop the top */
                pop( &stack, debugMode );
                continue;
            }

            /* if symbol is not at the top, then the stack is unbalanced */
            else if ( top( &stack ) != symbol )
            {
                /* check if the stack is empty */
                if ( empty( &stack ) == 0 )
                {
                    if ( top( &stack ) == '{' )
                    {
                        expectedSym = '}';
                    }
                    else if ( top( &stack ) == '[' )
                    {
                        expectedSym = ']';
                    }
                    else if ( top( &stack ) == '(' )
                    {
                        expectedSym = ')';
                    }
                    else if ( top( &stack ) == '<' )
                    {
                        expectedSym = '>';
                    }

                    /* print where the expected symbol should be */
                    for ( j = 0; j < i; j++ )
                    {
                        printf(" ");
                    }
                    printf("CHECK 1 ");
                    printf("^ expecting %c\n", expectedSym );
                    /* reset the balance */
                    balance = 0;
                    break;
                }

                else if ( empty( &stack ) == 1 )
                {
                    for ( j = 0; j < i; j++ )
                    {
                        printf(" ");
                    }
                    printf("CHECK 2 ");
                    printf("^ missing %c\n", symbol );
                    /* reset balance */
                    balance = 0;
                    break;
                }
            }// end of if ( top( &stack ) != symbol )

            else
            {
                if ( balance == 1 )
                {
                    /* check for balance */
                    if ( empty( &stack ) == 1 )
                    {
                        printf("CHECK 3 ");
                        printf("Expression is balanced\n");
                        continue;
                    }

                    /* check for unbalanced */
                    if ( empty( &stack ) == 0 )
                    {
                        if ( top( &stack ) == '{' )
                        {
                            symbol = '}';
                        }
                        else if ( top( &stack ) == '[' )
                        {
                            symbol = ']';
                        }
                        else if ( top( &stack ) == '(' )
                        {
                            symbol = ')';
                        }
                        else if ( top( &stack ) == '<' )
                        {
                            symbol = '>';
                        }

                        for ( j = 0; j < i; j++ )
                        {
                            printf(" ");
                        }
                        printf("CHECK 4 ");
                        printf("^ missing %c\n", symbol );
                    }
                }// checking if balance == 0
            }
        }//end of for loop

        

        /* clear the stack */
        clear( &stack );

    }//end of while
    
    printf ("\nGoodbye\n");
    return 0;
}// end of main()
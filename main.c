#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

int countLines(FILE* file)
{
    int lineCount = 0;
    int ch;
    while((ch = fgetc(file))!= EOF)
    {
        if(ch == '\n')
        {
            lineCount++;
        }
    }
    return lineCount;
}

//function that counts the number of words in a file.
int countWords(FILE* file)
{
    int wordCount = 0;
    int ch;
    int inWord = 0; //flag to trck whether currently in a word.
    while((ch = fgetc(file))!= EOF)
    {
        if(isspace(ch))
        {
            inWord = 0;
        }
        else
        {
            if(!inWord)
            {
                wordCount++;
                inWord = 1;
            }
        }
    }
    return wordCount;
}
//function ta=hat calculates the average length of words in the file.
double calculateAverageWordLength(FILE* file)
{
    int wordCount = 0;
    int totalWordLength = 0;
    int ch;
    int inWord = 0; //flag to track whether currently in word.
    while((ch = fgetc(file)) != EOF)
    {
        if(isspace(ch))
        {
            inWord = 0;
        }
        else
        {
            if(!inWord)
            {
                wordCount++;
                inWord = 1;
            }
            totalWordLength++;
        }
    }
    if(wordCount > 0)
    {
        return(double)totalWordLength / wordCount;
    }
    else
    {
        return 0.0;
    }
}

//function that calculates the frequency of a particular word in the file - allows for user input.
int countWordFrequency(FILE* file, const char* word)
{
    int frequency = 0;
    char currentWord[100];

    //convert the input word to lowercase for case-sensitive comparison
    char lowercaseWord[100];
    int i;
    for(i = 0; word[i] != '\0'; i++)
    {
        lowercaseWord[i] = tolower(word[i]);
    }
    lowercaseWord[i] = '\0';

    //scan the file for a given word
    while(fscanf(file, "%99s", currentWord) == 1)
    {
        //convert the scanned word to lower-case for case-sensitive comparison
        char lowercaseCurrentWord[100];
        for(i = 0; currentWord[i] != '\0'; i++)
        {
            lowercaseCurrentWord[i] = tolower(currentWord[i]);
        }
        lowercaseCurrentWord[i] = '\0';

        //compare the scanned word with the input word
        if (strcmp(lowercaseCurrentWord, lowercaseWord) == 0)
        {
            frequency++;
        }
    }
    return frequency;
}

int main(int argc, char* argv[])
{
    //checking if filename is provided in the arguement / eeror-checking.
    if(argc < 2)
    {
        printf("Please give the file name as the command-line argument.\n");
        printf("Example: main.c filename.txt\n");
    }

    //Open the file in read mode
    FILE* file;
    file = fopen(argv[1], "r");
    
    //check if the file is successfully opened
    if(file == NULL)
    {
        printf("Error! Failed to open file: %s\n", strerror(errno));
        return 1;
    }
    
    //Count the number of lines and words.
    int lineCount = countLines(file);
    rewind(file); //Reset the file pointer to the begining.
    int wordCount = countWords(file);
    rewind(file);
    double averageWordLength = calculateAverageWordLength(file);
    rewind(file);

    //prompt the user for a word in the file.
    char searchWord[100];
    printf("Enter a word to search: \n");
    scanf("%s", searchWord);

    //calculate the frequency of the word in the file
    int wordFrequency = countWordFrequency(file, searchWord);

    //Close the file
    fclose(file);

    //Print the line count.
    printf("TEXT DATA\n");
    printf("Number of lines in the file: %d\n", lineCount);
    printf("Number of words in the file: %d\n", wordCount);
    printf("Average word length in the file: %.2f\n", averageWordLength);
    printf("Frequncy of the word '%s' in the file: %d\n", searchWord, wordFrequency);


    return 0; //Exit the program successfully.
}
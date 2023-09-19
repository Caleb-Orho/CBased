
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

void doFrequencyAnalysis(char *, int *);
void sortFrequencyAddresses(int **, int *);
void displayFrequencyAnalysis(int **, int *);
void sort(int, int *);
void swapCipherTextChars(char *);
void printCipherText();

char cipherText[] = "LAD SJ-39 CFS EQYYT FQLPNFLZO, ZW LAFL CADW F YDLLDM RDT CFS UMDSSDV, LAD UYFZW FWV OZUADM YDLLDMS CDMD UMZWLDV PW SDUFMFLD UFUDM LFUDS, VZKZVDV ZWLP EPQM- PM EZKD-YDLLDM JMPQUS. LAD PQLUQLLDV OAFMFOLDM";

int main(void)
{
    // While loop to loop the program again.
    while (1)
    {
        // Calling the method to rpint out the Cipher Text.
        printCipherText();

        int charFreq[26] = {0};      // Used to store the occurence of each letter.
        int *alphaSort[26] = {'\0'}; // Contains the address of the most frequently element.

        // Calling required methods.
        doFrequencyAnalysis(cipherText, charFreq);
        sortFrequencyAddresses(alphaSort, charFreq);
        displayFrequencyAnalysis(alphaSort, charFreq);
        swapCipherTextChars(cipherText);
    }
}

/*
    This methos is used to print out the cipher text.
*/
void printCipherText()
{
    // Printing out the cipher text chars.
    for (int i = 0; i < strlen(cipherText); i++)
        printf("%c", *(cipherText + i));

    printf("\n\n");

    fflush(stdin);
}

/*
    This method is used to perform frequency analysis.
*/
void doFrequencyAnalysis(char *cipher_Text, int *char_Freq)
{
    // Looping through every character in the cipher text char array.
    for (int i = 0; i < strlen(cipher_Text); i++)
    {
        // Finding the position that needs to be incremented.
        int letter = (*(cipher_Text + i)) - 'A';

        // Incrementing the postion in the char frequency array.
        (*(char_Freq + letter))++;
    }
}

/*
    This code was gotten from prof. Rama Thavasinadar via lecture code walk through.
*/
typedef struct testtee
{
    int origpos;
    int freq;

} FRecord;

FRecord records[26];

/*
    This code was gotten from prof. Rama Thavasinadar via lecture code walk through.
*/
int qSort(const void *p1, const void *p2)
{
    FRecord *a = (FRecord *)p1;
    FRecord *b = (FRecord *)p2;

    return (b->freq - a->freq);
}

/*
    This method copies required information form char frequency into the array fr, and sorts the array, then copies the addressed into the alpha sort array.
*/
void sortFrequencyAddresses(int **alpha_Sort, int *char_Freq)
{
    // For loop to get the char frequency elements, and svaing it into the origpos variable.
    for (int i = 0; i < 26; i++)
    {
        (records + i)->origpos = i;
        (records + i)->freq = *(char_Freq + i);
    }

    // Using qSort to sort the fr varible elements.
    qsort(records, 26, sizeof(FRecord), qSort);

    // Copying the addresss of the sorted array element into alpha sort.
    for (int i = 0; i < 26; i++)
    {
        (*(alpha_Sort + i)) = &char_Freq[(records + i)->origpos];
    }
}

/*
    This method display the frequency analysis.
*/
void displayFrequencyAnalysis(int **alpha_Sort, int *char_Freq)
{
    // These two variables are used to format the output.
    int spAces = 0;
    char forMat;

    printf("Frequency analysis: \n");
    for (int i = 0; i < 26; i++)
    {
        // This two line of code are just used to format the Frequency analysis output.
        spAces %= 4, spAces++;
        forMat = (spAces == 4) ? '\n' : '\t';

        // Getting the character.
        int letter = ((*(alpha_Sort + i)) - char_Freq) + 'A';

        // Printing out requried information.
        printf("%c: %u %c", letter, (records + i)->freq, forMat);
    }

    printf("\n");
}

/*
    This method is used to swap two cipher chars.
    i.e Cipher text AACEBEAB; A occured 12, B occured 2.
    After this method runs B occured 12, A occured 2 and the new cipher text is BBCEAEBA.
*/
void swapCipherTextChars(char *cipher_Text)
{
    // Variables that holds the chars to be swaped.
    char sub, swap;

    // Getting the chars to swap.
    printf("Enter char to substitute: ");
    scanf(" %c", &sub);

    printf("Swap this with character: ");
    scanf(" %c", &swap);

    // Swapping the two chars.
    for (int i = 0; i < strlen(cipher_Text); i++)
        if (*(cipher_Text + i) == sub)
            *(cipher_Text + i) = swap;

        else if (*(cipher_Text + i) == swap)
            *(cipher_Text + i) = sub;
}

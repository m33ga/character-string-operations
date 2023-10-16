#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int isDuplicate(char *word, char *wordList[], int numWords, int wordOcc[]) {
    for (int i = 0; i < numWords; i++) {
        if (strcmp(word, wordList[i]) == 0) {
            wordOcc[i]++;
            return 1;
        }
    }
    return 0;
}

void eliminateDuplicates(char *sentence) {
    char *wordList[50];
    int wordOccurrences[50] = {0};
    int numWords = 0;

    char *word = strtok(sentence, " ");
    while (word != NULL) {
        if (!isDuplicate(word, wordList, numWords, wordOccurrences)) {
            wordList[numWords] = strdup(word);
            wordOccurrences[numWords]++;
            numWords++;
        }
        word = strtok(NULL, " ");
    }
    char newSentence[2500] = "";
    for (int i = 0; i < numWords; i++) {
        if (wordOccurrences[i] == 1){
            strcat(newSentence, wordList[i]);
            if (i < numWords - 1) {
                strcat(newSentence, " ");
            }
        }
    }
    strcpy(sentence, newSentence); // Copy the new sentence back to the original sentence
}

int isRotation(char *firstStr, char *secondStr){
    if (strlen(firstStr)!= strlen(secondStr)){
        return 0;
    }
    char aux[2 * strlen(firstStr) + 1];
    strcpy(aux, firstStr);
    strcat(aux, firstStr);
    if (strstr(aux, secondStr)!=NULL){
        return 1;
    }
    return 0;
}

int countPunctuationMarks(char *string){
    int counter = 0;
    for (int i = 0 ; i < strlen(string); ++i){
        switch (string[i]) {
            case '!' ... '.' :
            case ':' ... '?' : counter++; break;
        }
    }
    return counter;
}

int isPalindrome(char *string){
    char alphaNumeric[2500];
    int aNumIter = 0;
    for (int i = 0; i < strlen(string); ++i ){
        switch (string[i]) {
            case '0' ... '9': alphaNumeric[aNumIter] = string[i]; aNumIter++; break;
            case 'A' ... 'Z': alphaNumeric[aNumIter] = tolower(string[i]); aNumIter++; break;
            case 'a' ... 'z': alphaNumeric[aNumIter] = string[i]; aNumIter++; break;
        }
    }
    alphaNumeric[aNumIter] = '\0';
    if (strlen(alphaNumeric) < 2){
        return 0;
    } else {
        for (int i = 0; i < strlen(alphaNumeric)/2; i++){
            if (alphaNumeric[i] != alphaNumeric[strlen(alphaNumeric)-1-i]){
                return 0;
            }
        }
        return 1;
    }
}


int isChar(char c){
    if (((c >= 'A')&&(c <= 'Z'))||((c >= 'a')&&(c <= 'z'))){
        return 1;
    }
    return 0;
}

int isDigit(char c){
    if ((c >= '0')&&(c <= '9')){
        return 1;
    }
    return 0;
}

int isSymbol(char c){
    if ((c == '.')||(c == '_')||(c == '-')){
        return 1;
    }
    return 0;
}

int isValidEmail(char address[]){
    if (!isChar(address[0])){
        return 0;
    }
    int arond = -1;
    int lastDot = -1;
    int nrOfAronds = 0;
    for (int i = 0; i < strlen(address); ++i) {
        if (address[i] == '@'){
            arond = i;
            nrOfAronds++;
            if (nrOfAronds > 1){
                return 0;
            }
        }
        if (address[i] == '.'){
            lastDot = i;
        }
    }
   if((!isDigit(address[arond-1]))&&(!isChar(address[arond-1]))){
        return 0;
    }
    if((lastDot == strlen(address)-1)||(lastDot == strlen(address)-2)||(lastDot == arond+1)){
        return 0;
    }
    for (int i = 0; i < arond; ++i) { //check prefix Allowed characters: letters (a-z), numbers, underscores, periods, and dashes.
        //An underscore, period, or dash must be followed by one or more letter or number.
        if ((!isChar(address[i]))&&(!isDigit(address[i]))&&(!isSymbol(address[i]))){
            return 0;
        }
        if ((isSymbol(address[i]))&&(!isDigit(address[i+1]))&&(!isChar(address[i+1]))){
            return 0;
        }
    }
    for (int i = arond+1; i < lastDot; ++i) { //check valid domain
        //Allowed characters: letters, numbers, dashes.
        //The last portion of the domain must be at least two characters, for example: .com, .org, .cc
        if((!isChar(address[i]))&&(!isDigit(address[i]))&&(address[i] != '-')&&(address[i] != '.')){
            return 0;
        }
    }
    for (int i = lastDot+1; i < strlen(address) ; ++i) { //check valid top level domain
        if (isDigit(address[i])){
            return 0;
        }
    }
    return 1;
}


int compareWords(const void* word1, const void* word2){
    return strcmp(*(const char**)word1, *(const char**)word2);
}

char* sortSentence(char* sentence){
    char* copy = strdup(sentence);
    char* word;
    char* words[200];
    int nrOfWords = 0;
    char* sortedSentence = (char*)malloc(strlen(sentence)+1);
    strcpy(sortedSentence, "");

    word = strtok(copy, " "); //divide sentence into words
    while (word != NULL){
        words[nrOfWords] = strdup(word);
        word = strtok(NULL, " ");
        nrOfWords++;
    }

    qsort(words, nrOfWords, sizeof(char*), compareWords); //sort words

    for (int i = 0; i < nrOfWords; ++i) { //concatenate words into new sentence
        strcat(sortedSentence, words[i]);
        if (i < nrOfWords - 1){
            strcat(sortedSentence, " ");
        }
    }
    free(copy); // free allocated memory
    for (int i = 0; i < nrOfWords; ++i) {
        free(words[i]);
    }
    return sortedSentence;
}


int main() {
while(1){
    printf("************* Choose task *************\n");
    printf("#1: Eliminate identical words in a sentence\n");
    printf("#2: Check if second string is rotation of first string\n");
    printf("#3: Count the nr of punctuation marks in a sentence\n");
    printf("#4: Checks if a sentence is a valid palindrome when only alphanumeric characters are considered\n");
    printf("#5: Check if string is valid email address\n");
    printf("#6: Return sentence with words sorted alphabetically\n");
    printf("#7: Exit\n");
    char option;
    char string[2500];
    char string2[100];
    size_t length, length2;
    scanf("%c", &option);
    switch (option) {
        case '1':
            printf("Enter a sentence:\n");
            fflush(stdin);
            fgets(string, sizeof(string), stdin);
            length = strlen(string);
            if (length > 0 && string[length - 1] == '\n') {
                string[length - 1] = '\0';
            }
            eliminateDuplicates(string);
            printf("%s\n", string);
            break;
        case '2':
            printf("Enter first string:\n");
            scanf("%s", string);
            printf("Enter second string:\n");
            scanf("%s", string2);
            if(isRotation(string, string2)){
                printf("is rotation\n");
            } else {
                printf("no rotation\n");
            }
            break;
        case '3':
            printf("Enter a sentence:\n");
            fflush(stdin);
            fgets(string, sizeof(string), stdin);
            length = strlen(string);
            if (length > 0 && string[length - 1] == '\n') {
                string[length - 1] = '\0';
            }
            printf("Number of punctuation marks:%d \n", countPunctuationMarks(string));
            break;
        case '4':
            printf("Enter a sentence:\n");
            fflush(stdin);
            fgets(string, sizeof(string), stdin);
            length = strlen(string);
            if (length > 0 && string[length - 1] == '\n') {
                string[length - 1] = '\0';
            }
            if (isPalindrome(string)){
                printf("Valid palindrome\n");
            } else {
                printf("Invalid palindrome\n");
            }
            break;
        case '5':
            printf("Enter a email address:\n");
            fflush(stdin);
            fgets(string, sizeof(string), stdin);
            length = strlen(string);
            if (length > 0 && string[length - 1] == '\n') {
                string[length - 1] = '\0';
            }
            if (isValidEmail(string)){
                printf("Valid email address\n");
            } else {
                printf("Invalid email address\n");
            }
            break;
        case '6':
            printf("Enter a sentence:\n");
            fflush(stdin);
            fgets(string, sizeof(string), stdin);
            length = strlen(string);
            if (length > 0 && string[length - 1] == '\n') {
                string[length - 1] = '\0';
            }
            printf("%s \n", sortSentence(string));
            break;
        default:
            return 0;

        }
    }
}

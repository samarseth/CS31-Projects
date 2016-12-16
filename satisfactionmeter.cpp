#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <cassert>

using namespace std;

const int MAX_WORD_LENGTH = 20;


int normalizeRules(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int distance[], int nRules);
int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int distance[], int nRules, const char document[]);

int main()
{
    const int TEST2_NRULES = 4;
    char test2w1[TEST2_NRULES][MAX_WORD_LENGTH+1] = {
        "when",       "we", "cerr", "be"
    };
    char test2w2[TEST2_NRULES][MAX_WORD_LENGTH+1] = {
        "we", "discarded",    "writt",      "to"
    };
    int test2dist[TEST2_NRULES] = {
        1,           9,         3,           1
    };
    
    assert(normalizeRules(test2w1, test2w2, test2dist, TEST2_NRULES)==4);
    
    assert(calculateSatisfaction(test2w1, test2w2, test2dist, TEST2_NRULES,
                                 "When we program, we will cause anything written to cerr to be discarded") == 2);
    
    assert(calculateSatisfaction(test2w1, test2w2, test2dist, TEST2_NRULES,
                                 "When we program, we will cause anything writt to cerr to be discarded") == 3);
    
    assert(calculateSatisfaction(test2w1, test2w2, test2dist, TEST2_NRULES,
                                 "When we program, we will cause anything written to cerr to discard") == 1);
    
    assert(calculateSatisfaction(test2w1, test2w2, test2dist, TEST2_NRULES,
                                 "When were program, we will cause anything written to cerr to be discarded") == 2);
    
    assert(calculateSatisfaction(test2w1, test2w2, test2dist, TEST2_NRULES,
                                 "") == 0);
}

int normalizeRules(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int distance[], int nRules)
{
    if (nRules <= 0) // accounts for the trivial case when nRules is either negative ro equal to zero
        return 0;
    int samar = nRules; // creates a variable that changes as anomalies are found in the code
    for (int i = 0; i < samar; i++)
    {
        
        bool counter = 0; // set a bool variable equal to false
        
        for (int j = 0 ; word1[i][j]!= '\0' ; j++)
        {
            if (!isalpha(word1[i][j]))
            {
                counter = 1; // sets the bool variable to 1 if such an anomaly is found in the code
                break;
            }
        }
        for (int j = 0 ; word2[i][j] != '\0'; j++)
        {
            if (!isalpha(word2[i][j])) // the if statement will only execute when word[i][j] is not an alphabet
            {
                counter = 1;
                break;
            }
        }
        
        if (distance[i] <= 0) // checks whether the ith distance is negative
        {
            counter = 1;
            
        }
        
        for (int j = 0 ; word1[i][j] != '\0'; j++)
        { 
            word1[i][j] = tolower(word1[i][j]);// converts all the alphabets to lowercase letters in w1
        }
        for (int j = 0 ; word2[i][j] != '\0'; j++)
        { 
            word2[i][j] = tolower(word2[i][j]); // converts all the alphabets to lowercase letters in w2
        }
        for (int k = 0; k < samar; k++)
        {
            if (i!=k) // makes sure the same element of the array is not compared to inself
            {    
                if (strcmp(word1[i], word1[k]) == 0 && strcmp(word2[i], word2[k]) == 0)
                {
                    counter = 1;
                    
                }
                if (strcmp(word1[i], word2[k]) == 0 && strcmp(word2[i], word1[k]) == 0)
                {
                    counter = 1;
                }
            }
        }
        if (counter)
        {  
            samar = samar - 1;
            for (int x = i; x<samar; x++)
            {
                strcpy(word1[x], word1[x+1]); // removes the xth element of word1
                strcpy(word2[x], word2[x+1]);// removes the xth element of word2
                distance[x] = distance[x+1];// removes the xth element of distance
                
            }
            i--;
        }
        for (int j = 0; j < samar; j++)
        {
            if (i != j)
            {
                if (strcmp(word1[i], word1[j]) == 0 && strcmp(word2[i], word2[j]) == 0) // compares word1[i] & word1[j] and word2[i] & word2[j]
                {
                    if (distance[i] < distance[j])
                    {
                        samar = samar - 1;
                        for (int x = i; x<samar; x++)
                        {
                            strcpy(word1[x], word1[x+1]); // copies word1[x+1] to word1[x]
                            strcpy(word2[x], word2[x+1]); // copies word2[x+1] to word2[x]
                            distance[x] = distance[x+1]; // copies distance[x+1] to distance[x]
                            
                        }
                        i--;
                    }
                    else
                    {
                        samar = samar - 1;
                        for (int x = j; x<samar; x++)
                        {
                            strcpy(word1[x], word1[x+1]);
                            strcpy(word2[x], word2[x+1]);
                            distance[x] = distance[x+1];
                        }
                        i--;
                    }
                }
            }
        }        
    }
    return samar; // returns the required output (avoiding the funciton to reach a void situation)
}


int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int distance[], int nRules, const char document[])
{
    
    char temp[201]; // created a new character string temp of 201  
    
    
    int k = 0;
    for (int i = 0; i < strlen(document); i++)
    {
        
        if (isalpha(document[i]) || document[i] == ' ')  
        {
            temp[k] = document[i];
            k++;
        }
    }
    
    temp[k] = '\0';
    
    
    char temp2[201]; // defines a new character string called temp2
    int c = 0;
    char prev = 'a';
    for (int w = 0; w < strlen(temp); w++)
    {
        if (temp[w] == ' ')
        {
            if(prev == ' ') continue;
            prev = ' ';
            temp2[c] = temp[w];
            c++;
        }
        else {
            prev = 'a';
            temp2[c] = temp[w];
            c++;
        }
    }
    temp2[c] = '\0';
    
    for (int  i = 0; i < c; i++)
    {
        if(isalpha(temp2[i])) temp2[i] = tolower(temp2[i]);
    }
    
    char newSet[201][201];
    int i = 0; int o = 0, j = 0;;
    while(temp2[i] != '\0')
    {
        if(temp2[i] == ' ') 
        {
            newSet[o][j] = '\0'; // assigns the null terminator to newSet[o][j]
            
            o++; j = 0;
        }
        else 
        {
            newSet[o][j] = temp2[i];
            
            j++; // increments the value of j
        }
        i++; 
    }
    
    newSet[o][j] = '\0';
    
    //o is the number of words
    int counting= 0; // initialize counting to zero
    for (int s = 0; s < nRules; s++)  
    {
        for (int t = 0; t <=o; t++) 
        {
            if (strcmp(word1[s], newSet[t]) == 0) // bool statement to find whether the two elements of their respective elements are negative or not
            {
                for (int z = 0; z <=o; z++)
                {
                    if(z==t) continue;
                    if (strcmp(word2[s], newSet[z]) == 0)
                    {                    int cool;
                        if ((z-t) <0)
                        {
                            cool = t-z; // negates the previously negative value of 'cool' to make it positive
                        }
                        else
                        {
                            cool = z-t; // leaves the positive value as it is
                        }
                        if (cool<=distance[s])
                        {    
                            counting++;
                            break;
                        }
                    }
                }  
                break;  
            }
        }
    }
    return counting; // returns counting, the satisfaction score 
}



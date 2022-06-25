#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;


bool guessInList(string guess, string arr[], int num_words)
{
    int i;
    for(i = 0; i < num_words; i++)
    {
        if(arr[i] == guess)
        {
            cout << "The word '" << arr[i] << "' exists!" << endl;
            return true;
        }
    }
    return false;
}
void compareWords(char guess_arr[], char answer_arr[], int score[])
{
    for(int i = 0; i < 5; i++)
    {
        bool isScored = false;
        for(int j = 0; j <5; j++)
            if(guess_arr[i] == answer_arr[j])
            {
                if(i == j)
                {
                    score[i] = 2;
                    isScored = true;
                }
                else
                {
                    if(!isScored)
                    {
                        score[i] = 1;
                        isScored = true;
                    }
                }
            }
        if(isScored == false)
        {
            score[i] = 0;
        }
    }
}
void cleanChArray(char guess_array[], int score[], char remainingChArray[], char newChArray[], int remaining_count, int& added_counter, int num_attempts)
{
    added_counter = 0;
    for(int i = 0; i < remaining_count; i+=5)
    {
        bool keep_word = true;
        for(int j = 0; j < 5; j++)
        {
            char guess_ch = guess_array[j];
            int score_j = score[j];
            if(score_j == 0)
            {
                for(int k = 0; k < 5; k++)
                {
                    if(guess_ch == remainingChArray[i+k])
                    {
                        for(int e = 0; e < 5; e++)
                        {
                            if(guess_array[e] == remainingChArray[i+k] && e != k && score[e] != 0)
                            {
                                keep_word = true;
                                break;
                            }
                            else
                            {
                                keep_word = false;
                                break;
                            }
                        }
                    }
                }
            }
            else if(score_j == 2)
            {
                if(!(guess_ch == remainingChArray[i+j]))
                {
                    keep_word = false;
                    break;
                }
            }
            else if(score_j == 1)
            {
                int found = 0;
                for(int l = 0; l < 5; l++)
                {
                    if(guess_ch == remainingChArray[i+l] && j == l)
                    {
                        keep_word = false;
                        break;
                    }
                    else if(guess_ch == remainingChArray[i+l] && j!=l)
                    {
                        found += 1;
                    }
                }
                if(found != 1)
                {
                    keep_word = false;
                }
            }
            if(!keep_word)
            {
                break;
            }
        }
        if(keep_word)
        {
            for(int k = i; k < i+5; k++)
            {
                newChArray[added_counter] = remainingChArray[k];
                added_counter++;
            }
        }
    }
}
int numberEliminated(char guess_arr[], char keyword_arr[], int score[], char remainingChArray[], char newChArray[], int remainingCount, int& added_counter, int num_attempts)
{
    compareWords(guess_arr, keyword_arr, score);
    cleanChArray(guess_arr, score, remainingChArray, newChArray, remainingCount, added_counter, num_attempts);
    return(2309 - (added_counter)/5);
}
int averageEliminated(char guess_arr[], char remainingChArray[], int score[], char newChArray[], int remainingCount, int& added_counter, int num_attempts)
{
    int num_elim = 0;
    int current_length = added_counter;
    for(int i = 0; i < remainingCount; i += 5)
    {
        char * keyword_array = new char[5];
        for(int j = 0; j < 5; j++)
        {
            keyword_array[j] = remainingChArray[i+j];
        }
        num_elim += numberEliminated(guess_arr, keyword_array, score, remainingChArray, newChArray, remainingCount, added_counter, num_attempts);
    }
    return num_elim/2309;
}

void makeGuess(char remainingChArray[], int score[], char newChArray[], int& remainingCount, int& added_counter, char final_guess[], int& num_attempts)
{
    printf("%i, %i, %i\n", remainingCount, added_counter, num_attempts);
    char * guess = new char[5];
    int guess_avg = 0;
    char * best = new char[5];
    int best_avg = 0;
    for(int i = 0; i < remainingCount/5; i ++)
    {
        for(int j = 0; j < 5; j++)
        {
            guess[j] = remainingChArray[(5*i)+j];
        }
        guess_avg = averageEliminated(guess, remainingChArray, score, newChArray, remainingCount, added_counter, num_attempts);
        if(guess_avg > best_avg)
        {
            for(int i = 0; i < 5; i++)
            {
                best[i] = guess[i];
            }
            best_avg = guess_avg;
        }
    }
    for(int i = 0; i < 5; i++)
    {
        final_guess[i] = best[i];
        printf("%c", final_guess[i]);
    }
    printf(": %i\n", best_avg);
    num_attempts++;
    

}


int main()
{
    const int num_words = 2309;
    string * ANSWERLIST = new string[num_words];
    char * chArray = new char[11545*2];
    char * officialGuess = new char[5];
    char * officialAnswer = new char[5];
    int count = 0;
    int attempts = 0;
    int * score_template = new int[5];
    int numberOfWords;
    int addCount = 0;
    bool match = false;
    ifstream inputFile;
    inputFile.open("ANSWERS.txt");
    if(!inputFile)
    {
        cout << "Error finding input file" << endl;
        exit(-1);
    }
    while(!inputFile.eof())
    {
        inputFile >> ANSWERLIST[count];
        count++;
    }
    numberOfWords = count;
    int ch_count = 11545;
    int smaller_count = 1150;
    char * chAnswerList = new char[ch_count];
    char * smallerList = new char[smaller_count];
    for(int i = 0; i < 2309; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            chAnswerList[(5*i)+j] = ANSWERLIST[i][j];
        }
    }

    for(int i = 0; i < 230; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            smallerList[(i*5)+j] = ANSWERLIST[i][j];
        }
    }



    officialAnswer[0] = 'b';
    officialAnswer[1] = 'r';
    officialAnswer[2] = 'o';
    officialAnswer[3] = 'o';
    officialAnswer[4] = 'k';
    
    for(int i = 0; i < 3; i++)
    {
        match = true;
        makeGuess(smallerList, score_template, chArray, smaller_count, addCount, officialGuess, attempts);
        compareWords(officialGuess, officialAnswer, score_template);
        for(int j = 0; j < 5; j++)
        {
            if(score_template[j] != 2)
            {
                match = false;
                break;
            }
            
        }
        for(int j = 0; j < 5; j++)
        {
            printf("%i ", score_template[j]);
        }
        printf("\n");
        if(match)
        {
            printf("%c\n", i);
            return i;
        }
        for(int l = 0; l < 5; l++)
        {
            printf("%c", officialGuess[l]);
        }
        printf("\n");
        printf("%i\n", addCount);
        printf("\n");
        cleanChArray(officialGuess, score_template, smallerList, chArray, smaller_count, addCount, attempts);
        printf("%i\n", addCount);
        for(int k = 0; k < addCount; k++)
        {
            smallerList[k] = chArray[k];
            printf("%c", smallerList[k]);
        }
        printf("\n");
        
    }
}


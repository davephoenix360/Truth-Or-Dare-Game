// Truth or Dare Game with C++ 
// First Version

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>

using namespace std;
int Whowon(int scores[], int nop, int limiter);
void Gameplay(int scores[], int nop, int& turn, vector<string> truths, vector<string> dares, int& counter_d, int& counter_t);
string GetTruth(vector<string> truths, int counter_t);
string GetDare(vector<string> dares, int counter_d);

int main()
{
    
    ifstream inDare;
    ifstream inTruth;

    inDare.open("darequestions.txt");
    inTruth.open("truthquestions.txt");

    // Store the truth questions
    vector<string> truths;
    string questiond;
    getline(inTruth, questiond);
    while (getline(inTruth, questiond))
    {
        truths.push_back(questiond);
    }
    int counter_t = rand() % truths.size(); // A counter to know the last truth asked

    // Store the dare questions
    vector<string> dares;
    string question;
    getline(inDare, question);
    while (getline(inDare, question))
    {
        dares.push_back(question);
    }
    int counter_d = rand() % dares.size(); // A counter to know the last dare asked

    int nop; // Number of players
    cout << "/************* WELCOME TO TRUTH OR DARE *************/" << endl;
    cout<<endl;
    cout<<endl;
    cout << right;
    cout << "This is your classic truth of dare game." << endl;
    cout << "When a player completes either a truth or a dare, they" << endl;
    cout << "are awarded one point (no matter how hard it is) and  " << endl;
    cout << "zero points if not completed." << endl;

    cout << "Enter number of players (maximum of 10): ";
    cin >> nop; // Number of players
    cout<<endl;

    string players_names[nop];
    int scores[nop], limiter, turn=0;

    for ( int i = 0; i < nop; i++) // Initialize each player's score to zero.
    {
        scores[i] = 0;
    }

    cout << setw(48) << "/********** ENTER YOUR NAMES **********/" << endl;
    
    for ( int i = 0; i < nop; i++)
    {
        cout << "Player " << i+1 << ":";
        string name;
        cin >> players_names[i];
    }
    cout << "First to how many points wins:";
    cin >> limiter;
    cout << "Are you ready to play? (Y/N)" << endl;
    char state;
    cin >> state;
    if(state == 'Y' || state == 'y')
    {
        while (Whowon(scores, nop, limiter) == 0)
        {
            for(int i=0; i < nop; i++)
            {
                Gameplay(scores, nop, turn, truths, dares, counter_d, counter_t);
            }
        }
        int winner = Whowon(scores, nop, limiter);
        cout << "Player " << winner << "(" << players_names[winner-1] << ") won" << endl;
        cout << "Game Over.";
        inDare.close();
        inTruth.close(); 
        return 0;
        
    }
    else
    {
        cout << "Okay, restart the game when ready" ;
        inDare.close();
        inTruth.close();
        return 0;
    }

}

int Whowon(int scores[], int nop, int limiter)
{
    for (int i = 0; i < nop; i++)
    {
        if (scores[i] == limiter)
        {
            return i+1;
        }
    }
    return 0;
    
}

void Gameplay(int scores[], int nop, int& turn, vector<string> truths, vector<string> dares, int& counter_d, int& counter_t)
{
    cout << "\nPlayer " << turn + 1 << "\'s turn" << endl;
    cout << "Truth or Dare(T or D)? ";

    char choice;
    cin >> choice;
    
    if(choice == 'T' || choice == 't')
    {
        cout << endl;
        cout << GetTruth(truths, counter_t) << endl;
        cout << "You know the rules :)" << endl;
        cout << "Did player " << turn + 1 << " answer the question? (Y/N)" << endl;
        char answer;
        cin >> answer;
        if(answer == 'Y' || answer == 'y')
        {
            scores[turn]++;   
        }
        cout << "Okay" << endl;
        counter_t = rand() % truths.size();
    }
    if(choice == 'D' || choice == 'd')
    {
        cout << endl;
        cout << GetDare(dares, counter_d) << endl;
        cout << endl;
        cout << "You know the rules :)" << endl;
        cout << endl;
        cout << "Did Player " << turn + 1 << " agree to do the dare? (Y/N)" << endl;
        char answer;
        cin >> answer;
        if(answer == 'Y' || answer == 'y')
        {
            scores[turn]++;   
        }
        cout << "Okay" << endl;
        counter_d = rand() % dares.size();
    }
    turn = (turn+1) % nop;
}

string GetTruth(vector<string> truths, int counter_t)
{
    return truths[counter_t];
}

string GetDare(vector<string> dares, int counter_d)
{
    return dares[counter_d];
}

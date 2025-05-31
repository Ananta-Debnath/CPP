#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> // for file handling

using namespace std;

//**************** ****************************************************************** **********************/
//**************** 'Cricketer' class represents a general cricketer. Do not change!!! **********************/
//****************   You can not add any other properties or methods in any classes   **********************/
//**************** ****************************************************************** **********************/
class Cricketer
{
protected:
    int matchPlayed;
    string name;
    int age;

public:
    // constructor to initialize name, age, and matches played
    Cricketer(string s = "Unknown", int a = 0, int m = 0) : name(s), age(a), matchPlayed(m) {}

    string getName() { return name; }
    int getMatchPlayed() { return matchPlayed; }
    int getAge() { return age; }
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setMatchPlayed(int m) { matchPlayed = m; }

    // Prints basic cricketer info
    virtual void printInfo(ofstream &out)
    {
        out << "Name: " << name << ", Age: " << age << ", Matches Played: " << matchPlayed << endl;
    }

    virtual ~Cricketer() {}
};

//**************** ****************************************************************** **********************/
//**************** ****************************************************************** **********************/

// 'Batsman' class represents a batsman
// Inherit 'Cricketer' class to implement 'Batsman'
class Batsman : virtual public Cricketer
{
protected:
    int runScored;
    int ballsFaced;

public:
    // Implement Constructor to initialize batting details along with cricketer data
    // Take Name, Age, Matches played, Runs, Balls
    Batsman(string s = "Unknown", int a = 0, int m = 0, int run = 0, int balls = 0) : Cricketer(s, a, m)
    {
        runScored = run;
        ballsFaced = balls;
    }

    // Compute batting average: runs/matches
    double computeBattingAverage()
    {
        return (double)runScored / matchPlayed;
    }

    // Compute strike rate: (runs/balls faced) * 100
    double computeStrikeRate()
    {
        return ((double)runScored / ballsFaced) * 100;
    }

    // Getter & Setter for total runs
    int getRunScored() { return runScored; }

    void setRunScored(int run)
    {
        if (run >= 0) runScored = run;
    }
    // Getter & Setter for balls faced
    int getBallsFaced() { return ballsFaced; }

    void setBallsFaced(int balls)
    {
        if (balls >= 0) ballsFaced = balls;
    }

    // Print batsman-specific stats; you have to use the base class's method here.
    void printInfo(ofstream &out)
    {
        out << "---- Batsman Info ----" << endl;
        Cricketer::printInfo(out);
        out << "---- Batting Stats ----" << endl;
        out << "Runs Scored: " << runScored << ", Balls Faced: " << ballsFaced << endl;
        out << "Batting Average: " << fixed << setprecision(2) << computeBattingAverage() << ", Strike Rate: " << fixed << setprecision(2) << computeStrikeRate() << endl;
    }
};

// 'Bowler' class represents a bowler
// Inherit 'Cricketer' class to implement 'Bowler'
class Bowler : virtual public Cricketer
{
protected:
    int wicketsTaken;
    int runsConceded;
    double oversBowled;

public:
    // Implement Constructor to initialize bowling details along with cricketer data
    // Take Name, Age, Matches played, Wickets, RunsConceded, Overs
    Bowler(string s = "Unknown", int a = 0, int m = 0, int wickets = 0, int run = 0, double overs = 0) : Cricketer(s, a, m)
    {
        wicketsTaken = wickets;
        runsConceded = run;
        oversBowled = overs;
    }

    // Compute average wickets per match
    double computeWicketAverage()
    {
        return (double)wicketsTaken / matchPlayed;
    }

    // Compute economy rate: runs conceded per over
    double computeEconomy()
    {
        return runsConceded / oversBowled;
    }

    // Getter & Setter for wickets
    int getWicketsTaken() { return wicketsTaken; }

    void setWicketsTaken(int wickets)
    {
        if (wickets >= 0) wicketsTaken = wickets;
    }

    // Getter & Setter for runs conceded
    int getRunsConceded() { return runsConceded; }

    void setRunsConceded(int run)
    {
        if (run >= 0) runsConceded = run;
    }

    // Getter & Setter for overs bowled
    int getOversBowled() { return oversBowled; }

    void setOversBowled(double overs)
    {
        if (overs >= 0) oversBowled = overs;
    }

    // Print bowler-specific stats; you have to use the base class's method here.
    void printInfo(ofstream &out)
    {
        out << "---- Bowler Info ----" << endl;
        Cricketer::printInfo(out);
        out << "---- Bowling Stats ----" << endl;
        out << "Wickets Taken: " << wicketsTaken << ", Runs Conceded: " << runsConceded << ", Overs Bowled: " << oversBowled << endl;
        out << "Wicket Average: " << fixed << setprecision(2) << computeWicketAverage() << ", Economy: " << fixed << setprecision(2) << computeEconomy() << endl;
    }
};

// The following class represents an allrounder (inherits from both Batsman and Bowler)
class Allrounder : public Batsman, public Bowler
{
public:
    // Implement Constructor to initialize all data for an allrounder (batsman and bowler)
    Allrounder(string s = "Unknown", int a = 0, int m = 0, int run = 0, int balls = 0, int wickets = 0, int runsConceded = 0, double overs = 0) : Cricketer(s, a, m), Batsman(s, a, m, run, balls), Bowler(s, a, m, wickets, runsConceded, overs){}

    // Print both batting and bowling statistics; you have to use the base class's method here.
    void printInfo(ofstream &out) override
    {
        out << "---- Allrounder Info ----" << endl;
        Cricketer::printInfo(out);

        out << "---- Batting Stats ----" << endl;
        out << "Runs Scored: " << runScored << ", Balls Faced: " << ballsFaced << endl;
        out << "Batting Average: " << fixed << setprecision(2) << computeBattingAverage() << ", Strike Rate: " << fixed << setprecision(2) << computeStrikeRate() << endl;
        
        out << "---- Bowling Stats ----" << endl;
        out << "Wickets Taken: " << wicketsTaken << ", Runs Conceded: " << runsConceded << ", Overs Bowled: " << oversBowled << endl;
        out << "Wicket Average: " << fixed << setprecision(2) << computeWicketAverage() << ", Economy: " << fixed << setprecision(2) << computeEconomy() << endl;

    }
};

// input file style
// TYPE Name Age Matches Runs Balls Wickets RunsConceded Overs

int main()
{
    // You have to take input from "input1.txt" and you have to generate an "output.txt" file like "Demo_output.txt"
    // First take the players information from "input.txt" and create necessary player objects
    // Then save them in an array of players
    // Finally, show the players' information
    // NOTE: Players can be of any type

    ifstream in("input1.txt"); // or use cin if from console
    Cricketer** players = new Cricketer*[10];
    int playerCount = 0;

    string type;
    while (in >> type) {
        string name;
        int age, matches;
        in >> name >> age >> matches;

        if (type == "Batsman") {
            int runs, balls;
            in >> runs >> balls;
            players[playerCount++] = new Batsman(name, age, matches, runs, balls);
        }
        else if (type == "Bowler") {
            int wickets, conceded;
            double overs;
            in >> wickets >> conceded >> overs;
            players[playerCount++] = new Bowler(name, age, matches, wickets, conceded, overs);
        }
        else if (type == "Allrounder") {
            int runs, balls, wickets, conceded;
            double overs;
            in >> runs >> balls >> wickets >> conceded >> overs;
            players[playerCount++] = new Allrounder(name, age, matches, runs, balls, wickets, conceded, overs);
        }
    }

    // Optional: Print all player info to file or console
    ofstream out("output.txt");
    for (size_t i = 0; i < playerCount; ++i) {
        out << "=== Player " << (i + 1) << " ===" << endl;
        players[i]->printInfo(out);
        out << endl;
    }

    // Cleanup
    for (int i = 0; i < 10; i++) {
        delete players[i];
    }
    delete[] players;
    return 0;
}

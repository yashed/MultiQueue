#include <iostream>
#include <queue>
#include <sstream>
#include <algorithm>

using namespace std;

// Time Quantum of RR schedualing
#define timeQ 5

// multilevel queue schedualing function

void RRSche();
void SJFSche1();
void SJFSche2();
void FIFOSche();

// To calculate globale time
int Otime = 0;

// Calculate Total Witing Time and Total Turn Arround Time
float totalWaitingTime = 0, totalTurnAroundTime = 0;

// typecast int to string
string TC(int i)
{
    stringstream ss;
    ss << i;
    string s;
    ss >> s;
    return s;
}

// Process class
class Prosess
{
public:
    int burstTime, TurnArroudT, WaitingT, AdWaitingT;
    string pid;

    Prosess()
    {
        TurnArroudT = 0, WaitingT = 0, AdWaitingT = 0;
    }
};

// initialize 4 queues
queue<Prosess> q0, q1, q2, q3;

// This function is use to sort prosessers in SJF schedualing
bool compareByBurstTime(const Prosess &p1, const Prosess &p2)
{
    return p1.burstTime < p2.burstTime;
}

int main()
{
    // getting input from user
    int q0Num, q1Num, q2Num, q3Num;

    cout << "\nEnter Number of Prosessers in Queue 0 :";
    cin >> q0Num;

    Prosess *q0Prosesses = new Prosess[q0Num];

    // Getting prossesers in q0 with burst time
    for (int j = 0; j < q0Num; j++)
    {
        // Add pID
        string n = "q0_p";
        q0Prosesses[j].pid = n + TC(j);
        cout << "Enter the Burst time of Prosess " << j + 1 << " :";
        cin >> q0Prosesses[j].burstTime;

        // add these prosess to Queue (RR)
        q0.push(q0Prosesses[j]);
    }

    cout << "\nEnter Number of Prosessers in Queue 1 :";
    cin >> q1Num;

    Prosess *q1Prosesses = new Prosess[q1Num];

    // Getting prossesers in q1 with burst time
    for (int j = 0; j < q1Num; j++)
    {
        // Add pID
        string n = "q1_p";
        q1Prosesses[j].pid = n + TC(j);

        cout << "Enter the Burst time of Prosess " << j + 1 << " :";
        cin >> q1Prosesses[j].burstTime;
    }

    cout << "\nEnter Number of Prosessers in Queue 2 :";
    cin >> q2Num;

    Prosess *q2Prosesses = new Prosess[q2Num];

    // Getting prossesers in q2 with burst time
    for (int j = 0; j < q2Num; j++)
    {
        // Add pID
        string n = "q2_p";
        q2Prosesses[j].pid = n + TC(j);

        cout << "Enter the Burst time of Prosess " << j + 1 << " :";
        cin >> q2Prosesses[j].burstTime;
    }

    cout << "\nEnter Number of Prosessers in Queue 3 :";
    cin >> q3Num;

    Prosess *q3Prosesses = new Prosess[q3Num];

    // Getting prossesers in q3 with burst time
    for (int j = 0; j < q3Num; j++)
    {
        // Add pID
        string n = "q3_p";
        q3Prosesses[j].pid = n + TC(j);

        cout << "Enter the Burst time of Prosess " << j + 1 << " :";
        cin >> q3Prosesses[j].burstTime;

        // add these prosess to Queue (FIFO)
        q3.push(q3Prosesses[j]);
    }

    // sort q1Prosesses and  q2Prosesses
    sort(q1Prosesses, q1Prosesses + q1Num, compareByBurstTime);
    sort(q2Prosesses, q2Prosesses + q2Num, compareByBurstTime);

    // add sorted processers to queues
    for (int k = 0; k < q1Num; k++)
        q1.push(q1Prosesses[k]);

    for (int k = 0; k < q2Num; k++)
        q2.push(q2Prosesses[k]);

    // Run Schedualing Funcrions and print output
    cout << "\n\nP_ID\t\t"
         << "Waiting_Time\t\t"
         << "TurnAround_Time\n"
         << endl;

    // Running schedualing functions
    while (!q0.empty() || !q1.empty() || !q2.empty() || !q3.empty())
    {
        RRSche();
        cout << "\n";
        SJFSche1();
        cout << "\n";
        SJFSche2();
        cout << "\n";
        FIFOSche();
        cout << "\n";
    }

    // Calculate Average WT and TAT and Display
    int totalPro = q0Num + q1Num + q2Num + q3Num;
    float avgWT = totalWaitingTime / totalPro;
    float avgTT = totalTurnAroundTime / totalPro;

    cout << "Average Waiting Time : " << avgWT << endl;
    cout << "Average Turn Time    : " << avgTT << endl;
}

void RRSche()
{

    int q0time = 0;
    int wait1 = Otime;

    // Running prosess in q0 by RR schedualing
    while (!q0.empty())
    {
        wait1 = q0time + Otime;
        // check burstTime <= time Quntom
        if (q0.front().burstTime <= timeQ)
        {

            q0time += q0.front().burstTime;

            // Check total time > 20
            if (q0time >= 20)
            {
                // add waiting time and turnAround time and prit it, then pop from queue
                if (q0time == 20)
                {
                    q0.front().WaitingT = wait1 - (q0.front().AdWaitingT);
                    totalWaitingTime += q0.front().WaitingT;

                    q0.front().TurnArroudT = q0time;
                    totalTurnAroundTime += q0.front().TurnArroudT;

                    cout << q0.front().pid << "\t\t" << q0.front().WaitingT << "\t\t\t  " << q0.front().TurnArroudT << endl;
                    q0.pop();
                    break;
                }
                // update burst time
                else
                {
                    q0.front().burstTime = q0time - 20;
                    break;
                }
            }
            // add waiting time and turnAround time and prit it, then pop from queue
            else
            {
                q0.front().WaitingT = wait1 - (q0.front().AdWaitingT);
                totalWaitingTime += q0.front().WaitingT;

                q0.front().TurnArroudT = q0time;
                totalTurnAroundTime += q0.front().TurnArroudT;

                cout << q0.front().pid << "\t\t" << q0.front().WaitingT << "\t\t\t  " << q0.front().TurnArroudT << endl;
                q0.pop();
            }
        }

        // if burst time > time Quantum of RR schedualing
        else
        {
            q0time = q0time + timeQ;
            q0.front().AdWaitingT += timeQ;

            if (q0time >= 20)
            {
                if (q0time == 20)
                {
                    q0.front().WaitingT = wait1;
                    q0.front().burstTime = (q0.front().burstTime) - timeQ;
                    Prosess temp = q0.front();
                    q0.push(temp);
                    q0.pop();
                    break;
                }
                else
                {
                    q0.front().WaitingT = wait1;
                    q0.front().burstTime = (q0.front().burstTime) - timeQ + (q0time - 20);
                    Prosess temp = q0.front();
                    q0.push(temp);
                    q0.pop();
                    break;
                }
            }
            else
            {
                q0.front().WaitingT = wait1;
                q0.front().burstTime = (q0.front().burstTime) - (timeQ);
                Prosess temp = q0.front();
                q0.push(temp);
                q0.pop();
            }
        }
    }

    // To get total time
    if (q0time < 20)
    {
        Otime += q0time;
    }
    else
    {
        Otime += 20;
    }
    return;
}

void SJFSche1()
{
    int q1time = 0;
    int wait2 = Otime;

    // Running prosess in q1 by SJF schedualing
    while (!q1.empty())
    {
        wait2 = Otime + q1time;

        // assign total time of queue1
        q1time += q1.front().burstTime;

        // check q1time >=20
        if (q1time >= 20)
        {

            if (q1time == 20)
            {
                q1.front().WaitingT = wait2 - (q1.front().AdWaitingT);
                totalWaitingTime += q1.front().WaitingT;

                q1.front().TurnArroudT = Otime + q1time;
                totalTurnAroundTime += q1.front().TurnArroudT;

                cout << q1.front().pid << "\t\t" << q1.front().WaitingT << "\t\t\t  " << q1.front().TurnArroudT << endl;
                // wt2 = q1.front().burstTime + q1.front().WaitingT;
                q1.pop();
                break;
            }
            else
            {
                q1.front().AdWaitingT += (q1.front().burstTime) - (q1time - 20);
                q1.front().burstTime = q1time - 20;
                break;
            }
        }
        else
        {
            q1.front().WaitingT = wait2 - (q1.front().AdWaitingT);
            totalWaitingTime += q1.front().WaitingT;

            q1.front().TurnArroudT = Otime + q1time;
            totalTurnAroundTime += q1.front().TurnArroudT;

            cout << q1.front().pid << "\t\t" << q1.front().WaitingT << "\t\t\t  " << q1.front().TurnArroudT << endl;
            q1.pop();
        }
    }

    // To get total time
    if (q1time < 20)
    {
        Otime += q1time;
    }
    else
    {
        Otime += 20;
    }

    return;
}

void SJFSche2()
{
    int q2time = 0;
    int wait3 = Otime;

    // Running prosess in q2 by SJF schedualing
    while (!q2.empty())
    {
        wait3 = Otime + q2time;

        // assign total time of queue2
        q2time += q2.front().burstTime;

        // check q2time>=20
        if (q2time >= 20)
        {
            if (q2time == 20)
            {
                q2.front().WaitingT = wait3 - (q2.front().AdWaitingT);
                totalWaitingTime += q2.front().WaitingT;

                q2.front().TurnArroudT = Otime + q2time;
                totalTurnAroundTime += q2.front().TurnArroudT;

                cout << q2.front().pid << "\t\t" << q2.front().WaitingT << "\t\t\t  " << q2.front().TurnArroudT << endl;
                q2.pop();
                break;
            }
            else
            {
                q2.front().AdWaitingT += (q2.front().burstTime) - (q2time - 20);
                q2.front().burstTime = q2time - 20;
                break;
            }
        }
        else
        {
            q2.front().WaitingT = wait3 - (q2.front().AdWaitingT);
            totalWaitingTime += q2.front().WaitingT;

            q2.front().TurnArroudT = Otime + q2time;
            totalTurnAroundTime += q2.front().TurnArroudT;

            cout << q2.front().pid << "\t\t" << q2.front().WaitingT << "\t\t\t  " << q2.front().TurnArroudT << endl;
            q2.pop();
        }
    }

    // To get total time
    if (q2time < 20)
    {
        Otime += q2time;
    }
    else
    {
        Otime += 20;
    }

    return;
}

void FIFOSche()
{
    int q3time = 0;
    int wait4 = Otime;

    // Running prosess in q3 by FIFO schedualing
    while (!q3.empty())
    {
        wait4 = Otime + q3time;
        // assign total time of queue 3
        q3time += q3.front().burstTime;

        // check q3time>=20
        if (q3time >= 20)
        {
            if (q3time == 20)
            {
                q3.front().WaitingT = wait4 - (q3.front().AdWaitingT);
                totalWaitingTime += q3.front().WaitingT;

                q3.front().TurnArroudT = Otime + q3time;
                totalTurnAroundTime += q3.front().TurnArroudT;

                cout << q3.front().pid << "\t\t" << q3.front().WaitingT << "\t\t\t  " << q3.front().TurnArroudT << endl;
                q3.pop();
                break;
            }
            else
            {
                q3.front().AdWaitingT += (q3.front().burstTime) - (q3time - 20);
                q3.front().burstTime = q3time - 20;
                break;
            }
        }
        else
        {
            q3.front().WaitingT = wait4 - (q3.front().AdWaitingT);
            totalWaitingTime += q3.front().WaitingT;

            q3.front().TurnArroudT = Otime + q3time;
            totalTurnAroundTime += q3.front().TurnArroudT;

            cout << q3.front().pid << "\t\t" << q3.front().WaitingT << "\t\t\t  " << q3.front().TurnArroudT << endl;
            q3.pop();
        }
    }
    // To get total time
    if (q3time < 20)
    {
        Otime += q3time;
    }
    else
    {
        Otime += 20;
    }

    return;
}

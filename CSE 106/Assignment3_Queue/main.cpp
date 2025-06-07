#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" << endl;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

int main()
{
    // freopen("test_input_1.txt", "r", stdin); // Test Case 1
    freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;

    Queue* merged = new ListQueue(); // stores the id in ascending order of timestamp
    Queue* queue[] = {Q1, Q2, Q, merged};
    int op;
    int id, ts, l; // ts -> timestamp
    int activeQueue = 0; // 0 -> Q1 ; 1 -> Q2 ; 2 -> Q(Merged);

    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic
        cin >> op;
        cout << "Operation " << i << " ";

        switch (op)
        {
            case 1:
                cin >> id >> ts;
                cout << "(Arrival " << id << " " << ts << "): " << endl;

                if (activeQueue != 2 && Q1->empty() && Q2->empty()) activeQueue = randomQueue() - 1;
                // merged->empty() ---> Q1->empty() && Q2->empty()

                queue[activeQueue]->enqueue(id);
                if (activeQueue < 2)
                {
                    merged->enqueue(id);
                    activeQueue = (activeQueue + 1) % 2; // 0 <--> 1
                }

                break;

            case 2:
                cin >> id >> ts;
                cout << "(Leave " << id << " " << ts << "): " << endl;

                if (activeQueue != 2 && !merged->empty() && merged->back() == id) activeQueue = (activeQueue + 1) % 2;
                // last patient will be removed

                for (int i = 0; i < 4; i++)
                {
                    l = queue[i]->size();
                    while (l--)
                    {
                        if (queue[i]->front() == id) queue[i]->dequeue();

                        else queue[i]->enqueue(queue[i]->dequeue());
                    }
                }
                break;

            case 3:
                cout << "(Merge): " << endl;

                if (activeQueue == 2) cout << "Already merged!" << endl;

                else
                {
                    while (!merged->empty()) Q->enqueue(merged->dequeue());
                    Q1->clear();
                    Q2->clear();
                    activeQueue = 2; // -> merged
                }
                break;

            case 4:
                cout << "(Split): " << endl;

                if (activeQueue != 2) cout << "Queue not merged!" << endl;

                else
                {
                    activeQueue = 0;
                    while (!Q->empty())
                    {
                        merged->enqueue(Q->front());
                        queue[activeQueue]->enqueue(Q->dequeue());
                        activeQueue = (activeQueue + 1) % 2; // 0 <--> 1
                    }
                }
                break;

            case 5:
                cout << "(Departure): " << endl;

                if (activeQueue == 2) id = Q->front();

                else if (Q1->empty()) id = Q2->front(); // if both empty -> id = -1

                else if (Q2->empty()) id = Q1->front();

                else id = queue[randomQueue() - 1]->front();


                if (id >= 0) // if all empty -> id = -1;
                {
                    if (activeQueue != 2 && !merged->empty() && merged->back() == id) activeQueue = (activeQueue + 1) % 2;
                    // last patient will be removed

                    for (int i = 0; i < 4; i++)
                    {
                        l = queue[i]->size();
                        while (l--)
                        {
                            if (queue[i]->front() == id) queue[i]->dequeue();

                            else queue[i]->enqueue(queue[i]->dequeue());
                        }
                    }
                }
                else cout << "All queues are empty!" << endl;

                break;

            default:
                cout << "Invalid Operation!" << endl;
                break;
        }


        cout << "Q1: " << Q1->toString() << endl;
        cout << "Q2: " << Q2->toString() << endl;
        cout << "Q : " << Q->toString() << endl;

        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
    }

    for (int i = 0; i < 4; i++) delete queue[i];

    return 0;
}
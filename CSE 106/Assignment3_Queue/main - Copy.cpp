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
    freopen("test_input_1.txt", "r", stdin); // Test Case 1
    // freopen("test_input_2.txt", "r", stdin); // Test Case 2
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
    
    // Queue* queue[] = {Q, Q1, Q2};
    Queue* order = new ListQueue();
    int op;
    bool merged = false;
    int id, ts, l, item, flag;

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
                
                if (merged)
                {
                    Q->enqueue(id);
                }
                else if (order->empty())
                {
                    if (randomQueue() == 2)
                    {
                        order->enqueue(1);
                        Q1->enqueue(id);
                    }
                    else
                    {
                        order->enqueue(2);
                        Q2->enqueue(id);
                    }
                }
                else
                {
                    if (order->back() == 2)
                    {
                        order->enqueue(1);
                        Q1->enqueue(id);
                    }
                    else
                    {
                        order->enqueue(2);
                        Q2->enqueue(id);
                    }
                }
                break;

            case 2:
                cin >> id >> ts;

                cout << "(Leave " << id << " " << ts << "): " << endl;

                if (merged)
                {
                    l = Q->size();
                    for (int i = 0; i < l; i++)
                    {
                        item = Q->dequeue();
                        if (item != id) Q->enqueue(item);
                    }
                }
                else
                {
                    l = order->size();
                    for (int i = 0; i < l; i++)
                    {
                        item = order->dequeue();
                        if (item == 1)
                        {
                            item = Q1->dequeue();
                            if (item != id)
                            {
                                Q1->enqueue(item);
                                order->enqueue(1);
                            }
                        }
                        else
                        {
                            item = Q2->dequeue();
                            if (item != id)
                            {
                                Q2->enqueue(item);
                                order->enqueue(2);
                            }
                        }
                    }
                }
                break;

            case 3:
                cout << "(Merge): " << endl;

                if (merged) cout << "Already merged!" << endl;

                else
                {
                    merged = true;
                    while (!order->empty())
                    {
                        item = order->dequeue();
                        if (item == 1) Q->enqueue(Q1->dequeue());

                        else Q->enqueue(Q2->dequeue()); 
                    }
                }
                break;

            case 4:
                cout << "(Split): " << endl;

                if (!merged) cout << "Queue not merged!" << endl;

                else
                {
                    merged = false;
                    flag = 1;
                    while (!Q->empty())
                    {
                        if (flag == 1)
                        {
                            Q1->enqueue(Q->dequeue());
                            order->enqueue(1);
                            flag = 2;
                        }
                        else
                        {
                            Q2->enqueue(Q->dequeue());
                            order->enqueue(2);
                            flag = 1;
                        }
                    }
                }
                break;

            case 5:
                flag = 0;
                l = order->size();
                cout << "(Departure): " << endl;

                if (merged) Q->dequeue();

                else if (order->empty()) cout << "Both queue are empty!" << endl;

                else if (Q1->empty())
                {
                    Q2->dequeue();
                    while (l--)
                    {
                        if (flag == 0 && order->front() == 2)
                        {
                            order->dequeue();
                            flag = 1;
                        }
                        else order->enqueue(order->dequeue());
                    }
                }

                else if (Q2->empty())
                {
                    Q1->dequeue();
                    while (l--)
                    {
                        if (flag == 0 && order->front() == 1)
                        {
                            order->dequeue();
                            flag = 1;
                        }
                        else order->enqueue(order->dequeue());
                    }
                }

                else if (randomQueue() == 1)
                {
                    Q1->dequeue();
                    while (l--)
                    {
                        if (flag == 0 && order->front() == 1)
                        {
                            order->dequeue();
                            flag = 1;
                        }
                        else order->enqueue(order->dequeue());
                    }
                }

                else
                {
                    Q2->dequeue();
                    while (l--)
                    {
                        if (flag == 0 && order->front() == 2)
                        {
                            order->dequeue();
                            flag = 1;
                        }
                        else order->enqueue(order->dequeue());
                    }
                }
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

    return 0;
}
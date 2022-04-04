#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class hashBucket
{
    int localDepth, capacity;
    vector<int> v;

public:
    hashBucket()
    {
    }
    hashBucket(int localDepth, int capacity)
    {
        this->localDepth = localDepth;
        this->capacity = capacity;
    }
    int getLocalDepth()
    {
        return localDepth;
    }
    int increaseLocalDepth()
    {
        localDepth++;
        return localDepth;
    }
    int decreaseLocalDepth()
    {
        localDepth--;
        return localDepth;
    }
    int getCapacity()
    {
        return capacity;
    }
    int isFull()
    {
        if (v.size() == capacity)
        {
            return 1;
        }
        return 0;
    }
    int isEmpty()
    {
        if (v.size() == 0)
        {
            return 1;
        }
        return 0;
    }
    int insert(int key)
    {
        if (!isFull())
        {
            v.push_back(key);
            return 1;
        }
        return 0;
    }
    int remove(int key)
    {
        vector<int>::iterator it;
        it = find(v.begin(), v.end(), key);
        if (it != v.end())
        {
            v.erase(it);
            return 1;
        }
        else
        {
            cout << "This key doesn't exist. So, can't remove!" << endl;
            return 0;
        }
    }
    int search(int key)
    {
        vector<int>::iterator it;
        it = find(v.begin(), v.end(), key);
        if (it != v.end())
        {
            return 1;
        }
        return 0;
    }
    void clear()
    {
        v.clear();
    }
    vector<int> copy()
    {
        vector<int> temp(v.begin(), v.end());
        return temp;
    }
    int display()
    {
        vector<int>::iterator it;
        for (it = v.begin(); it != v.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
        return 1;
    }
};

class Directory
{
    int globalDepth;
    int bucketCapacity;
    vector<hashBucket *> hashBuckets;
    vector<int> bno;

    // Finding the hash value
    int hash(int n, int depth)
    {
        return n & ((1 << depth) - 1);
    }

    int pairIndex(int bucketNum, int depth)
    {
        return bucketNum ^ (1 << (depth - 1));
    }

    int split(int bucketNum)
    {
        int localDepth, pair_index, indexDiff, dirSize;
        vector<int> temp;

        localDepth = hashBuckets[bucketNum]->increaseLocalDepth();
        if (localDepth > globalDepth)
        {
            for (int i = 0; i < (1 << globalDepth); i++)
            {
                hashBuckets.push_back(hashBuckets[i]);
            }
            globalDepth++;
        }

        if (globalDepth > 20)
        {
            return 0;
        }

        pair_index = pairIndex(bucketNum, localDepth);
        bno.push_back(pair_index);
        hashBuckets[pair_index] = new hashBucket(localDepth, bucketCapacity);
        temp = hashBuckets[bucketNum]->copy();
        hashBuckets[bucketNum]->clear();
        indexDiff = (1 << localDepth);
        dirSize = (1 << globalDepth);
        for (int i = pair_index - indexDiff; i >= 0; i -= indexDiff)
        {
            hashBuckets[i] = hashBuckets[pair_index];
        }
        for (int i = pair_index + indexDiff; i < dirSize; i += indexDiff)
        {
            hashBuckets[i] = hashBuckets[pair_index];
        }
        for (auto it = temp.begin(); it != temp.end(); it++)
        {
            insert(*it);
        }
        return 1;
    }

public:
    Directory()
    {
    }

    Directory(int globalDepth, int bucketCapacity)
    {
        this->globalDepth = globalDepth;
        this->bucketCapacity = bucketCapacity;
        for (int i = 0; i < (1 << globalDepth); i++)
        {
            bno.push_back(i);
            hashBuckets.push_back(new hashBucket(globalDepth, bucketCapacity));
        }
    }

    // Insertion
    int insert(int key)
    {
        int bucketNum;
        int depth = globalDepth;
        while (depth >= 0)
        {
            bucketNum = hash(key, depth);
            auto it = find(bno.begin(), bno.end(), bucketNum);
            if (it != bno.end())
            {
                break;
            }
            else
            {
                depth--;
            }
        }

        int status = hashBuckets[bucketNum]->insert(key);
        if (status == 0)
        {
            split(bucketNum);
            insert(key);
        }
        return 1;
    }

    // Remove
    int remove(int key)
    {
        int i = search(key);
        if (i != -1)
        {
            hashBuckets[i]->remove(key);
            return 1;
        }
        return 0;
    }

    // Search
    int search(int key)
    {
        for (auto it = bno.begin(); it != bno.end(); it++)
        {
            int i = hashBuckets[*it]->search(key);
            if (i == 1)
            {
                return *it;
            }
        }
        return -1;
    }

    // Display
    void display()
    {
        cout << globalDepth << endl;
        cout << bno.size() << endl;
        for (auto it = bno.begin(); it != bno.end(); it++)
        {
            int localDepth = hashBuckets[*it]->getLocalDepth();
            cout << hashBuckets[*it]->getCapacity() << " ";
            cout << localDepth << endl;
        }
    }
};

void menu()
{
    cout << "------------------" << endl;
    cout << "Codes for queries!" << endl;
    cout << "2 to insert" << endl;
    cout << "3 to search" << endl;
    cout << "4 to delete" << endl;
    cout << "5 to display the status of the hash table" << endl;
    cout << "6 to quit" << endl;
    cout << "------------------" << endl;
}

int main()
{
    int globalDepth;
    cin >> globalDepth;
    int bucketCapacity;
    cin >> bucketCapacity;

    int key, choice;

    Directory D(globalDepth, bucketCapacity);

    menu();

    do
    {
        cin >> choice;
        switch (choice)
        {
        case 2:
            cin >> key;
            D.insert(key);
            break;

        case 3:
            cin >> key;
            D.search(key);
            break;

        case 4:
            cin >> key;
            D.remove(key);
            break;

        case 5:
            D.display();
        }
    } while (choice != 6);

    return 0;
}
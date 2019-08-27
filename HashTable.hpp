#ifndef HW_7_HASH_TABLE
#define HW_7_HASH_TABLE

#include <string>

using namespace std;


struct activity
{
    string title;
    string location;
    int start;
    int end;
    int duration;
    activity* next;
};

class HashTable {
  public:
    HashTable(int hashTableSize, int startTime, int endTime);
    //~HashTable();
    void addActivity(string title, string location, int start, int end, int duration, int index);
    void deleteActivity(string title, int index);
    bool isInTable(string title, string location, int start, int end, int index);
    void printSchedule(int index);
    string getSchedule(int index, int size);
    string getLocation(int index, int x);
    int getNumItems(int index);

  private:
    /* member functions */
    activity* searchTable(string title, string location, int start, int end, int x);

    /* instance variables */
    activity** hashTable;
    int hashTableSize;
    int startTime;
    int endTime;
};

const int STOPWORD_TABLE_SIZE = 50;


#endif

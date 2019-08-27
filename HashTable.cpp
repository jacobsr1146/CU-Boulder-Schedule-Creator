#include "HashTable.hpp"
#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

HashTable::HashTable(int hashTableSize, int startTime, int endTime){
    this->startTime = startTime;
    this->endTime = endTime;
    this->hashTableSize = hashTableSize;
    hashTable = new activity*[hashTableSize];
    for(int x=0; x!=hashTableSize; x++){
      hashTable[x] = NULL;
    }
}

void HashTable::addActivity(string title, string location, int start, int end, int duration, int index){
    if(isInTable(title, location, start, end, index) == true){
      cout << "Activity Already In Schedule" << endl;
      return;
    }

  activity *na = new activity;
  na->title = title;
  na->location = location;
  na->start = start;
  na->end = end;
  na->duration = duration;
  if(hashTable[index] == NULL){
    na->next = NULL;
    hashTable[index] = na;
    cout << "Successfully Added Activity" << endl;
  }
  else{
     for(activity *temp = hashTable[index]; temp!=NULL; temp=temp->next){
      if(temp == hashTable[index]){
        if(na->end < temp->start){
          na->next = temp;
          hashTable[index] = na;
          cout << "Successfully Added Activity" << endl;
        }
      }
      if(temp->next == NULL){
        if(na->start > temp->end){
          temp->next = na;
          na->next = NULL;
          cout << "Successfully Added Activity" << endl;
        }
      }
      if(temp->end < na->start && na->end < temp->next->start){
        na->next = temp->next;
        temp->next = na;
        cout << "Successfully Added Activity" << endl;
      }
    }
  }
}

void HashTable::deleteActivity(string title, int index){
  string location = " ";
  int start;
  int end;
  for(activity *temp = hashTable[index]; temp != NULL; temp = temp->next){
    if(temp->title == title){
      location = temp->location;
      start = temp->start;
      end = temp->end;
    }
  }
  if(location == " "){
    cout << "Could Not Find Activity" << endl;
    return;
  }
  activity *temp = searchTable(title, location, start, end, index);
  if(temp == hashTable[index]){
    hashTable[index] = temp->next;
    delete temp;
    cout << "Successfully Deleted Activity" << endl;
  }
  else{
    for(activity *prev = hashTable[index]; prev!=NULL; prev = prev->next){
      if(prev->next == temp){
        prev->next = temp->next;
        delete temp;
        cout << "Successfully Deleted Activity" << endl;
      }
    }
  }
}

bool HashTable::isInTable(string title, string location, int start, int end, int index){
  if(searchTable(title, location, start, end, index) == NULL){
    return false;
  }
  return true;
}

activity* HashTable::searchTable(string title, string location, int start, int end, int x){
  for(activity *temp = hashTable[x]; temp!=NULL; temp = temp->next){
    if(temp->title == title && temp->location == location && temp->start == start && temp->end == end){
      return temp;
    }
  }
  return NULL;
}


void HashTable::printSchedule(int index){
  switch(index){
    case 1:
      cout << "----------SUNDAY----------" << endl;
      break;
    case 2:
      cout << "----------MONDAY----------" << endl;
      break;
    case 3:
      cout << "----------TUESDAY----------" << endl;
      break;
    case 4:
      cout << "----------WEDNESDAY----------" << endl;
      break;
    case 5:
      cout << "----------THURSDAY----------" << endl;
      break;
    case 6:
      cout << "----------FRIDAY----------" << endl;
      break;
    case 7:
      cout << "----------SATURDAY----------" << endl;
      break;
  }
  for(activity *temp = hashTable[index-1]; temp!=NULL; temp = temp->next){
    cout << " " << temp->title << ":" << endl;
    cout << "    " << temp->location << endl;
    cout << "    " << temp->start << "-" << temp->end << endl;
    cout << "-  -  -  -  -  -  -  -  -  -" << endl;
  }
}

string HashTable::getSchedule(int index, int size){
  string arr;
  for(activity* temp = hashTable[index]; temp!=NULL; temp = temp->next){
    arr = arr + to_string(temp->start) + to_string(temp->end) + "-";
  }
  return arr;
}

string HashTable::getLocation(int index, int x){
  int y=0;
  for(activity* temp = hashTable[index]; temp!=NULL; temp = temp->next){
    if(y==x){
      return temp->location;
    }
    y++;
  }
}

int HashTable::getNumItems(int index){
  int x=0;
  for(activity* temp = hashTable[index]; temp!=NULL; temp = temp->next){
    x++;
  }
  return x;
}

#include "HashTable.hpp"
#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


struct event
{
    string title;
    string location;
    int start;
    int end;
    int duration;
};

int time(int num){
  string time = to_string(num);
  if(time.size() == 4){
    if((int)time[2]>'5'){
      num = num + 40;
    }
    return num;
  }
  else if(time.size() == 3){
    if((int)time[1]>'5'){
      num = num + 40;
    }
    return num;
  }
}

int time2(int num){
  string time = to_string(num);
  if(time.size() == 4){
    if((int)time[2]>'5'){
      num = num - 40;
    }
    return num;
  }
  else if(time.size() == 3){
    if((int)time[1]>'5'){
      num = num - 40;
    }
    return num;
  }
}

int insert(string title, int start, int end){
  string r;
  cout << title << ":" << endl;
  cout << "Start: " << start << endl;
  cout << "End: " << end << endl;
  cout << "Is this ok?" << endl;
  cout << "1. Yes   2. No" << endl;
  getline(cin, r);
  return stoi(r);
}

void menu(){
  cout << "1. Add Activity" << endl;
  cout << "2. Delete Activity" << endl;
  cout << "3. Print Schedule" << endl;
  cout << "4. Find distance" << endl;
  cout << "5. Quit" << endl;
}

void pickLoc(){
  cout << "1. Engineering Quad      2. Reed Hall              3. Farrand Hall         4. Hallet Hall" << endl;
  cout << "5. Libby Hall            6. Baker Hall             7. Willard Hall         8. Cheyenne Hall" << endl;
  cout << "9. Farrand Field         10. C4C                   11. Engineering Center  12. Koelbel Building" << endl;
  cout << "13. Math Building        14. Benson Earth Science  15. Duane Physics       16. Wardenburg Health Center" << endl;
  cout << "17. Muenzinger Building  18. Visusal Arts Complex  19. UMC                 20. Chemistry Building" << endl;
  cout << "21. Norlin Library       22. Music Building        23. Folsom Field        24. Rec Center" << endl;
  cout << "25. BasketBall Stadium   26. Kittredge             27. Wolf Law Building   28. Fiske Planitarium" << endl;
  cout << "29. Macky Auditorium     30. Sewell Hall           31. Williams Village" << endl;
}

int main(int argc, char* argv[]){
  cout << "-----WELCOME TO THE CU SCHEDULE PLANNER-----" << endl << endl;
  string r1, r2, r3, r4, r5, r6;
  cout << "Start Day Time (ex: 700): ";
  getline(cin, r1);
  cout << endl;
  cout << "End Day Time (ex: 2300): ";
  getline(cin, r2);
  cout << endl;

  HashTable ht(7, stoi(r1), stoi(r2));
  int startTime = stoi(r1);
  int endTime = stoi(r2);
  Graph g;
  string loc[31] = {"Engineering Quad", " Reed Hall", "Farrand Hall", "Hallet Hall", "Libby Hall", "Baker Hall", "Willard Hall", "Cheyenne Arapahoe Hall",
   "Farrand Field", "C4C", "Engineering Center", "Koelbel Building", "Math Building", "Benson Earth Science", "Duane Physics", "Wardenburg Health Center",
   "Muenzinger Building", "Visual Arts Complex", "UMC", "Chemistry Building", "Norlin Library", "Music Building", "Folsom Field", "Rec Center",
   "Basketball Stadium", "Kittredge", "Wolf Law Building", "Fiske Planitarium", "Macky Auditorium", "Sewell Hall", "Williams Village"};
  int distance[31][31] = {{0,2,2,2,2,0,0,0,0,0,3,3,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//Engineering Quad
                          {2,0,2,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//Reed Hall
                          {2,2,0,2,2,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//Farrand Hal
                          {2,2,2,0,0,0,2,0,0,2,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//Hallet Hall
                          {2,0,2,0,0,2,0,0,2,0,0,0,0,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//Libby Hall
                          {0,0,0,0,2,0,0,0,2,0,0,0,0,0,2,0,0,5,0,0,0,3,0,0,0,0,0,0,0,0,0},//Baker Hall
                          {0,0,2,2,0,0,0,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//Willard Hall
                          {0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,2,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0},//Cheyenne Arapahoe Hall
                          {0,0,2,0,2,2,2,2,0,0,0,0,0,0,0,3,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},//Farrand Field
                          {0,0,0,2,0,0,3,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,10,5,0,4,0,0,10},//C4C
                          {3,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//Engineering Center
                          {3,2,0,3,0,0,0,0,0,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0},//Koelbel Building
                          {2,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},//Math Buulding
                          {3,0,0,0,2,0,0,0,0,0,0,0,2,0,4,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,8},//Benson Earth Science
                          {0,0,0,0,3,2,0,0,0,0,0,0,0,4,0,0,3,0,0,0,0,0,3,0,0,0,0,0,0,0,10},//Duane Physics
                          {0,0,0,0,0,0,0,2,3,0,0,0,0,0,0,0,0,0,9,0,0,3,0,0,0,0,0,0,0,0,0},//Wardenburg Heath Center
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,5,0,0,3,0,2,4,0,0,0,0,0,0,10},//Muenzinger Building
                          {0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,5,0,3,2,4,4,0,0,0,0,0,0,0,0,0},//Visual Arts Complex
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,3,0,2,0,0,0,0,0,0,0,0,0,0,12},//UMC
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,2,0,0,0,0,0,0,0,7,0,0},//Chemistry Building
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,4,9,2,0,0,0,4,0,0,0,0,5,0,0},//Norlin Library
                          {0,0,0,0,0,3,0,3,2,0,0,0,0,0,0,3,0,4,0,0,0,0,2,0,0,0,0,0,0,0,0},//Music Building
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,4,3,0,2,0,0,0,0,2,0,3,0,0,0,0,0,0,0},//Folsom Field
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,4,0,3,0,0,0,0,0,0,4,0},//Rec Center
                          {0,0,0,0,0,0,0,0,0,10,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,7,0,0,0},//Basketball Stadium
                          {0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,3,2,0,0,0},//Kittredge
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},//Wolf Law Building
                          {0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,2,0,0,0,0,0},//Fiske Planitarium
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,5,0,0,0,0,0,0,0,0,5,0},//Macky Auditorium
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,5,0,0},//Sewell Hall
                          {0,0,0,0,0,0,0,0,0,10,0,0,8,8,10,0,10,0,12,0,0,0,0,0,0,0,0,0,0,0,0}};//Williams Village
  for(int x=0; x!=31; x++){
    g.addVertex(loc[x]);
  }

  for(int y=0; y!=31; y++){
    for(int x=0; x!=31; x++){
      if(distance[y][x] > 0){
        g.addEdge(loc[y], loc[x], distance[y][x]);
      }
    }
  }
  string times;
  string Arr[20];
  int d1, d2, size;
  int z = 0;
  int last;
  event *e = new event;
  event *temp = new event;
  event *tempN = new event;
  string choice = "0";
  int repeat = 0;
  while(stoi(choice)!=5){
    menu();
    getline(cin, choice);
    switch(stoi(choice)){
      case 1: //add activity
        cout << "name: ";
        getline(cin, r1);
        cout << endl;
        cout << "Set Start/End Time?" << endl;
        cout << "1. Yes     2. No" << endl;
        getline(cin, r5);
        if(stoi(r5) == 1){
          cout << "Start Time (ex: 1400): ";
          getline(cin, r2);
          cout << endl;
          cout << "End Time (ex: 1400): ";
          getline(cin, r3);
          cout << endl;
        }
        if(stoi(r5) == 2){
          cout << "Event Duration (min): ";
          getline(cin, r2);
          cout << endl;
          r3 = "0";
        }
        cout << "Pick a location: " << endl;
        pickLoc();
        getline(cin, r4);
        cout << "Day of the Week: " << endl;
        cout << "1. Sunday" << endl;
        cout << "2. Monday" << endl;
        cout << "3. Tuesday" << endl;
        cout << "4. Wednesday" << endl;
        cout << "5. Thursday" << endl;
        cout << "6. Friday" << endl;
        cout << "7. Saturday" << endl;
        getline(cin, r6);

        size = ht.getNumItems(stoi(r6)-1);
        times = ht.getSchedule(stoi(r6)-1, size);
        repeat = 0;
        last = 0;
        for(int x=0; x!=times.size(); x++){
          if(times[x] == '-'){
            Arr[repeat] = times.substr(last,x-last);
            repeat++;
            last = x+1;
          }
        }
        repeat = 0;
        e->title = r1;
        e->location = loc[stoi(r4)-1];
        if(stoi(r3) == 0){ //no set time
          e->duration = stoi(r2);

          for(int x=0; x!=size && z==0; x++){
            if(Arr[x].size() == 8){
              temp->start = stoi(Arr[x].substr(0,4));
              temp->end = stoi(Arr[x].substr(4,4));
            }
            else if(Arr[x].size() == 7){
              temp->start = stoi(Arr[x].substr(0,3));
              temp->end = stoi(Arr[x].substr(3,4));
            }
            else if(Arr[x].size() == 6){
              temp->start = stoi(Arr[x].substr(0,3));
              temp->end = stoi(Arr[x].substr(3,3));
            }
            temp->location = ht.getLocation(stoi(r6)-1, x);
            if(x+1 != size){
              if(Arr[x+1].size() == 8){
                tempN->start = stoi(Arr[x+1].substr(0,4));
                tempN->end = stoi(Arr[x+1].substr(4,4));
              }
              else if(Arr[x+1].size() == 7){
                tempN->start = stoi(Arr[x+1].substr(0,3));
                tempN->end = stoi(Arr[x+1].substr(3,4));
              }
              else if(Arr[x+1].size() == 6){
                tempN->start = stoi(Arr[x+1].substr(0,3));
                tempN->end = stoi(Arr[x+1].substr(3,3));
              }
              tempN->location = ht.getLocation(stoi(r6)-1, x+1);
            }
            if(x==0){
              d1 = time2(temp->start - g.shortestDistance(e->location, temp->location) - e->duration);
              if(d1 >= startTime){
                if(insert(e->title, d1, time(d1+e->duration)) == 1){
                  e->start = d1;
                  e->end = time(d1+e->duration);
                  z++;

                }
              }
            }
            if(x+1 == size){
              d1 = time(temp->end + g.shortestDistance(temp->location, e->location) + e->duration);
              if(d1 <= endTime){
                if(insert(e->title, time(temp->end + g.shortestDistance(temp->location, e->location)), d1) == 1){
                  e->start = time(temp->end + g.shortestDistance(temp->location, e->location));
                  e->end = d1;
                  z++;
                }
              }
            }
            else{
              d1 = time(temp->end + g.shortestDistance(temp->location, e->location));
              d2 = time2(tempN->start - g.shortestDistance(e->location, tempN->location));
              if((d1 + e->duration) <= d2){
                if(insert(e->title, d1, time(d1+e->duration)) == 1){
                  e->start = d1;
                  e->end = d2;
                  z++;
                }
              }
            }
          }
        }
        else{ //set time
          e->start = stoi(r2);
          e->end = stoi(r3);
          e->duration = time2(stoi(r3) - stoi(r2));

          for(int x=0; x!=size && z==0; x++){
            temp->start = stoi(Arr[x].substr(0,4));
            temp->end = stoi(Arr[x].substr(4,4));
            temp->location = ht.getLocation(stoi(r6)-1, x);
            if(x+1 != size){
              tempN->start = stoi(Arr[x+1].substr(0,4));
              tempN->end = stoi(Arr[x+1].substr(4,4));
              tempN->location = ht.getLocation(stoi(r6)-1, x+1);
            }
            if(x==0){
              d1 = time(e->end + g.shortestDistance(e->location, temp->location));
              if(d1 <= temp->start && e->start >= startTime){
                z++;
              }
            }
            else if(x+1 == size){
              d1 = time(temp->end + g.shortestDistance(temp->location, e->location));
              if(e->start >= d1 && e->end <= endTime){
                z++;
              }
            }
            if(x!=0 && x+1 != size){
              d1 = time(temp->end + g.shortestDistance(temp->location, e->location));
              d2 = time(e->end + g.shortestDistance(e->location, tempN->location));
              if((e->start >= d1) && (d2 <= tempN->start) && e->start >= startTime && e->end <= endTime){
                z++;
              }
            }
          }
        }
        if(z==0 && size!=0){
          cout << "Event could not fit in schedule for that day" << endl;
          delete e;
        }
        else{
          ht.addActivity(e->title, e->location, e->start, e->end, e->duration, stoi(r6)-1);
        }
        z=0;
        break;
      case 2: //delete activity
        cout << "name: ";
        getline(cin, r1);
        cout << endl;
        cout << "Day of the Week: " << endl;
        cout << "1. Sunday" << endl;
        cout << "2. Monday" << endl;
        cout << "3. Tuesday" << endl;
        cout << "4. Wednesday" << endl;
        cout << "5. Thursday" << endl;
        cout << "6. Friday" << endl;
        cout << "7. Saturday" << endl;
        getline(cin, r2);
        ht.deleteActivity(r1, stoi(r2)-1);
        break;
      case 3: //print schedule
        cout << "Day of the Week: " << endl;
        cout << "1. Sunday" << endl;
        cout << "2. Monday" << endl;
        cout << "3. Tuesday" << endl;
        cout << "4. Wednesday" << endl;
        cout << "5. Thursday" << endl;
        cout << "6. Friday" << endl;
        cout << "7. Saturday" << endl;
        getline(cin, r1);
        ht.printSchedule(stoi(r1));
        break;
      case 4: //find distance
        cout << "Pick Locations: " << endl;
        pickLoc();
        cout << "Location 1:";
        getline(cin, r1);
        cout << endl;
        cout << "Location 2: ";
        getline(cin, r2);
        cout << endl;
        cout << "min: " << g.shortestDistance(loc[stoi(r1)-1], loc[stoi(r2)-1]) << endl;
        break;
      case 5://quit
        break;
    }
  }

}

/*ToDo List:
    -create findSpace() function
    -create user interaction section
    -Bug Test*/

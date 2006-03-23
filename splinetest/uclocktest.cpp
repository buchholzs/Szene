#include <assert.h>
#include <iomanip>
#include <iostream>
#include <list>
#include <time.h>

using namespace std;
const int avgSize = 100;

list<float> fpsQ_;

void dumpFps() {
  cout << "fpsQ_=[";
  for (list<float>::iterator it = fpsQ_.begin();
       it != fpsQ_.end(); ++it) {
    cout << *it << ' ';
  }
  cout << "]" << endl;
}
float calcAvg(float fps) {
  fpsQ_.push_front(fps);
  if (fpsQ_.size() > avgSize) {
    fpsQ_.pop_back(); // remove 1. elem
    assert(fpsQ_.size()==avgSize);
  }
  // calc average
  float avg = 0.0; 
  for (list<float>::iterator it = fpsQ_.begin();
       it != fpsQ_.end(); ++it) {
    avg += *it; // *((_List_node<float>*)it->_M_node)
  }
  avg /= fpsQ_.size();
  return avg;
}

int main() {
  clock_t prevtime = clock();
  cout << "Start" << endl;
  int cntok = 0;
  int cntnok = 0;
  float avgDiff = 0.0;
  while(1) {
    clock_t currtime = clock();
    if (prevtime < currtime) {
      cout << "prevtime=" << prevtime 
           << " curtime=" << currtime << endl; 
    }
    assert(prevtime <= currtime);
    float difftime = (float)(currtime - prevtime)*1000.0 / (float)CLOCKS_PER_SEC;
    avgDiff = calcAvg(difftime);
    if ((long)difftime == 0) {
      continue;
    }
    prevtime = currtime;
    
    dumpFps();

    if (difftime < 0) {
      cntnok ++;
      cout << "difftime=" << difftime;
    } else {
      cout << "difftime=" << difftime;
      cntok ++;
    }
    cout << " avg=" << avgDiff << " ok=" << cntok << " not ok=" << cntnok << endl; 
  }

  return 0;
}

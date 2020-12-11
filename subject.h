#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <utility>
#include <string>

class Observer;

class Subject {
   // std::vector<Observer*> observers;

  public:
  std::vector<Observer*> observers;
    void attach(Observer *o);  
    void notifyObservers();
    virtual std::pair<char, int> getInfo() const = 0;
};

#endif

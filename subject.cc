#include "subject.h"
#include "observer.h"


void Subject::attach(Observer *o) { observers.emplace_back(o); }

void Subject::notifyObservers() {
    for (auto obs = observers.begin(); obs != observers.end(); ++obs) {
        (*obs)->notify( *this );
    }
}

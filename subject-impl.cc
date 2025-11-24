module Subject;

import <vector>;
import <algorithm>;
import Observer;

using namespace std;

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::detach(Observer *o) {
    for (auto it = observers.begin(); it != observers.end();) {
        if (*it == o) it = observers.erase(it);
        else ++it;
    }
}

void Subject::notifyObservers() {
    for (int i = 0; i < observers.size(); ++i){
        if (observers[i]) observers[i]->notify();
    }
}

Subject::~Subject() {}

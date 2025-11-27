export module Subject;

import <vector>;
import Observer;

using namespace std;

export class Subject {
    protected:
        vector<Observer*> observers;

    public: 
        void attach(Observer *o);
        void detach(Observer *o);
        void notifyObservers(); 
        virtual ~Subject() = 0;
};

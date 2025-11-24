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
        virtual ~Subject() = 0;

    protected:
        void notifyObservers(); 
};

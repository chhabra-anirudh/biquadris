export module Subject;

import <vector>;
import Observer;

using namespace std;

export class Subject {
    protected:
        vector<Observer*> observers;

    public: 
        // Attaches a new observer to this subject
        void attach(Observer *o);
        // Removes an observer from this subject
        void detach(Observer *o);
        // Notifies all attached observers of a state change
        void notifyObservers(); 
        // Pure virtual destructor
        virtual ~Subject() = 0;
};

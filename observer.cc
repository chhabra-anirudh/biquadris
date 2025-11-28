export module Observer;

using namespace std;

export class Observer {
    public: 
        // Pure vitual notify function
        virtual void notify() = 0; 
        // destructor
        virtual ~Observer();
};

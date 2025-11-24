export module Observer;

using namespace std;

export class Observer {
    public: 
        virtual void notify() = 0; 
        virtual ~Observer();
};

#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum EventType {
   EVENT_FIRST,
   EVENT_SECOND,
};

//Extend this class
class Observer
{
public:
    virtual void catchEvent(EventType e) = 0;
    virtual ~Observer(){};
};

class Observed
{
    //List of observers
    typedef vector<Observer*> ObserverList;
    typedef map<EventType, ObserverList> observersTable;
    //map of observers for specific event type
    observersTable m_observers;
public:
    //Add observer to the evtHandler
    void addObserver(Observer &observer, EventType eType) {
        m_observers[eType].push_back(&observer);
    }

    //Send out evt to registered observers for specific event
    void sendEvent(EventType event) {
        ObserverList& observers = m_observers[event];
        for (ObserverList::iterator it = observers.begin(); it != observers.end(); ++it) {
            Observer *observer = *it;
            observer->catchEvent(event);
        }
   }
};

//Create class that extends Observer class
class Player: public Observer {
public:
    //Override method to catch events
    void catchEvent(EventType evt) {
        cout << "player observer " << evt << endl;
    }
};

//Second class for testing
class SecondPlayer: public Observer {
    //Override method to catch events
    void catchEvent(EventType evt) {
        cout << "second player observer " << evt << endl;
    }
};

int main()
{
    //Create global event handler class
    Observed evtHandler;
    //Create test class
    Player p;
    //add test class to the observers list in the event handler class
    evtHandler.addObserver(p, EVENT_FIRST);
    //second test class
    SecondPlayer p2;
    //add second test class to observer list in the event handler class
    evtHandler.addObserver(p2, EVENT_SECOND);
    evtHandler.addObserver(p2, EVENT_FIRST);

   cout << "input event code: ";
   int evt;
   cin >> evt;
   switch(evt) {
        case 0:
            //Send event to eventHandler class
            evtHandler.sendEvent(EVENT_FIRST);
            break;
        case 1:
            //Send event to eventHandler class
            evtHandler.sendEvent(EVENT_SECOND);
            break;
   }

   return 0;
}

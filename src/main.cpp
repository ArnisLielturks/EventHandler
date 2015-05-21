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
   typedef vector<Observer*> ObserverList;
   typedef map<EventType, ObserverList> observersTable;
   observersTable m_observers;
public:
   void addObserver(Observer &observer, EventType eType) {
      m_observers[eType].push_back(&observer);
   }

   void sendEvent(EventType event) {
      ObserverList& observers = m_observers[event];
      for (ObserverList::iterator it = observers.begin(); it != observers.end(); ++it) {
         Observer *observer = *it;
         observer->catchEvent(event);
      }
   }
};

class Player: public Observer {
public:
   void catchEvent(EventType evt) {
      cout << "player observer " << evt << endl;
   }
};

class SecondPlayer: public Observer {
   void catchEvent(EventType evt) {
      cout << "second player observer " << evt << endl;
   }
};

int main()
{
   Observed evtHandler;
   Player p;
   evtHandler.addObserver(p, EVENT_FIRST);
   SecondPlayer p2;
   evtHandler.addObserver(p2, EVENT_SECOND);
   evtHandler.addObserver(p2, EVENT_FIRST);

   cout << "input event code: ";
   int evt;
   cin >> evt;
   switch(evt) {
      case 0:
         evtHandler.sendEvent(EVENT_FIRST);
         break;
      case 1:
         evtHandler.sendEvent(EVENT_SECOND);
         break;
   }

   return 0;
}

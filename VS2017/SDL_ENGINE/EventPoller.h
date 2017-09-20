#ifndef EVENTPOLLER_H
#define EVENTPOLLER_H

#include "EventHandler.h"
#include <vector>

//Event poller singleton for sending event messages to all EventHandlers
class EventPoller {
public:
	static EventPoller* instance();

	void update();

	void addHandler(EventHandler* pHandler);
	void removeHandler(EventHandler* pHandler);
	void clean();

private:
	EventPoller(){};
	std::vector<EventHandler*> m_handlers;
};

#endif
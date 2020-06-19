#pragma once
#include <vector>
#include <string>

class Object;
class Observer;

class Subject
{
public:
	Subject();
	virtual ~Subject();
	
	void AddObserver(Observer* observer);

	void RemoveObserver(Observer* observer);
	
	void Notify(const Object& actor, const std::string& event);
private:
	const unsigned int m_MaxObservers = 10;
	std::vector<Observer*>m_pObservers;
	int m_NrObservers;
};
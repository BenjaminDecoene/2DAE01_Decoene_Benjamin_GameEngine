#include "pch.h"
#include "Subject.h"
#include "Observer.h"

Subject::Subject()
	:m_pObservers(m_MaxObservers)
	,m_NrObservers(0)
{
}

Subject::~Subject()
{
	for(auto i : m_pObservers)
	{
		if(i != nullptr)
		{
			delete i;
			i = nullptr;
		}
	}
}

void Subject::AddObserver(Observer* observer)
{
	m_pObservers[m_NrObservers] = observer;
	m_NrObservers++;
}

void Subject::RemoveObserver(Observer* observer)
{
	for(int i{}; i < m_NrObservers; i++)
	{
		if(observer == m_pObservers[i])
		{
			m_pObservers.erase(m_pObservers.begin() + i);
			break;
		}
	}
	m_NrObservers--;
}

void Subject::Notify(const Object& actor, const std::string& event)
{
	for(int i{}; i < m_NrObservers; i++)
	{
		m_pObservers[i]->Notify(actor, event);
	}
}
#include "CLocator.h"

CLocator* CLocator::instance = nullptr;

CLocator* CLocator::Instance()
{
	if (instance == nullptr)
	{
		instance = new CLocator();
	}
	return instance;
}

void CLocator::Add(CAbstractService* service)
{
	services.push_back(service);
}

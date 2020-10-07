#ifndef CLOCATOR_H
#define CLOCATOR_H
#endif

#include <vector>
#include "CAbstractService.h"

using namespace std;
class CLocator
{
private:
	static CLocator* instance;
	vector<CAbstractService*> services;
public:
	static CLocator* Instance();
	void Add(CAbstractService*);
	template<typename T>
	T* Get();
};

template<typename T>
inline T* CLocator::Get()
{
	for (auto service : services)
	{
		T* cast = dynamic_cast<T*>(service);
		if (cast != nullptr) return cast;
	}
	return nullptr;
}

#ifndef CANIMATIONSMANAGER_H
#define CANIAMTIONSMANAGER_H

#include "CAnimation.h"
#include <unordered_map>
using namespace std;
class CAnimationsManager
{
private:
	unordered_map<int, LPANIMATION> animations;
public:
	void Init();
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
};

#endif

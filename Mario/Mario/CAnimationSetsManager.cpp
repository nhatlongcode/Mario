#include "CAnimationSetsManager.h"

void CAnimationSetsManager::Add(int id, LPANIMSET ani)
{
	animation_sets[id] = ani;
}

LPANIMSET CAnimationSetsManager::Get(unsigned int id)
{
	LPANIMSET ani_set = animation_sets[id];
	if (ani_set == NULL)
		DebugOut(L"[ERROR] Failed to find animation set id: %d\n", id);

	return ani_set;
}

void CAnimationSetsManager::Clear()
{
	for (auto x : animation_sets)
	{
		auto element = x.second;
		if (element != nullptr) delete element;
	}
	animation_sets.clear();
}

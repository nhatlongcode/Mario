#include "CAnimationSetsManager.h"

void CAnimationSetsManager::Add(int id, LPANIM_SET ani)
{
	animation_sets[id] = ani;
}

LPANIM_SET CAnimationSetsManager::Get(unsigned int id)
{
	LPANIM_SET ani_set = animation_sets[id];
	if (ani_set == NULL)
		DebugOut(L"[ERROR] Failed to find animation set id: %d\n", id);

	return ani_set;
}

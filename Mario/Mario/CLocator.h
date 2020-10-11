#pragma once
template<typename T>
class CLocator
{
private:
	static T* instance;
public:
	static T* Get();

	static void Add(T* ins);
};

template <typename T>
T* CLocator<T>::instance;

template<typename T>
inline T* CLocator<T>::Get()
{
	return instance;
}

template<typename T>
inline void CLocator<T>::Add(T* ins)
{
	instance = ins;
}
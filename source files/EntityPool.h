#pragma once

#include "PCH.h"

//메모리풀 => 메모리 단편화 현상을 방지한다.
template <typename T>
class CEntityPool
{
	enum { 
			DEFAULT_MAX_SIZE = 100,
			DEFAULT_MAX_COUNT = 10
		};

private:
	unordered_set<T*> m_UsingEntities;
	stack<T*> m_FreeEntities;
	int m_nMaxSize;
	int m_nMaxCount;

public:
	CEntityPool(int _maxSize = DEFAULT_MAX_SIZE, int _maxCount = DEFAULT_MAX_COUNT);
	~CEntityPool();

	void Allocate();
	void Deallocate();

	T* New();
	void Delete(void* _entity);

	typename unordered_set<T*>::iterator begin();
	typename unordered_set<T*>::iterator end();
	typename unordered_set<T*>::const_iterator cbegin() const;
	typename unordered_set<T*>::const_iterator cend() const;
};

template<typename T>
CEntityPool<T>::CEntityPool(int _maxSize, int _maxCount)
	: 
	m_nMaxSize(_maxSize < DEFAULT_MAX_SIZE ? DEFAULT_MAX_SIZE : _maxSize), 
	m_nMaxCount(_maxCount < DEFAULT_MAX_COUNT ? DEFAULT_MAX_COUNT : _maxCount)
{

}

template<typename T>
CEntityPool<T>::~CEntityPool()
{
	Deallocate();
}

template<typename T>
void CEntityPool<T>::Allocate()
{
	//메모리를 미리 할당받는다.
	for (int i = 0; i < m_nMaxCount; i++)
		m_FreeEntities.push((T*)malloc(m_nMaxSize));
}

template<typename T>
void CEntityPool<T>::Deallocate()
{
	//메모리 해제
	if (m_UsingEntities.size() > 0)
	{
		for (auto it : m_UsingEntities)
			delete it;
		m_UsingEntities.clear();
	}

	while (!m_FreeEntities.empty())
	{
		free(m_FreeEntities.top());
		m_FreeEntities.pop();
	}
}

template<typename T>
T* CEntityPool<T>::New()
{
	//여분이 없다면 capacity를 2배로 늘린다.
	if (m_FreeEntities.empty())
		for (int i = 0; i < m_nMaxCount; i++)
			m_FreeEntities.push((T*)malloc(m_nMaxSize));

	T* newEntity = m_FreeEntities.top();
	m_FreeEntities.pop();
	m_UsingEntities.insert(newEntity);

	return newEntity;
}

template<typename T>
void CEntityPool<T>::Delete(void* _entity)
{
	auto it = m_UsingEntities.find((T*)_entity);
	m_UsingEntities.erase(it);
	((T*)_entity)->~T();
	m_FreeEntities.push((T*)_entity);
}

template<typename T>
typename unordered_set<T*>::iterator CEntityPool<T>::begin()
{
	return m_UsingEntities.begin();
}

template<typename T>
typename unordered_set<T*>::iterator CEntityPool<T>::end()
{
	return m_UsingEntities.end();
}

template<typename T>
typename unordered_set<T*>::const_iterator CEntityPool<T>::cbegin() const
{
	return m_UsingEntities.cbegin();
}

template<typename T>
typename unordered_set<T*>::const_iterator CEntityPool<T>::cend() const
{
	return m_UsingEntities.cend();
}

#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_

#include <cassert>

template <class T> class Singleton
{
    private:
        static T *m_singleton;

    public:
        Singleton()
        {
            assert(!m_singleton);

            // Offset from Singleton<T> to T. This lets calculate the location of T object in memory.
            int offset = (int)(T*)1 - (int)(Singleton<T> *)(T*)1;

            m_singleton = (T*)((int)this + offset);
        }
        ~Singleton()
        {
            assert(m_singleton);
            m_singleton = nullptr;
        }
        static T & GetSingleton() { assert(m_singleton); return *m_singleton; }
        static T * GetSingletonPtr() { assert(m_singleton); return m_singleton; }
};
template <class T> T * Singleton<T>::m_singleton = 0;

#endif
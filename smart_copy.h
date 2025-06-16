#pragma once


template<typename T> 
void smart_copy(const T* start, const T* end, T* target)
{
        smart_copy_helper<T, !NumTraits<T>::RequireInitialization>::run(start, end, target);
}
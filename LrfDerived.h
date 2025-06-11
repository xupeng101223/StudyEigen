#pragma once
#include "LrfHasCols.h"
#include "LrfHasRows.h"

template<typename T>
concept LrfDerived = LrfHasCols<T> && LrfHasRows<T>;
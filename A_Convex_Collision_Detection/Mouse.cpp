#include "Mouse.h"

Mouse* Mouse::s_pInstance = nullptr;

Mouse& Mouse::getInstance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new Mouse();
	}

	return *s_pInstance;
}
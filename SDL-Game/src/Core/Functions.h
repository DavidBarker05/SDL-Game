#ifndef FUNCTIONS_H
#define FUNCTIONS_H

template <typename To, typename From>
To* Cast(From* from)
{
	return dynamic_cast<To*>(from);
}
#endif // !FUNCTIONS_H

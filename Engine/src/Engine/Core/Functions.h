#pragma once

template <typename To, typename From>
To* Cast(From* from)
{
	return dynamic_cast<To*>(from);
}
#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

template<class T>
inline T ClampIntoRange(T value, T lower_range, T upper_range)
{
	if (value > upper_range)
		return upper_range;

	if (value < lower_range)
		return lower_range;

	return value;
}


#endif //ENGINE_MATH_H

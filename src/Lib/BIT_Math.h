
#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(ADDRESS, BIT_POS)		(ADDRESS |= (1 << BIT_POS))
#define CLEAR_BIT(ADDRESS, BIT_POS)	    (ADDRESS &= ~(1 << BIT_POS))
#define TOGGLE_BIT(ADDRESS, BIT_POS)	(ADDRESS ^= (1 << BIT_POS))
#define READ_BIT(ADDRESS, BIT_POS)		((ADDRESS >> BIT_POS) & 1)


#endif /* BIT_MATH_H_ */
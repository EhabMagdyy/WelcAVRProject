/*
 * IncFile1.h
 *
 * Created: 9/6/2025 1:54:59 PM
 *  Author: Ehab
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(ADDRESS, BIT_POS)		(ADDRESS |= (1 << BIT_POS))
#define CLEAR_BIT(ADDRESS, BIT_POS)	    (ADDRESS &= ~(1 << BIT_POS))
#define TOGGLE_BIT(ADDRESS, BIT_POS)	(ADDRESS ^= (1 << BIT_POS))
#define READ_BIT(ADDRESS, BIT_POS)		((ADDRESS >> BIT_POS) & 1)

#define CLR_BITS_IN_REG(REG, MASK)      (REG = (REG & (~MASK)))
#define SET_BITS_IN_REG(REG, MASK)      (REG = (REG | MASK))


#endif /* BIT_MATH_H_ */
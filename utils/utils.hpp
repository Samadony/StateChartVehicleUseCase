/*
 * utils.hpp
 *
 *  Created on: Jan 10, 2025
 *      Author: Ahmed Elsamadony
 */

#ifndef UTILS_HPP
#define UTILS_HPP

/*
 * Bitwise operations
 */
//Write
#define SET_BIT(Reg, Bit_Num)					(Reg |= (1 << Bit_Num))
#define CLR_BIT(Reg, Bit_Num)					(Reg &= ~(1 << Bit_Num))
#define TGL_BIT(Reg, Bit_Num)					(Reg ^= (1 << Bit_Num))
#define ASSIGN_BIT(Reg, Bit_Num, Bit_Value)		Bit_Value ? \
												SET_BIT(Reg, Bit_Num) : \
												CLR_BIT(Reg, Bit_Num)
//Read
#define GET_BIT(Reg, Bit_NUM)					(Reg & (1 << Bit_NUM))

#endif // UTILS_HPP

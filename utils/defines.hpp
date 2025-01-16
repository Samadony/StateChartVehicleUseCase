/*
 * defines.hpp
 *
 *  Created on: Jan 10, 2025
 *      Author: Ahmed Elsamadony
 */

#ifndef DEFINES_HPP
#define DEFINES_HPP

#define ENABLE								0xFFU
#define DISABLE								0x00U
#define UTEST								ENABLE

#if(ENABLE == UTEST)
#define PRIVATE                             public
#define PROTECTED                           public  
#else
#define PRIVATE								private
#define PRIVATE								protected
#endif

#define PUBLIC_API							extern
#define	PUBLIC

#endif // DEFINES_HPP

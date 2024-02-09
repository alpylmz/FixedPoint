#ifndef TEMPLATE_UTILS_H__
#define TEMPLATE_UTILS_H__

#include <stdint.h>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

using int8_bt    = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<8,    8,    boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using int16_bt   = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<16,   16,   boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using int32_bt   = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<32,   32,   boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using int64_bt   = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<64,   64,   boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using int128_t  = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<128,  128,  boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using int256_t  = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<256,  256,  boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using int512_t  = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<512,  512,  boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using int1024_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<1024, 1024, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using int2048_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<2048, 2048, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using int4096_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<4096, 4096, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using int8192_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<8192, 8192, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using max_int   = int8192_t;
using bigfloat  = boost::multiprecision::cpp_dec_float_100;

// This is a dummy type meaning that there are too many bits in the data type
struct TooManyBits;

// template <int X>
// struct ROUND_UP_INT_SIZE
// {
//     static int RESULT = ROUND_UP_INT_SIZE<X+1;
// };


/// RETURNS a signed integer type that has at least as many bits as the value of BITS
template <int BITS>
struct GET_INT_WITH_LENGTH
{
    // The default is that an integer with N bits can be represented
    // by an integer with N+1 bits
    typedef typename GET_INT_WITH_LENGTH<BITS+1>::RESULT RESULT;
};

template <>
struct GET_INT_WITH_LENGTH<8>
{
    typedef int8_bt RESULT;
};

template <>
struct GET_INT_WITH_LENGTH<16>
{
    typedef int16_bt RESULT;
};

template <>
struct GET_INT_WITH_LENGTH<32>
{
    typedef int32_bt RESULT;
};

template <>
struct GET_INT_WITH_LENGTH<64>
{
    typedef int64_bt RESULT;
};

template <>
struct GET_INT_WITH_LENGTH<128>
{
    typedef int128_t RESULT;
};

template <>
struct GET_INT_WITH_LENGTH<256>
{
    typedef int256_t RESULT;
};

template <>
struct GET_INT_WITH_LENGTH<512>
{
    typedef int512_t RESULT;
};

template <>
struct GET_INT_WITH_LENGTH<1024>
{
    typedef int1024_t RESULT;
};


template <>
struct GET_INT_WITH_LENGTH<2048>
{
    typedef TooManyBits RESULT;
};

/// Returns X1 if isX1 is true, else return X2
template <int X1, int X2, bool isX1>
struct PICK_ONE
{
    static const int RESULT; // Undefined
};

/// Returns X1 if (X1 > X2) else returns X2
template <int X1, int X2>
struct GET_MAX
{
    static const int RESULT = PICK_ONE<X1, X2, (X1 > X2)>::RESULT;
};

template <int X1, int X2>
struct PICK_ONE<X1, X2, true>
{
    static const int RESULT = X1;
};

template <int X1, int X2>
struct PICK_ONE<X1, X2, false>
{
    static const int RESULT = X2;
};

template <typename T, int AMOUNT, bool left>
struct SHIFT_IN_DIRECTION
{
    T exec(T value);
};

template <typename T, int AMOUNT>
struct SHIFT_IN_DIRECTION<T, AMOUNT, true>
{
    T exec(T value) { return value << AMOUNT; }
};

template <typename T, int AMOUNT>
struct SHIFT_IN_DIRECTION<T, AMOUNT, false>
{
    T exec(T value) { return value >> (-AMOUNT); }
};


// Shifts a value by a constant amount. Positive = left, negative = right
template <typename T, int AMOUNT>
struct SHIFT
{
    T exec(T value)
    {
        return SHIFT_IN_DIRECTION<T, AMOUNT, (AMOUNT < 0)>::exec(value);
    }
};

template <typename TSRC, typename TDEST, int SHL_AMT, bool IS_LEFT>
struct CONVERT_FIXED_POINT
{
    static TDEST exec(TSRC src);
};

// Convert fixed point by shifting the value left
template <typename TSRC, typename TDEST, int SHL_AMT>
struct CONVERT_FIXED_POINT<TSRC, TDEST, SHL_AMT, true>
{
    static TDEST exec(TSRC src)
    {
        // Because we're left shifting, we need to change the target type before
        // shifting. If the target type gets smaller, we havent lost anything
        // more by changing type first, but if the target type gets bigger then
        // we need the bigger type to ensure all the data is preserved in the 
        // shift
        TDEST intermediate = src;
        intermediate <<= SHL_AMT;
        return intermediate;        
    }
};

// Convert fixed point by shifting the value right
template <typename TSRC, typename TDEST, int SHL_AMT>
struct CONVERT_FIXED_POINT<TSRC, TDEST, SHL_AMT, false>
{
    static TDEST exec(TSRC src)
    {
        // Because we're right shifting, we need to shift before we change the
        // target type. If the target type gets bigger, then the early shift 
        // doesnt matter because the upper bits are independent of the src, but
        // if the target get smaller then the right shift first is important
        // in order not to lose data.
        TSRC intermediate = src;
        intermediate >>= (-SHL_AMT);
        return (TDEST)intermediate;        
    }
};

#endif /* end of include guard: TEMPLATE_UTILS_H__ */

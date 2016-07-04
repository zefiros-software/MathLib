//
//  simdMathf.h
//  math
//
//  Created by koen visscher on 6/27/16.
//
//

#ifndef simdMathf_h
#define simdMathf_h

namespace Mathf
{
    // SIMD General Algorithms
    template < typename simdTraits >
    struct _SGA
    {
        typedef typename simdTraits::vec_n_type simdvector;
        typedef typename simdTraits::vecb_n_type boolvector;
        typedef typename simdTraits::value_type valueType;
        
        static simdvector SGA_Sin_F32( const simdvector &lhs );
        static simdvector SGA_Sin_F64( const simdvector &lhs );
    };

}

/* Inspired by part
 
 Copyright (c) 2012, 2013 Erik Schnetter <eschnetter@gmail.com>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

/*
template < typename simdTraits >
typename simdTraits::vec_type Mathf::_SGA< simdTraits >::SGA_Sin_F32( const typename simdTraits::vec_type &lhs )
{
    typedef typename simdTraits::vec_type simd_vec;
    typedef typename simdTraits::vecb_type simd_vec_b;
    typedef typename simdTraits::veci_type simd_veci;
    
    typedef typename simdTraits::type_array type_array;
    typedef typename simdTraits::int_array  int_array;
    typedef typename simdTraits::bool_array bool_array;
    
    typedef typename simdTraits::value_type simd_value_type;
    typedef typename simdTraits::int_type simd_int_type;
    
    // Algorithm taken from SLEEF 2.80
    const simd_value_type PI4_A = 0.78515625f;
    const simd_value_type PI4_B = 0.00024187564849853515625f;
    const simd_value_type PI4_C = 3.7747668102383613586e-08f;
    const simd_value_type PI4_D = 1.2816720341285448015e-12f;
    
    simd_vec q =  Mathf::SIMD< simdTraits>::Rint( lhs * simd_vec(M_1_PI) );
    simd_veci iq = q.ConvertToInt();
    simd_vec d = Mathf::SIMD< simdTraits>::IfThenElse( (iq & simd_veci(simd_int_type(1))).ConvertToBool(), -lhs, lhs );

    simd_vec s = lhs * lhs;
    simd_vec u = simd_vec(2.6083159809786593541503e-06);
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(-0.0001981069071916863322258));
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(0.00833307858556509017944336));
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(-0.166666597127914428710938));
    u = Mathf::SIMD< simdTraits>::MAD(s, u * d, d);

    return u;
}

template < typename simdTraits >
typename simdTraits::vec_type Mathf::_SGA< simdTraits >::SGA_Sin_F64( const typename simdTraits::vec_type &lhs )
{
    typedef typename simdTraits::vec_type simd_vec;
    typedef typename simdTraits::vecb_type simd_vec_b;
    typedef typename simdTraits::veci_type simd_veci;
    
    typedef typename simdTraits::type_array type_array;
    typedef typename simdTraits::int_array  int_array;
    typedef typename simdTraits::bool_array bool_array;
    
    typedef typename simdTraits::value_type simd_value_type;
    typedef typename simdTraits::int_type simd_int_type;
    
    // Algorithm taken from SLEEF 2.80
    const simd_value_type PI4_A = 0.78539816290140151978;
    const simd_value_type PI4_B = 4.9604678871439933374e-10;
    const simd_value_type PI4_C = 1.1258708853173288931e-18;
    const simd_value_type PI4_D = 1.7607799325916000908e-27;

    
    simd_vec q =  Mathf::SIMD< simdTraits>::Rint( lhs * simd_vec(M_1_PI) );
    simd_veci iq = q.ConvertToInt();
    simd_vec d = Mathf::SIMD< simdTraits>::IfThenElse( (iq & simd_veci(simd_int_type(1))).ConvertToBool(), -lhs, lhs );
    
    simd_vec s = lhs * lhs;
    simd_vec u = simd_vec(-7.97255955009037868891952e-18);
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(2.81009972710863200091251e-15));
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(-7.64712219118158833288484e-13));
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(1.60590430605664501629054e-10));
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(-2.50521083763502045810755e-08));
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(2.75573192239198747630416e-06));
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(-0.000198412698412696162806809));
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(0.00833333333333332974823815));
    u = Mathf::SIMD< simdTraits>::MAD(u, s, simd_vec(-0.166666666666666657414808));
    
    return u;
}
*/

#endif /* simdMathf_h */

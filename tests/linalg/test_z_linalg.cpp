#define BOOST_TEST_MODULE Z_QTShapes_LinAlg
#include <boost/test/included/unit_test.hpp>
#include <array>
#include <initializer_list>
#include <vector>
#include <iostream>

#include "z_linalg.h"

BOOST_AUTO_TEST_CASE(Z_LinAlg)
{
    // If only QGenericMatrix could accept and return std::array...
    QGenericMatrix<4, 3, qreal> A(&std::array<qreal, 12>({
        1, 2, -1, -4,
        2, 3, -1, -11,
        -2, 0, -3, 22})[0]);
    QGenericMatrix<4, 3, qreal> B = z_linalg::rref(A);
    qreal *pb = B.data();
    std::vector<qreal> vb(pb, pb + 12);
    std::vector<qreal> va({1, 0, 0, 0, 1, 0, 0, 0, 1, -8, 1, -2});

    BOOST_TEST_MESSAGE("Reduced row echelon form");

    std::ostringstream vts; 
    if (!va.empty()) 
    { 
        // Convert all but the last element to avoid a trailing "," 
        std::copy(va.begin(), va.end()-1, 
            std::ostream_iterator<qreal>(vts, ", ")); 
  
        // Now add the last element with no delimiter 
        vts << va.back(); 
    } 

    BOOST_TEST_MESSAGE(std::string("va: ") + vts.str());

    vts.str("");
    vts.clear();
    if (!vb.empty()) 
    { 
        // Convert all but the last element to avoid a trailing "," 
        std::copy(vb.begin(), vb.end()-1, 
            std::ostream_iterator<qreal>(vts, ", ")); 
  
        // Now add the last element with no delimiter 
        vts << vb.back(); 
    } 

    BOOST_TEST_MESSAGE(std::string("vb: ") + vts.str());
    BOOST_TEST(va == vb);

    BOOST_TEST_MESSAGE("Rank");
    BOOST_TEST(z_linalg::rank(B) == 3);

   QGenericMatrix<4, 3, qreal> C(&std::array<qreal, 12>({
        1, 1, 1, 1,
        2, 2, 2, 2,
        -2, 0, -3, 22})[0]);
    BOOST_TEST(z_linalg::rank(C) == 2);
}

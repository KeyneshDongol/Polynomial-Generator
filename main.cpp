# include <iostream>
# include "Timer.h"
# include <boost/core/demangle.hpp>
# include "BasisFunctionsSets.h"
# include "Polynomial.h"

using namespace SparseFunctionals;

int main() {
    std::cout << "-> Now we start working on the basis function and sparseFunction in general.\n\n";


    const int Order = 4;
    const int Ndim = 1;

    Polynomial<Order, Ndim> testFunc;
    testFunc.printCoeff(); /// Notice, when we instantiate it without any values, the values are zero.


    /// Now, we will fill the above polynomial with some values for use to compute other methods on.
    auto coeffPointers = testFunc.firstCoeff();
    coeffPointers[0] = 0;
    coeffPointers[1] = 2;
    coeffPointers[2] = 2;
    coeffPointers[3] = 3;
    coeffPointers[4] = 4;
    std::cout << "\n\n";
    testFunc.printCoeff();



    std::cout << "\ntestFunc is of type: \n->" << boost::core::demangle(typeid(decltype(testFunc)).name()) << "\n\n";
    std::cout << "\ncoeffPointer is of type: \n->" << boost::core::demangle(typeid(decltype(coeffPointers)).name()) << "\n\n";

    std::cout << testFunc.coeffPtr << "\n\n"; /// Address of our polynomial.

    std::cout << "The roots are: \n"<< testFunc.roots();

    std::cout << "\nThe real roots are: \n" << testFunc.realRoots() ;
    {
        Timer timer("testFunc"); /// Simple class method to profile code
        testFunc.realRoots();
    }

    /// In fact, we can do this for polynomials of any dimensions and order as we show below

    const int numVar = 3;
    Polynomial<Order , numVar> anotherFunc;
    std::cout << "Number of basis functions: " << anotherFunc.numBasisFunction() << "\n\n";
    anotherFunc.printCoeff();
    const int nDataPoint = 50;
    Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic> v = Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic>::Random(nDataPoint, numVar);
    Eigen::Array<double,Eigen::Dynamic,Eigen::Dynamic> y = 3.1*v.col(0) + 2.*v.col(1) + 3.*v.col(2)*v.col(1) + 1.2;
    anotherFunc(v);
    std::cout << "\nAnd the fitting error is: " << anotherFunc.fitData(v, y)<< "\n";
    anotherFunc.printCoeff(); /// The polynomial is now of form 3.1 x + 2 y + 3 y z + 1.2
    /*!
     * If the fitting works well the fitted coefficients should be very close to the ones above.
     * anotherFunc.fitData(v, y) calculates the coefficient of bla such that it approximates the passed points the best.
     * The return value is the fitting error. with the values above the fitting error should be very small
     * If instead of using a polynomial expression, we had used a more generic function to construct y, the error would be finite, since there is no way
     * a polynomial can approximate exactly a generic function
     */

    /// In fact we can even expressive the above polyomial as funciton over one variable by the function
    Eigen::Array<double, numVar, 1> vectorA = Eigen::Array<double, numVar, 1>::Ones();
    Eigen::Array<double, numVar, 1> vectorB = Eigen::Array<double, numVar, 1>::Ones();

    Polynomial<Order, 1> smallPoly = anotherFunc.substitute(vectorA, vectorB);
    std::cout <<"\n\n";
    smallPoly.printCoeff(); /// We have went from a polynomial over 3 variables ot that of 1 variable.



    return 0;
}

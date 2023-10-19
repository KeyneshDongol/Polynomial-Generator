//
//  Created by Keynesh Dongol on 19/9/23.
//

#pragma once

#include "SparseFunction.h"
#include "BasisFunctionsSets.h"
#include <boost/core/demangle.hpp>

namespace SparseFunctionals {

    template <int order, int nVar, typename ScalarType = double>
    struct Polynomial: public SparseFunction<order, nVar, TaylorBasis, ScalarType> {

        using SparseFunction<order, nVar, TaylorBasis, ScalarType>::coeffPtr;

    public:

        //~~~~ Substituition
        template<typename Derived1, typename Derived2>
        Polynomial<order, 1> substitute (const Eigen::ArrayBase<Derived1>& vectorA, const Eigen::ArrayBase<Derived2>& vectorB) {
            assert(vectorA.rows() == nVar && vectorA.cols() == 1); assert(vectorB.rows() == nVar && vectorB.cols() == 1);

            //~~~ Necessary variables to be constructed
            Eigen::Array<ScalarType, order + 1, 1> wValues = Eigen::Array<ScalarType, order + 1, 1>::LinSpaced(order + 1, 0.0, 1.0);
            Polynomial<order, 1, ScalarType> smallPoly;

            //~~~ Calculations
            auto bigXValue = (vectorA.matrix() * wValues.matrix().transpose()).array().colwise() + vectorB;
            smallPoly.fitData(wValues, (*this)(bigXValue.transpose()));

            return smallPoly;
        }

        auto  roots() requires (nVar==1) {
            Eigen::EigenSolver<Eigen::Matrix<ScalarType, Eigen::Dynamic, Eigen::Dynamic>> solver(buildCompanionMatrix());
            return solver.eigenvalues();
        }


        auto  realRoots() requires (nVar==1) {
            Eigen::Matrix<std::complex<ScalarType>,Eigen::Dynamic, 1> roots = (*this).roots(); //type -> Eigen::Matrix<std::__1::complex<double>, -1, 1, 0, -1, 1>
            const int size = roots.size();
            Eigen::VectorXd realRoots; //type -> Eigen::Matrix<double, -1, 1, 0, -1, 1>
            realRoots.resize(size);
            size_t nReal = 0;
            for (size_t i{}; i != size; ++i){
                if(roots(i).imag() == 0)
                    realRoots(nReal++) = roots(i).real();
            }
            realRoots.conservativeResize(nReal);
            return realRoots;
        }


    private:
        //~~~~ Companion Matrix
        auto buildCompanionMatrix() const requires (nVar==1) {

            size_t skipped = 0;
            auto incrementCounterIfNotMet = [&skipped](ScalarType arr[]){ if (arr[skipped] < std::numeric_limits<ScalarType>::min()) { skipped++; } };
            incrementCounterIfNotMet(coeffPtr);

            size_t degree = order - skipped;

            Eigen::Matrix<ScalarType, Eigen::Dynamic, Eigen::Dynamic> companionMatrix(degree, degree);
            companionMatrix.setZero();
            // Fill the subdiagonal with ones
            for (size_t i = 1; i != degree; ++i) {
                companionMatrix(i, i - 1) = 1.0;
            }
            // Set the first row of the companion matrix using SparseFunction::Polynomial coefficient
            for (size_t i{}; i != degree; ++i) {
                companionMatrix(i , degree - 1) = - (coeffPtr[order - i]) / (coeffPtr[skipped]);
            }

            return companionMatrix;
        }

    };

} // namespace SparseFunction


//
// Created by Keynesh Dongol on 13/8/23.
//

#pragma once

#include <Eigen/Dense>

namespace SparseFunctionals {

    template <int order> struct TaylorBasis{
        template <typename Derived> static auto basisF(const Eigen::ArrayBase<Derived>& x){
            return x * TaylorBasis<order-1>::basisF(x);
        }
    };
    template <> struct TaylorBasis<0>{
        template <typename Derived> static auto basisF(const Eigen::ArrayBase<Derived>& x){
            return Eigen::ArrayBase<Derived>::Constant(x.rows(), x.cols(), 1);
        }
    };
    template <> struct TaylorBasis<1>{
        template <typename Derived> static auto basisF(const Eigen::ArrayBase<Derived>& x){
            return x.matrix().array();
        }
    };

    template <int order> struct FourierBasis{
        template <typename Derived> static auto basisF(const Eigen::ArrayBase<Derived>& x){
            return sin(3.14159265358979323846 * order * x.matrix().array());
        }
    };

    template <> struct FourierBasis<0>{
        template <typename Derived> static auto basisF(const Eigen::ArrayBase<Derived>& x){
            return Eigen::ArrayBase<Derived>::Constant(x.rows(), x.cols(), 1);
        }
    };

} // namespace SparseFunctionals





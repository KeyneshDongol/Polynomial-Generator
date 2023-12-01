# Polynomial-Generator
This package is designed to generate polynomials of various forms during compile time by just giving the order and the dimensions of the polynomial. Here, we provided methods to substitute the polynomial and to find its roots. Originally hard-coded (as seen by the other github project) this provides the benefit of being flexible and since it's generated during run time, the package as a whole is faster. 


The explanation of the method is listed below:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------
We assume that we can make a spectral discretisation of a 1 variable function using basis functions of increasing order from 0 to a maxOrder

The most straightforward way of generating basis functions for a multivariate case is to construct a Cartesian product of the single variable
basis functions. This is however wasteful and scales very badly with the number of dimensions.

We then construct basis functions for the multivariate case by taking products of univariate basis functions with a total order not exceeding
a predetermined maximum total order.

The simplest example is with polynomial basis functions. Let us assume that we use basis functions<br />
```f_0(x) = 1; f_1(x) = x; f_2(x) = x^2; f_3(x) = x^3 ```
where the subscript is the order

We can construct 2 variate basis functions as <br />
```
g_00(x,y) = f_0(x)*f_0(y) 
g_01(x,y) = f_0(x)*f_1(y);  g_10(x,y) = f_1(x)*f_0(y) 
g_02(x,y) = f_0(x)*f_2(y);  g_11(x,y) = f_1(x)*f_1(y);  g_20(x,y) = f_2(x)*f_0(y)  
etc
```

We include all the basis functions up to a maximum total order is fixed.

The object representing a discretised function has to contain all the coefficients for all the basis functions above.
The structure is built by nesting objects.

Let us suppose that we need to discretise a function of 3 variables with a maximum degree of 2
The top level will be of type
   sparseFunctionStruct<totalOrder = 2, maxOrder = 2, nVariables = 3, basisFunctType>    (notice that we will drop the last template parameter)
   
Such object will contain all sub-objects for which 

1. there are at least nVariables variables,
2. the first variable has at most order maxOrder
3. the total order is at most totalOrder
                                                   
We split the basis functions with those characteristics into two groups:
   1. the ones where the first variable has an order of exactly maxOrder
   2. and the ones where the first variable has an order of maxOrder-1 or lower
   
Both those groups have to contain several basis fucntions and therefore coefficients. They will be objects containing further objects

The structure above is implementedby making the mentioned object contain two objects: <br />
* "top" of type <br />
          ```sparseFunctionStruct<totalOrdertop = totalOrder - maxOrder, maxOrdertop = totalOrder - maxOrder , nVariablestop = nVariables -1>``` <br />
               Notice how this object will be in charge of handling one less variable. The remaining variables can have a total order which is 
               the original one decreased by the order that the first variable has <br />
and <br />
* "rest" of type <br />
          ```sparseFunctionStruct<totalOrderrest = totalOrder , maxOrderrest = maxOrder - 1, nVariablesrest = nVariables> ```<br />
               This object instead will contain all the subobjects for which the first variable has at most order maxOrder - 1 <br />
This nesting structure ends when the order of the last variable is determined. In that case the innermost object stores the value of the coefficient.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

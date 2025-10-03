import numpy as np 
from scipy.optimize import minimize

def objective_function(x):
    return x**2 + 10*np.sin(x)

result = minimize(objective_function, x0=0)
print(result)


# LIP

from scipy.optimize import linprog
c = [2, -1] # Objective function coefficients
# Coefficients of inequality constraints (Ax <= b)
A = [[-1, 2], [1, 1]]
b = [4, 5]
# Bounds for variables
x0_bounds = (0, None)
x1_bounds = (0, None)
result = linprog(c, A_ub=A, b_ub=b, bounds=[x0_bounds, x1_bounds]) # Solve the linear programming problem
print("Optimal solution:", result.x)
print("Optimal value:", result.fun)


# Integration: SciPy includes functions for numerical integration, making it easy to compute definite integrals.

from scipy import integrate
result, error = integrate.quad(lambda x: x**2, 0, 1)  # mind the lambda function here
print(result)


#  Signal Processing: If you are working with signals, images, or time-series data, SciPy provides tools for signal processing, such as filtering, convolution, and Fourier analysis.

from scipy import signal
# Example: Butterworth low-pass filter
b, a = signal.butter(N=4, Wn=0.2, btype='low', analog=False)  


# LAL: SciPy builds on NumPy's linear algebra capabilities and extends them with additional functions for sparse matrix operations, eigenvalue problems, and more. 

from scipy import linalg
# Solve a linear system of equations
A = np.array([[1, 2], [3, 4]])
b = np.array([5, 6])
x = linalg.solve(A, b)  


# statistics: SciPy provides statistical functions for common tasks such as hypothesis testing, descriptive statistics, and probability distributions. 

from scipy import stats
# Example: t-test
data1 = np.random.normal(0, 1, size=100)
data2 = np.random.normal(0.5, 1, size=100)
t_stat, p_value = stats.ttest_ind(data1, data2)
print(t_stat, p_value)
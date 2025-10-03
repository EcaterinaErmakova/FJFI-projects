import numpy as np 

# create a 1D array from a list
a = np.array([1, 2, 3, 4, 5]) 

# create a 2D array from lists
b = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])

# create a 2D array with shape (3, 4) filled with zeros 
a = np.zeros((3, 4)) 

# create a 1D array with shape (5) filled with ones
b = np.ones(5) 

# create a 3D array with shape (2, 3, 4) filled with random values
c = np.random.rand(2, 3, 4)


# create an array of integers
a = np.array([1, 2, 3], dtype=np.int32)
print(a)

# create an array of floats
b = np.array([1.0, 2.0, 3.0], dtype=np.float64)
print(b)
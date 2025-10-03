# lambda arguments: expression
xyz = lambda x, y: x + y
result = xyz(5, 10)
print(result) # Output: 15

my_list = [(2, 'b'), (1, 'c'), (3, 'a')]
sorted_list = sorted(my_list, key=lambda x: x[1])
print(sorted_list) # Output: [(1, 'a'), (2, 'b'), (3, 'c')]

def get_key(t):
    return t[0]
my_list = [(2, 'b'), (1, 'c'), (3, 'a')]
sorted_list = sorted(my_list, key=get_key)
print(sorted_list) # Output: [(1, 'a'), (2, 'b'), (3, 'c')]

# map()
numbers = [1, 2, 3, 4, 5]
squares = list(map(lambda x: x**2, numbers))
print(squares) # Output: [1, 4, 9, 16, 25]

# filter()
numbers = [1, 2, 3, 4, 5]
even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
print(even_numbers) # Output: [2, 4]

# reduce()
from functools import reduce
numbers = [1, 2, 3, 4, 5]
product = reduce(lambda x, y: x*y, numbers)
print(product) # Output: 120

# zip()
numbers = [1, 2, 3]
letters = ('a', 'c', 'b')
zipped = [f'{x[0]}/{x[1]}' for x in zip(numbers, letters)]
print(zipped) # Output: [(1, 'a'), (2, 'b'), (3, 'c')]

# itertools

# count(start=0, step=1)
from itertools import count
for i in count(1, 2):
    print(i)
    if i==11:
        break

# cycle(iterable): repeats the elements of the given iterable indefinitely.
from itertools import cycle
colors = cycle(['red', 'green', 'blue'])
for _ in range(5):
    print(next(colors))

# repeat(element, times=None): repeats the specified element a specified number of times or indefinitely if times is not provided.
from itertools import repeat
for i in repeat('Hello', 3):
    print(i)

# chain(iterable1, iterable2, ...): chains together multiple iterables into a single iterable. 
from itertools import chain
numbers = chain([1, 2, 3], [4, 5, 6])
for num in numbers:
    print(num)

# combinations(iterable, r): generates all possible combinations of length r from the elements of the iterable. 
from itertools import combinations
colors = ['red', 'green', 'blue']
for combo in combinations(colors, 2):
    print(combo)  
'''
Output:
('red', 'green')
('red', 'blue')
('green', 'blue')
'''

# permutations(iterable, r=None): generates all possible permutations of length r from the elements of the iterable. 
from itertools import permutations
numbers = [1, 2, 3]
for perm in permutations(numbers):
    print(perm)  
''' 
Output:
(1, 2, 3)
(1, 3, 2)
(2, 1, 3)
(2, 3, 1)
(3, 1, 2)
(3, 2, 1)
'''

# product(*iterables, repeat=1): computes the Cartesian product of input iterables. 
from itertools import product
dice = product(range(1, 7), repeat=2)
for roll in dice:
    print(roll)
'''
Output:
(1, 1)
(1, 2)
(1, 3)
(1, 4)
(1, 5)
(1, 6)
(2, 1)
(2, 2)
(2, 3)
(2, 4)
(2, 5)
(2, 6)
(3, 1)
(3, 2)
(3, 3)
(3, 4)
(3, 5)
(3, 6)
(4, 1)
(4, 2)
(4, 3)
(4, 4)
(4, 5)
(4, 6)
(5, 1)
(5, 2)
(5, 3)
(5, 4)
(5, 5)
(5, 6)
(6, 1)
(6, 2)
(6, 3)
(6, 4)
(6, 5)
(6, 6)
'''
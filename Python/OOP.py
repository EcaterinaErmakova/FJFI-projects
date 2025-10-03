# Define a class
class Car:
    def __init__(self, make, model, year):
        self.make = make
        self.model = model
        self.year = year

    def get_make(self):
        return self.make

    def get_model(self):
        return self.model

    def get_year(self):
        return self.year

    def __str__(self):
        return f"{self.make} {self.model} ({self.year})"

# Create an object of the class
car1 = Car("Toyota", "Corolla", 2018)

# Access properties and methods of the object
print(car1.get_make()) # Output: Toyota
print(car1.get_model()) # Output: Corolla
print(car1.get_year()) # Output: 2018
print(car1) # Output: Toyota Corolla (2018)



class Circle:
    def __init__(self, r):
        self.r = r
    def area(self):
        return 3.14*((self.r)**2)
    def perimeter(self):
        return self.r * 2 * 3.14
    def resize(self, factor):
        self.r*factor
    
class Square:
    def __init__(self, a):
        self.a = a
    def area(self):
        return (self.a)**2
    def perimeter(self):
        return 4*self.a
    def resize(self, factor):
        self.a*factor
    
class Rectangle:
    def __init__(self, a, b):
        self.a = a
        self.b = b
    def area(self):
        return (self.a)*(self.b)
    def perimeter(self):
        return 2*(self.a) + 2*(self.b)
    def resize(self, factor):
        self.a *= factor
        self.b *= factor
    

 # Create some shapes
circle = Circle(5)
square = Square(10)
rectangle = Rectangle(10, 5)

# Get the area and perimeter of each shape
print("Circle area:", circle.area()) # Output: Circle area: 78.53981633974483
print("Circle perimeter:", circle.perimeter()) # Output: Circle perimeter: 31.41592653589793
print("Square area:", square.area()) # Output: Square area: 100
print("Square perimeter:", square.perimeter()) # Output: Square perimeter: 40
print("Rectangle area:", rectangle.area()) # Output: Rectangle area: 50
print("Rectangle perimeter:", rectangle.perimeter()) # Output: Rectangle perimeter: 30

# Resize the shapes
circle.resize(2)
square.resize(0.5)
rectangle.resize(1.5)

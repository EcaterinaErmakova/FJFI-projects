# Decorator pattern, where function returns a function
def log_function_call(func):
    def wrapper(*args, **kwargs):
        print(f"Calling function {func.__name__} with arguments {args} and keyword arguments {kwargs}.")
        result = func(*args, **kwargs)
        print(f"Function {func.__name__} finished execution with result: {result}.")
        return result
    return wrapper

@log_function_call
def add_numbers(a, b):
    return a + b

@log_function_call
def multiply_numbers(a, b):
    return a * b

# Calling the decorated functions
sum_result = add_numbers(3, 4)
product_result = multiply_numbers(b=5, a=2)
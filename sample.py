from typing import List, Dict, Set, Generator, Union, Optional, Type, TypeVar

# FunctionDef, arguments, Return, Expr, Constant, Name, List, Tuple
def my_function(a: int, b: str, *args, c: float = 3.14, **kwargs) -> List[Union[int, str]]:
    print("Hello, world!")
    return [a, b, *args, c, *kwargs.values()]

# ClassDef, Assign, Attribute, Subscript, Slice, BinOp, UnaryOp, BoolOp, Compare, IfExp
class MyClass:
    class_var: List[int] = [1, 2, 3]
    
    def __init__(self, value: int) -> None:
        self.instance_var = value + 1 if value < 0 else -value
    
    def instance_method(self) -> bool:
        return self.instance_var % 2 == 0 and not (self.instance_var > 10 or self.instance_var < -10)
    
    @classmethod
    def class_method(cls) -> List[int]:
        return cls.class_var[1:-1]

# TypeAlias, type_params
MyUnion = Union[int, float, str]

# AugAssign, Raise
def aug_assign_and_raise(value: MyUnion) -> None:
    result = 0
    result += value  # type: ignore
    raise ValueError("Something went wrong!")

# For, While, If, Break, Continue, Pass
def loops_and_conditionals() -> None:
    for i in range(10):
        if i % 2 == 0:
            continue
        elif i == 7:
            break
        else:
            pass
        print(i)
    
    i = 0
    while i < 5:
        print(i)
        i += 1

# With
def context_managers() -> None:
    with open("file.txt", "r") as f:
        content = f.read()
        print(content)

# Match
def pattern_matching(value: Union[int, str, List[int], Dict[str, int], None]) -> None:
    match value:
        case int(x):
            print(f"Integer: {x}")
        case str(x):
            print(f"String: {x}")
        case [x, y, *rest]:
            print(f"List: {x}, {y}, {rest}")
        case {"a": x, "b": y, **rest}:
            print(f"Dict: {x}, {y}, {rest}")
        case None:
            print("None")
        case _:
            print("Something else")

# Try, TryStar, ExceptHandler, Finally
def exception_handling() -> None:
    try:
        result = 1 / 0
    except ZeroDivisionError as e:
        print(f"Caught exception: {e}")
    except Exception:
        print("Caught generic exception")
    else:
        print("No exception occurred")
    finally:
        print("Finally block")

# Assert
def assertions(value: int) -> None:
    assert value > 0, "Value must be positive"

# Import, ImportFrom, alias
import math
from typing import List as ListType

# Global, Nonlocal
global_var = 0

def outer_function() -> None:
    nonlocal_var = 1
    
    def inner_function() -> None:
        global global_var
        nonlocal nonlocal_var
        global_var += 1
        nonlocal_var += 1

# Delete
my_list = [1, 2, 3]
del my_list[1]

# Lambda, NamedExpr
square = lambda x: (y := x ** 2)

# Dict, Set, ListComp, SetComp, DictComp, GeneratorExp
my_dict = {x: x**2 for x in range(5)}
my_set = {x for x in range(10) if x % 2 == 0}
my_list_comp = [x * 2 for x in range(5)]
my_set_comp = {x * 3 for x in range(5)}
my_dict_comp = {x: x ** 2 for x in range(5)}
my_generator = (x ** 2 for x in range(5))

# Yield, YieldFrom
def generator_function() -> Generator[int, None, None]:
    yield 1
    yield from [2, 3, 4]

# Call, FormattedValue, JoinedStr
def formatted_string(name: str, age: int) -> str:
    return f"My name is {name} and I'm {age} years old."

# Starred
def star_args(*args: int) -> None:
    print(args)

star_args(*(1, 2, 3))

# TypeVar
T = TypeVar("T")

def generic_function(value: T) -> T:
    return value
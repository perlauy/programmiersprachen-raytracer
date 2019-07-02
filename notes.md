# Notes

## Inheritance
Using a class as a base is equivalent to defining an unnamed object of that class (its constructor is called and its member variables instantiated). Consequently, a class must be defined in order to be used as a base.

```
class Base; // declaration only, not definition

class Derived : public Base { // error: Base is not defined
  //...
};
```

## Abstract class
Defines an abstract type **which cannot be instantiated**, but can be used as a base class.
It has *at least* one **pure virtual** function (either defined in itself, or inherited), with the following syntax:

```
virtual type f() = 0;
```

No objects of an abstract class can be created (except for base subobjects of a class derived from it) and no non-static data members of an abstract class can be declared. 

Abstract types cannot be used as parameter types, as function return types, or as the type of an explicit conversion (note this is checked at the point of definition and function call, since at the point of function declaration parameter and return type may be incomplete)

Pointers and references to an abstract class can be declared. 

```
struct Abstract {
    virtual void f() = 0; // pure virtual
}; // "Abstract" is abstract
 
struct Concrete : Abstract {
    void f() override {} // non-pure virtual
    virtual void g();     // non-pure virtual
}; // "Concrete" is non-abstract
 
struct Abstract2 : Concrete {
    void g() override = 0; // pure virtual overrider
}; // "Abstract2" is abstract
 
int main()
{
    // Abstract a; // Error: abstract class
    Concrete b; // OK
    Abstract& a = b; // OK to reference abstract base
    a.f(); // virtual dispatch to Concrete::f()
    // Abstract2 a2; // Error: abstract class (final overrider of g() is pure)
}
```

(https://en.cppreference.com/w/cpp/language/abstract_class)

### Why can it not be instantiated?

(https://stackoverflow.com/questions/2091426/why-cant-we-create-objects-for-an-abstract-class-in-c)


## virtual function
They allow the programmer to declare functions in a base class that can be redefined in each derived class. **The compiler and linker will guarantee the correct correspondence between objects and the functions applied to them.**

## virtual & override
`virtual` specifies that a non-static member function is virtual and supports dynamic dispatch. It may only appear in the decl-specifier-seq of the initial declaration of a non-static member function (i.e., when it is declared in the class definition). 

Virtual functions are member functions whose behavior **can be overridden** in derived classes. As opposed to non-virtual functions, **the overridden behavior is preserved even if there is no compile-time information about the actual type of the class**. If a derived class is handled using pointer or reference to the base class, a call to an overridden virtual function would invoke the behavior defined in the derived class. This behavior is suppressed if the function is selected using qualified name lookup (that is, if the function's name appears to the right of the scope resolution operator :: `Base::f()` ). 

For every virtual function, there is the final overrider, which is executed when a virtual function call is made. A virtual member function vf of a base class Base is the final overrider unless the derived class declares or inherits (through multiple inheritance) another function that overrides vf.

(https://en.cppreference.com/w/cpp/language/virtual)

Except when specifying the version of the function (::) the overriding function is chosen as the most appropriate for the object for which it is called. Independently of which basic class is used to access an object (static type), we always get the same function when we use the virtual function call mechanism (dynamic). 
```
class Shape {
  //...
  void print() const { cout << "SHAPE!"; }
}
class Sphere : public Shape {
  //...
  void print() const { cout << "SPHERE!";}
}

Shape* s = new Sphere();
// static type: Shape  -  Dynamic type: Sphere

s->print(); // Prints "SHAPE!" -> From static type

```

But: 
```
class Shape {
  //...
  virtual void print() const { cout << "SHAPE!"; }
}
class Sphere : public Shape {
  //...
  void print() const override { cout << "SPHERE!";}
}

Shape* s = new Sphere();
// static type: Shape  -  Dynamic type: Sphere

s->print(); // Prints "SPHERE!" -> From dynamic type

```

A type with virtual functions is called a *(run-time) polymorphic type*.
Every function that overrides a virtual function becomes too `virtual`. The keyword **could be written** in the derived class, but instead it is preferred to use the keyword `override`.


#### Override / Hide

```
struct B0 {
  void f(int) const;
  virtual void g(double);
}

struct D : B0 {
  void f(int) const;  // B0::f() is not virtual, so it's being hidden, not overriden
  void g(int);        // different argument type, so just hiding
  virtual int h();    // creates a new virtual function
}
```

The *contextual* keyword `override` helps to clarify the developer's intent (not necessary, but it may also help throwing errors when compiling). It may only be used in the declaration of the member function, and *not* in the out-of-class definition.

---

**`virtual`**: The function may be overriden

**`=0`**: The function must be virtual and *must* be overriden

**`override`**: The function is meant to override a virtual function in a base class 

**`final`**: The function is not meant to be overriden.

`final` may also be applied to a class, meaning it won't be able to be derived from. As with override, it cannot be used in out-of-class definitions.

## Aufgabe 5.7
### Static vs Dynamic type from a variable

## Destructor
If the destructor of the base class is not virtual, then the derived class should not have secondary structures and resources for the freestore, since their destructor could not be called.
As with the other member functions, if not declared virtual, the destructor of the static type will be called. So in the following case, the derived destructor (which may delete additional data) could not be called:

```
class Base 
{
    // some virtual methods
};

class Derived : public Base
{
    ~Derived()
    {
        // Do some important cleanup
    }
};

Base *b = new Derived();
// use b
delete b; // Here's the problem!

```

Overriding a destructor:
```
class Base 
{
  public:
    // some methods...
    virtual ~Base() {}
};

class Derived : public Base
{
    ~Derived() override
    {
        // ...
    }
};

```
(https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors)


## Aufgabe 5.9
### Class hierarchy vs. Object hierarchy
Class hierarchy refers to classes inheriting and being derived from others. This is part of the program design. But at run-time, once objects are instantiated, there is no real hierarchy.
Object hierarchy refers to the structure of data inside each object; an object of certain type may contain data as objects of another type, and so on. So there is a certain "hierarchy" in the way the data is structured.
### Class diagram vs. Object diagram
A Class Diagram will show what the Objects in your system consist of (members) and what they are capable of doing (methods). -> Design stage
In contrast, an Object Diagram will show how objects in your system are interacting with each other at some point in time, and what values those objects contain when the program is in this state. -> Run-time
(https://stackoverflow.com/questions/19282748/what-is-the-difference-between-a-class-diagram-vs-an-object-diagram)
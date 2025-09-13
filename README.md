# JTracer (2006)

This is a ray tracer I wrote in C++ some time around 2006. I believe this is
the second ray tracer I wrote as it has a multi-threaded design, which was not
true of my very first attempt.

It implements the following features:

- Simple Windows graphical interface
- Multithreaded design with separate UI and render threads
- Perspective projection
- Point lighting
- Sphere and plane primitives
- Ambient, diffuse, and specular lighting with shadows and reflections.

This project was then abandoned in favour of an improved design that would
allow for improved scene description and support for matrix-based
transformations.

## Building

There is no build system included in my archives, but from what I can tell it
was compiled with Borland C++ Compiler v5.5 using a command something like:

    bcc32 -tW *.cpp

## Disclaimer

As of 2025 this code may serve as a useful reference for how a simple ray
tracer may be implemented algorithmically, however I would not recommend it as
a good example from a software design standpoint.

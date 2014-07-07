TexGen
=======

Overview
-------

TexGen is a small language that can be used to generate images.
TexGen scripts are authored in .tgs files and are compiled to a "bytecode" intermediate state
where the instructions are optimized for size.
At runtime, the interpreter / VM runs the compiled instructions and produces the desired images.

Goals
-------
* A simple to use and powerful language for generating images
* A size efficient format for storing compiled instructions
* Can be easily integrated into existing projects

# GMS
Gang's Makefile build System

GMS is a Project Descriptor System that let you describe your Project in a platform-independent and IDE-independent way. This
is a Yet Another CMake's Type program. 

## Brief Introduction to GMS 

GMS uses its own language. This language is very simple : 

- A Context is created when analysing the main file.
- A Subcontext is created by default.
- A Namespace can contains static Functions and Variables. 
- An Objects can contains member/static Functions, and Variables. An Object is also a Variable.
- A Function execute its code.

Basically, the language is defined as many layers. Each layer correspond to a Word. An instruction is a Sentence as : 

```
Var myproject CreateProject "My Project"
```

This Sentence has a beginning ( "Var" ) . This Word can be found in "GMS -> Functions" . It has two arguments : 
- "myproject" : This is the name of the variable. You can access later this variable using this name.
- "CreateProject" : This is a function which creates a Project object with given name and returns the object.

As "CreateProject" has one argument, the Analyser will also take the next Word ( " "My Project" " ) to take the name of the
Project. The Function is then executed and the returned value is the second argument of "Var" . 

The function "Var" can then be called. Its arguments are packed together and its code is executed. It is exepected that this
function register the new variable in the local subcontext. ( If we have no subcontext change, this is the main one. ) 



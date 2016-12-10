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

## The Analysing Process of a ".gms" file

The file is first processed using a 'WordPeeker' class. This objet skip the comments lines ( lines beginning with "//" ) , and
divides the file in Words. A Word can be : 
- A String : begins and ends with " .
- A Node : everything that is not a String .

The Interpreter has then the task to analyse the file. This is done sequentially, Word after Word, in the first-in-first-out
order. Once this task finished, a NodeTree is build from the Context point of view. 

In order to create project files , or even compile the project , the user has to choose the NodeTreeUser . This NodeTreeUser
is generally a plugin. This object will have the task to take the data in the tree, and to create the appropriate files or
do the appropriate actions ( which can even be directly compiling the project ) .

## GMS Command Line

The GMS Program has the following options : 
- '-f' : A '.gms' file to analyse.
- '-t' : A '.gmstree' file to use.
- '-u' : The name of the NodeTreeUser to use.
- '-ot' : Output the NodeTree corresponding to the given file. This file will have the same name with '.gmstree' as extension.
- '-cf' : Set a specific configuration file.

The NodeTree is System-dependent. You cannot copy the '.gmstree' file from one system to another. Generating the '.gmstree' 
and using this file permit to skip the analysing part and building the project quicker. Please note that you have to update
this file if you add or remove files from the project.

## GMS Options file

In your directory, you can create a file named 'gms.conf' . This is the default name for GMS 's configuration files. You can 
also use the '-cf' option. 

This file as very simple 'conf' language : 
```
nameofvariable=valueofvariable
```

Those Variables can be : 
- inputfile : replace the '-f' option.
- treefile : replace the '-t' option.
- user : replace the '-u' option.



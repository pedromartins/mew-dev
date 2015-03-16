Guys and Gals!

Welcome to the Neubau project.
This source tree is built based on new principles that I find may increase the
ease of use of the source-tree for the mew-robotics project that we had.

# Contents #
  1. Introduction
  1. Prerequisites for building
  1. Building using CMake!
> > - configuring CMakelists.txt files
  1. Use CTest!
  1. Use CppUnit!
  1. Do everything with one command!
  1. Previously encountered problems


# Introduction #


Neubau is the **official** and current mew-dev software team source-tree.

Older code can be found in the `svn/mew-dev` tree (which I always had called Maple :P).

# Prerequisites for building #
To build Neubau, you will need:
  * `svn` Subversion control system client
  * `cmake` (bundled with it, `ctest`) A build makefile management system
  * `make` A build management system
  * `g++` A C++ compiler
  * cppunit (for some unit tests to be compiled)

The build system we're using is called CMake. It comes with a testing tool called
CTest.

## Step by Step... ##
1) Check out the source tree
Run the following command

```
svn checkout https://mew-dev.googlecode.com/svn/neubau/ <dir-name> --username <yourusername>
```

where `dir-name` is the directory you want to have the source-tree under
and `<yourusername>` is your Google Code username

2) Build the project
The project consists of different types of binaries: libraries, and test applications. All of these are built at the same time by CMake when it is invoked. Read on to find out how to build the project with CMake.

3) Edit files
Editing source files can be done by any IDE or text-editor of choice. Eclipse is recommended.

After editing code, to upload your changes onto the SVN repository, you will need to **commit**. For further information about how to do this, see the [SVNHowTo](SVNHowTo.md) page.


# Building using CMake! #
With configuration files already in the source-tree, building Neubau cannot be easier.
CMake GENERATES makefiles. It looks at the CMakeLists.txt files in the directory
tree which describes to CMake the targets that need to be built, and it chugs
out a lot of configuration files in a BUILD TREE.

To build everything related to this project, simply follow the following steps
on a Linux system:

```
cd build  # enter our build directory.
cmake ../ # run cmake on the source directory (which is the parent of the build dir)
make      # run the usual 'make' on the generated makefiles!
```

If your shell complains that you don't have cmake installed, run
```
sudo apt-get install cmake
```
...
Hopefully you won't get any errors on the make. If you get errors from CMake,
stop, fix your CMakeLists.txt files and then try cmake again.
make then builds all the binaries into the build/ folder.


## Configuring CMakeLists.txt files ##
CMakeLists.txt are like meta-makefiles: they describe how CMake should make
its makefiles. Consult the CMake wiki, or other CMakeLists files, or me,
to see how CMakeLists.txt work.


# Using CTest! #
CTest is a module of CMake that runs tests after making, and reports which tests
failed and which tests succeeded.

Test programs (or test executables, or test CASES) are normal programs that have their
own main() functions as per any C++ file, and they return 0 on test PASS
and returns 1 on test FAILURE.

Unlike traditional test tools, there's no notion of a test suite. We simply put
test cases in their separate directories, as needed.

The 'test' directory should look something like this:

```
test/
 |- core
 |    |
 |    +- TestVector2d.cpp  // Tests the Vector class
 |
 |- experimental
 |    |
 |    +- ...
 | ...
```

Each test case should be named 'Testxxx.cpp', with a fairly descriptive file name.


# Using CppUnit! #
CTest provides us a means of running many tests, but doesn't give us many means
of making meaningful error messages, so it is advised that you use some sort of
unit testing library such as CppUnit.

# Do Everything with One Command! #
For your convenience, I have created a script that will invoke
`cmake`, `make` AND `ctest` one after another.
Just run:
```
cd build
./buildall.sh
```

If it for some reason says 'Permission denied', then:
```
chmod a+x buildall.sh
```
to grant execution permissions for the script.
## Previously encountered problems ##
**Both CMake AND Eclipse gives linker errors due to the fact that files are

> named .c. Name ALL files .cpp despite them being C-files, please!**
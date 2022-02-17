<center>CSC333 C Bootcamp assignments</center>

<!-- TOC -->

- [Introduction](#introduction)
- [Task Overview](#task-overview)
- [Setup](#setup)
- [Getting Started](#getting-started)
    - [Cloning the repositories.](#cloning-the-repositories)
    - [Compiling and running the code](#compiling-and-running-the-code)
- [Assignment 1: Modifying the code](#assignment-1-modifying-the-code)
    - [Submit:](#submit)

<!-- /TOC -->
# Introduction

The goals of this in-class assignment are as follows:

* introduce you to git, gitlab, and how we'll be using it in this class
* introduce you to C programming, including editing, compiling and debugging code
* introduce you to writing Markdown documents

The assignments include:
* A fun little brute-force algorithm (although, as it turns out, much too simple) for factorization.
* A larger vector-multiplication algorithm, to get you used to operating on arrays of data.
* A linked list algorithm to get you *really* used to pointers

# Task Overview

- [ ] Complete Setup (clone repos)
- [ ] Assignment 1: Factorization
- [ ] Assignment 2: Vector Multiplication
# Setup

What you'll need for this assignment:

* a terminal app (Terminal on MacOS or puTTY on windows)
* git installed on your computer (via XTools on MacOS, or GitBash on Windows)
* ssh installed on your computer (pre-installed on MacOS and I think on Windows?)
* I am assuming a basic knowledge of the UNIX Command line.  If you are new to the command line, I'll be around to help you in class.  You may also find [this Unix Command Line Cheat Sheet useful](https://files.fosswire.com/2007/08/fwunixref.pdf)
---
# Getting Started

1. Log into slack
2. Log into cs-gitlab.union.edu.  If 
3. On the machine you're using (I'll call this your *development machine*):
   * create a CSC333 folder or directory in the location of your choice.
4. If you already have an ssh keypair generated on your development machine, skip this step.  Otherwise, [generate one using these steps](https://cs-gitlab.union.edu/help/ssh/README#generating-a-new-ssh-key-pair)
   * IMPORTANT - when prompted for a password to use with your keypair, just hit enter to create a blank password for your ssh keypair.  You'll thank me later.  
   *  You may want to re-create a keypair with a blank password if you already have one on your computer
5. Add you SSH public key to your gitlab profile (if it isn't there already)
under your profile icon (top right), select "Settings", then "SSH Keys"

---

## Cloning the repositories.

You'll be using two repositories in this course.
   * `csc333-labs-n-demos` (read only) - this is where I'll post lab assignments and starter code
   * `username-csc333` - your personal repository

 From your CSC33 Folder or directory on your development machine:

`git clone git@cs-gitlab.union.edu:rieffelj/csc333-labs-n-demos.git`

(if you're asked for a password, or get an error, then return to the step about SSH keys above.)

You'll see an `week-1-c-bootcamp` directory in there.  Next, clone your personal csc333-<username> project.  This should involve something like this:
 
`git clone git@cs-gitlab.union.edu:username/username-csc333-s21.git` (except with your username)

Next, perform the following steps:

```
cd csc333-username
touch README.md
git add README.md
git commit -m "add README"
git push -u origin master
```

Great! Now move (via  `cp -R` or drag-and-drop) the `week-1-c-bootcamp` directory from the class repo into your personal repo, and add the files to your repository:

```
cd week-1-c-bootcamp
git add prime-factors.c
```

---

## Compiling and running the code

We don't use no stinkin IDEs in this class.  We will be working from the command line!

Try compiling the code:

`gcc factors.c`

And running it:

`/a.out`

Neato!  You may, of course, want to give the executable a different name.  You can do this with the `-o` flag:

`gcc factors.c -o factors`


# Assignment 1: Modifying the code


First,  modify the [Writeup Markdown](Writeup.md) in the repo to reflect your name.  

Now that that's out of the way, make the following changes to the code:

1. Look at the code to understand what is happening
2. try picking other big numbers, and find their factor
3. change the code by:
   1. code should find the largest divisor, not the first (don't break)
   2. print if the number is prime or not
   3. Take some timing, and make a note of them down in your Writeup.
4. Now improve the code by:
   1.  incrementing by 2 instead of 1
   2.  stopping as soon as you reach the square root of the number (why?)
   3. Take some timing, make a note in your Writeup
You may need to add the line `#include <math.h>` at the top of your program, and then you'll need to compile with the `-lm` flag

`gcc factors.c -o factors -lm`

## Submit:

Commit and push to your repo:

*  Your Writeup,  containing
   * data from steps 3 and 4 above 
   * an explanation of why you might get different time values for the same number
*  Your qfactors.c`




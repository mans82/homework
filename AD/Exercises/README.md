# Exercises

## List of known incorrect solutions

Not all my solutions to coding exercises are correct. Here is a list of those that did not get full mark from the Quera Judge:

* Exercise 1 - Question 5 (marked 97 of 100)
* Exercise 4 - Question 3 (marked 97 of 100)
* Exercise 5 - Question 6 (marked 87 of 100)

## Compiling LaTeX for Exercise 2

Exercise 2 was written using LaTeX. `xelatex` was used to compile the source file. Several LaTeX packages, most notably `xepersian`, were also used and need to be installed before compiling.

After installing `xelatex` and required packages, compile the `.tex` file:

```bash
cd "AD/Exercises/MySolutions/HW02"
xelatex ./HW02.tex
```

The resuling PDF file will be available as `./HW02.pdf`.

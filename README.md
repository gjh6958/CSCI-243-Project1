# CSCI-243-Project1
Project 1 for the Mechanics of Programming
Assignment Overview:
Language processing programs (such as compilers, interpreters, and assemblers) face a number of challenging tasks. They must examine the original source code being processed, must break it up into its component pieces (called lexical analysis), verify that those pieces form legal statements in the language (called syntax analysis), and then generate an equivalent version of the program that can be executed directly by the computer (called code generation).

Lexical analysis is typically performed by a program called a scanner. The scanner reads the input character by character, determining what type of element each represents, and converting that information into a form that is easier for the rest of the language processing software to deal with. Each of these converted items is called a token; using tokens makes it easier for the syntax analyzer (called a parser) to examine the input elements and verify their legality.

For this assignment, you will implement a scanner for a small subset of the C language: identifiers, decimal integers, octal integers, block-style comments, and basic arithmetic operators. Scanners can be implemented in many different ways. For this assignment, you will implement your scanner using a data structure known as a transition matrix.

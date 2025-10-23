# C++ Quiz Application

## Description
This is a console-based quiz application built in C++. It allows users to answer multiple-choice questions while tracking their score and total time taken. Skipped or incorrectly answered questions display explanations to enhance learning.  

The application demonstrates core Object-Oriented Programming concepts and memory management in C++.

---

## Concepts

- **Constructors:** Initialize quiz questions and the quiz manager object.  
- **Destructors:** Clean up dynamically allocated memory for questions and the quiz manager.  
- **Polymorphism:** Implemented through the `Question` base class and `TimedQuestion` derived class, allowing different types of questions to be handled uniformly.  
- **Dynamic Memory Allocation:** Questions and the quiz manager are allocated dynamically using `new` and cleaned up with `delete`.  
- **Timer and Score Tracking:** Measures the total time taken to complete the quiz and calculates the score with feedback.

---

## Features

- **Multiple-Choice Questions**
  - 12 pre-defined questions on C++ OOP concepts.
  - Users can answer or skip questions.
  - Explanations are provided for skipped or incorrect answers.

- **Score Tracking**
  - Displays total score, percentage, and performance feedback.

- **Time Measurement**
  - Tracks total duration of the quiz.

- **Interactive Console Interface**
  - Questions and options are clearly displayed.
  - Immediate feedback is provided for each answer.

---

## Technologies

- **Programming Language:** C++  
- **C++ Standard Library Features**
  - `iostream` for input/output operations.
  - `vector` and `string` for data storage.
  - `chrono` for time measurement.
  - Dynamic memory allocation with `new` and `delete`.


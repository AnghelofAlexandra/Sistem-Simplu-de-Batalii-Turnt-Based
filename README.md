# Sistem-Simplu-de-Batalii-Turnt-Based
Console RPG Combat System (C++ Object-Oriented Project) This is a turn-based combat and user management system developed in C++, emphasizing Object-Oriented Programming (OOP) principles such as classes, custom operators, friend functions, and dynamic memory management. 

Key Features
Player Class (Player): Manages user data including username, level, and points. Includes overloaded operators for point manipulation (+=, -=) and ranking comparison (<=).

Character Class (Character): Defines combat entities with properties like health, maxAttackPower, and powerBoost. The core attack mechanic is handled via the overloaded subtraction operator (-=).

User Management (Users): A container class designed to handle a dynamic array of Player objects (via pointers). It utilizes shallow copy for memory efficiency (while acknowledging the risks involved in production environments). Features include user existence checks, sorting by points (orderByPoints), and resizing the internal array (operator+=).

Randomized Combat (fight function): Implements a best-of-three round system. Combat rounds utilize C++'s rand() function to introduce randomized damage within a specified range, ensuring the Player does not always win.

Level Progression: Points earned/lost dynamically adjust the player's level via specific thresholds (50 points per level), correctly implementing both "Level Up" and "Level Down" logic.

Technical Focus
Custom Operator Overloading (+, -, =, ==, <<).

Dynamic Memory Management (new and delete for classes and pointer arrays).

Friend Functions and Classes for controlled access to private members.

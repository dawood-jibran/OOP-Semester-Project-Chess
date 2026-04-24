♟️ Console Chess Game (C++ OOP)
FAST-NUCES Faisalabad-Chiniot Campus
Course: Object-Oriented Programming (Spring 2026)

Project Group: Muhammad Dawood, Faisal Ali, Abdullah Matloob

📝 Project Overview
This project is a fully functional, two-player, console-based Chess game developed in C++. The goal of this project is to apply advanced Object-Oriented Programming (OOP) concepts to manage complex game logic and piece interactions.

🚀 Key Features
Full Chess Rules: Supports unique movement logic for all pieces (Pawns, Rooks, Knights, Bishops, Queens, and Kings).

Turn-Based System: Automated turn switching between White and Black players.

Dynamic Board: An 8x8 interactive grid that updates in real-time in the console.

Win Condition: Detection of King capture to conclude the game.

🛠️ OOP Principles Demonstrated
This project was built from the ground up to showcase the following pillars of OOP:

Inheritance: A base Piece class serves as the parent for all specific piece types (e.g., class Pawn : public Piece).

Polymorphism: Utilizes virtual functions for isValidMove() so the board can handle various pieces through a single base pointer.

Encapsulation: Private data members and protected attributes ensure data security and proper access control.

Composition: The Board class "has-a" 2D array of Piece objects, managing their lifecycle and interactions.
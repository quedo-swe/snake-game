# 🐍 Snake Game (C++ / SFML)

A classic Snake game built in C++ using the SFML library.

## 🎮 Features

* Smooth snake movement using grid-based logic
* Food spawning system
* Score tracking
* High score system (runtime)
* Increasing difficulty (speed increases over time)
* Screen wrapping (snake goes through walls)
* Game over screen with restart option

## 🎯 Controls

* **W / ↑** → Move up
* **S / ↓** → Move down
* **A / ←** → Move left
* **D / →** → Move right
* **R** → Restart after game over
* **ESC** → Exit game

## 🛠 Technologies

* C++
* SFML (Graphics, Window, System, Audio)

## ▶️ How to Run

1. Install SFML
2. Open the project in Visual Studio
3. Build the project
4. Run the executable

⚠️ Make sure SFML `.dll` files are available in the executable directory

## 🧠 Game Logic Overview

* The snake is stored as a vector of segments
* Movement is controlled by direction vectors `(dx, dy)`
* Each update step:

  * A new head is added
  * Tail is removed (unless food is eaten)
* Collision with itself triggers game over
* Speed increases every 5 points

Example:

* Snake grows when eating food
* Game speed increases gradually
* High score updates dynamically 

## 🚀 Future Improvements

* Save high score to file
* Add sound effects
* Add main menu
* Improve graphics / animations

## 👤 Author

Vadym Beshta

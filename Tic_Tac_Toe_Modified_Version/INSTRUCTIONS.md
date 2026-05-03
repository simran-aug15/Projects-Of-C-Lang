# 🧠 Project Logic & Implementation Details 📚

This document explains the working logic behind the **Modified Tic Tac Toe** version. 🎮

## 🕹️ 1. CLI-Based Game Logic (Terminal) 💻
The **CLI (Command Line Interface)** version is built in C and runs directly in your terminal. It uses a 3x3 grid (2D array) to manage the game state. 🛠️
- **Win Condition Check**: After every move, the system scans rows, columns, and diagonals for three matching symbols ('X' or 'O'). 🔍
- **Terminal Refresh**: Uses `system("cls")` to provide a clean, "app-like" experience by clearing the screen before each redraw. 🧹

## 🤖 2. AI Difficulty Levels 🧠

### 🟢 Easy (Level 1)
- **Logic**: Random selection. 🎲
- **Implementation**: The AI scans for all available empty spots, stores them in an array, and picks one randomly using `rand()`. Simple and unpredictable! ⚡

### 🟡 Medium (Level 2)
- **Logic**: Heuristic-based / "Smart" moves. 💡
- **Implementation**:
  1. **Win**: AI checks if it can win in the next move. If so, it takes it! 🏆
  2. **Block**: AI checks if the player is about to win and blocks that spot. 🛡️
  3. **Fallback**: If no immediate win or block is needed, it makes a random move. 🎲

### 🔴 Hard (Level 3)
- **Logic**: **Minimax Algorithm** (Optimal Strategy). 🎓
- **Implementation**: 
  - A recursive algorithm that simulates every possible game outcome. 📈
  - It assigns scores: **+10** for an AI win, **-10** for a player win, and **0** for a draw. 📊
  - The AI plays perfectly, ensuring it either wins or forces a draw. It is **unbeatable**! 🥇

## 🎨 3. Terminal Interface Enhancements 🌈
- **ANSI Escape Codes**: Used to bring the CLI to life with vibrant colors! 🎨
- **Score Persistence**: Tracks wins, losses, and draws across multiple rounds in a single session. 📈
- **Input Guard**: Sophisticated validation logic prevents players from making illegal moves or entering invalid data. 🛡️

## 🌐 4. Web Implementation (Gamified) ✨
- **State Management**: JavaScript handles the reactive board state and turn-based logic. ⚙️
- **Premium UI/UX**:
  - **Glassmorphism**: Elegant semi-transparent backgrounds with blur effects. 💎
  - **Smooth Transitions**: CSS animations for symbol placement and hover effects. 🎬
  - **Responsive Design**: Play on any device, from mobile to ultra-wide monitors! 📱💻

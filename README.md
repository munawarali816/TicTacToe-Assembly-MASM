# ❌ Tic Tac Toe - Assembly Language Project ⭕

## 📚 Overview
A fully functional Tic Tac Toe game implemented in **Assembly Language (MASM32)** as a Computer Organization and Assembly Language course project. This project demonstrates low-level programming concepts including memory management, register manipulation, and system calls.

## 👥 Team Members
- **Munawar Ali** - NUM-BSCS-2024-60
- **Muhammad Hamza** - NUM-BSCS-2024-48

## ✨ Features
- **Two-Player Gameplay**: Player 1 (X) and Player 2 (O) alternate turns
- **Interactive 3x3 Grid**: Dynamic board display with position mapping (1-9)
- **Input Validation**: Handles invalid inputs and occupied positions
- **Win Detection**: Checks rows, columns, and diagonals for winning combinations
- **Draw Condition**: Detects when board is full without a winner
- **Replay Option**: Play again or exit after each game
- **Modular Design**: Separate procedures for each game function
- **Memory Efficient**: Approximately 1000 bytes memory footprint

## 🛠️ Technical Implementation

### Assembly Language Concepts Used
- **Procedures** (PROC/ENDP): For modular code organization
- **Conditional Jumps** (JE, JNE, JMP): For game logic and decision making
- **Memory Addressing**: Direct access to game board memory
- **Registers**: EAX, EBX, ECX, ESI for data manipulation
- **Stack Operations**: For preserving register states
- **System Calls**: Irvine32 library for I/O operations

### Data Structures
```nasm
row1 BYTE ' 1 ', '|', ' 2 ', '|', ' 3 ', 0
row2 BYTE ' 4 ', '|', ' 5 ', '|', ' 6 ', 0
row3 BYTE ' 7 ', '|', ' 8 ', '|', ' 9 ', 0

 Project Structure

Coal Project/
├── main.cpp                  # Main source code (MASM Assembly)
├── Tic-Tac-Toe.pptx          # Project presentation slides
├── Tic-Tac-Toe Report.docx   # Complete project documentation
├── README.md                 # Project overview and guide
└── .gitignore               # Exclude unnecessary files


🚀 How to Run
Prerequisites
MASM32 (Microsoft Macro Assembler)

Irvine32 Library

DOSBox or Windows Command Prompt

How to Play
Player 1 (X) makes the first move

Enter a number (1-9) corresponding to grid position:

 1 | 2 | 3
-----------
 4 | 5 | 6
-----------
 7 | 8 | 9

              TIC TAC TOE
  ________________________________________________________________________________
 |  ______         _____     _____            ____     ________  ______    ____   |
 |    |      |    /            |     //\\    /             |     | __ |   |       |
 |    |      |   |             |    //--\\  |              |     ||__||   |----   |
 |    |      |    \___         |   //    \\  \___          |     |____|   |____   |
 |________________________________________________________________________________|

 -----------
  X | O | 3
 -----------
  4 | 5 | 6
 -----------
  7 | 8 | 9
 -----------

 X PLAYER's TURN: 3

 Key Code Snippets
Win Detection Logic
nasm
win PROC
    ; Check rows
    mov esi, offset row1
    mov bl, [esi+1]
    cmp bl, [esi+5]
    jne check_row2
    cmp bl, [esi+9]
    je w
    ; Check columns & diagonals
    ; ... (additional logic)
win ENDP
Board Update Logic
nasm
updatetable PROC
    ; Compare input with valid positions
    cmp value, '1'
    je replace1
    ; ... (additional checks)
    ; Replace position with player's mark
    mov [esi+1], al
updatetable ENDP
Input Validation
nasm
inputPlayer PROC
    mov edx, offset player1
    call writechar
    mov edx, offset plmsg
    call WriteString
    call readchar
    mov value, al
    ret
inputPlayer ENDP
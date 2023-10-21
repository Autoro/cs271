// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Initialize variables.
@current
M = 0
@previous
M = 0
@diff
M = 0
@color
M = 0

// Main loop to listen for a key being pressed.
(LOOP)
// Get current keyboard state, and check to see if it is different
// than the previous state.
    @KBD
    D = M
    @current
    M = D
    @previous
    D = D - M
    @diff
    M = D

// Update previous keyboard state.
    @current
    D = M
    @previous
    M = D
    
    @diff
    D = M

// Keyboard key was pressed.
// The color of -1 means every bit of the register will be set to
// 1 (black).
    @color
    M = -1
    @FILL
    D;JGT

// Keyboard key was released.
    @color
    M = 0
    @FILL
    D;JLT

    @LOOP
    0;JMP

// Function to fill the screen based on key press or release.
(FILL)
// Get the screen starting address to iterate with.
    @SCREEN
    D = A
    @address
    M = D

// Create iterator for every address of the of the screen.
// The screen 256 rows of 32 16bit registers; meaning 
// 8,192 total addressable spaces. Each space corresponds to
// a 16bit register where each bit corresponds to a single pixel.
    @i
    D = M
    @8192
    D = A
    @i
    M = D

// Loop through every address of the screen.
(LOOP_FILL)
// Update the iterator and exit function if less than zero.
    @i
    MD = M - 1
    @END_FILL
    D;JLT

// Set pixel color.
    @color
    D = M
    @address
    A = M
    M = D

// Go to next screen address.
    @address
    M = M + 1

    @LOOP_FILL
    D;JMP

(END_FILL)
    @LOOP
    0;JMP
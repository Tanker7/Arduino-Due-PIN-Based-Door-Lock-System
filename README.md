This project is a secure PIN-based door lock system built with an Arduino microcontroller. It uses a keypad to allow the user to enter a PIN and control the locking mechanism via a servo motor. The system provides feedback to the user through an LCD display and a buzzer to indicate correct or incorrect PIN entries.

Features
- PIN Authentication: Users can enter a predefined PIN using a 4x4 matrix keypad. If the PIN is correct, the door lock (controlled by a servo motor) opens, and the system provides feedback on the LCD screen.
- Security Feedback: An audible buzzer sounds if the entered PIN is incorrect, and the system resets to allow the user to retry.
- Visual Display: A 16x2 I2C LCD display provides real-time information, showing the entered PIN digits and indicating whether the entry was correct or incorrect.
- Servo-Controlled Lock: The servo motor unlocks the door for a set period when the correct PIN is entered, then returns to its locked position.
- Buzzer Feedback: An integrated buzzer gives auditory feedback for incorrect PIN entries, ensuring users know when access is denied.

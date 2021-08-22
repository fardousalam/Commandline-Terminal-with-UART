# UART Command Line Terminal Programming 

# Motivation of this Project
In Embedded system it's a very common application that we write a command in our terminal and wants to do some actions according to the command. So, this project can be used for this type of work. The developper just need to modify his/her code according to the required acctions.

# Tasks of this Project:

1. Enabling the tera term terminal to receive the command string in UART recieve interrupt mode
2. check whether the command is valid or not
3. If the command is invalid then get the error messages in the terminal
4. If the command is "LED ON" then turn the in build microcontroller LED
5. If the Command is "LED OFF" turn of the LED
6. If the Command is "COUNTER ON", then Count how many times LED has been ON
7. If the Command is "COUNTER OFF", then Count how many times LED has been OFF
8. If the Command is "COUNTER", then Count the number of time LED ON and LED OFF
9. If the Buffer is full then its overloaded buffer

# Future works
1. If the Command is "Move forward", start clockwise motor rotation
2. if the command is "Move backward", start anticlock wise motor rotation.

# Requirements:
1. Stm32 Nucleuo board or dicovery board
2. Stm32 cube id
 
# Installation
Install the stm32 cube ID in PC and Configure the Project according to the target stm32 board that will be used.
In this project Nucleo F303RE board was used.

# RS232-synchronous-chat
Chat application with synchronous communication via Recommended Standard 232.

## Taxi-v3
The taxi-v3 problem is a classic reinforcement learning problem in the Python library Gym.
The goal is to learn an agent how to navigate a grid-world environment as a taxi driver, picking up passengers and dropping them off at their desired locations.
The environment is represented by a 5×5 grid, with walls blocking certain paths and 
passengers and destinations represented by colored squares. 500 states.
The agent receives a reward for successfully picking up and dropping off passengers. However, the agent also incurs a penalty for each time step is taken and for illegal actions, such as attempting to pick up a passenger who is already in the taxi.
Actions: move south, move north, move east, move west, pick up a passenger, drop off a passenger.
</br>More info here: [Gym Documentation]: https://www.gymlibrary.dev

## Project files:
- <code>'rs232.c'</code> contains functions for:
	- rs232_open
	- rs232_close
	- rs232_read
	- rs232_write 

- <code>'rs232.h'</code> contains:
	- structure rs232_obj
	- declaration of rs232 functions

- <code>'232chat.c'</code> contains:
	- ReadThread func 
	    -that сonstantly waiting and reading a message from another user 
  - main
      -that daw

## Overview

For each algorithm, you can run a training and test methods.
</br><code>agent1 = QlearningAgent()</code> choose the algorithm.
</br><code>agent1.train()</code> run a training method.
</br>After that, policy file will be generated and saved to main path.
</br>Similarly, you can run test method <code>agent1.test()</code>

If you want to change hyperparameters such as: learning rate, discount factor, epochs, 
use: </br><code>QlearningAgent(0.9, 0.6, 2000)</code>

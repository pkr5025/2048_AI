# 2048_AI

###### Final Project: Built an AI to play the game 2048 using both monte carlo and neural network methods

![2048 Example](https://github.com/philipkleinrodick/2048_AI/blob/master/Readme_Images/2048_Example.png)


## Objectives
* Build an artificial intelligence to play the game 2048
* Build an artificial intelligence to play the game 2048 WELL (ie achieve a high score)
* Implement a deep q neural network 

### How to play 2048

The rules of the game are quite simple.  You start with a four by four grid initially filled with two '2' tiles.  Then make a move up, down, left, or right.  All of the tiles will shift in the designated direction.  Tiles of the same value will combine into a single tile of twice the value.  If there are any empty tiles, a single new tile will be added.  The new tile will be a '2' with a probability of 90 percent and '4' with a probability of 10 percent.  Each time two tiles are merged, the value of the resultant tile is added to your score.  You win the game by achieving the 2048 tile, although one is allowed to continue playing until there are no more legal moves remaining.


### The Algorithms: Deep Q Learning

The basic idea behind q learning is to learn, for any given input, what is the best output.  To this end, each output is given a reward.  Q learning then learns a policy (ie output for each input) that maximizes the total reward over the current step and all future steps taken.  Then, for deep q learning, we are just using a neural network to appoximate the policy.  For more information, see https://en.wikipedia.org/wiki/Q-learning.

My algorithm is simply applying deep q learning to the game 2048.  I tried multiple reward functions before mostly focusing on a simplistic one, the change in score after a move.

### The Algorithms: Monte Carlo

First, given a board state, find the legal moves.  Then for each legal move, play a large number of games starting with that move followed by entirely random moves.  Take the average score of the games played grouped by starting move.  Then, in the actual game, perform the move with the highest average score.  

### My Initial Approach

First I implemented a version of the game in python.  Then I implemented my own deep q neural network using keras with a tensorflow backend, and I proceeded to train the network.  Unfortunately, soon after starting to train the network, I found my implementation was too slow to have any meaningful results.

### My Second Approach

Fortunately, I had a deep learning library to turn to in Keras-RL (https://github.com/keras-rl/keras-rl) which smoothly integrates with OpenAI Gym (https://gym.openai.com/), an environment built for implementing deep learning algorithms on.  In Keras-RL, there is a ready made deep q learning agent already implemented.  So, I found an open source implementation of 2048 made in openAI gym, and ran the deep q learning agent on it.

#### A Problem and Attempted Solutions

Unfortunately, Keras-RL requires one to feed as input all possible actions, not just legal actions.  That is, for the given board state <img src="https://github.com/philipkleinrodick/2048_AI/blob/master/Readme_Images/Illegal_Example.png" alt="Legal Options Example" width="100"/> , the deep q agent would be fed the options Left, Right, Up, and Down instead of just Left, Right, and Up.  And once the agent is fully trained, it will always give the same output for a given input, leading to an infinite loop of the agent continually playing an illegal move, arriving at the same board state, and trying to play the same illegal move again.

* Solution One: give a negative reward for illegal moves.  
This solution succeeds in greatly limiting the number of illegal moves the agent makes.  Then for the illegal moves, alternative approaches can choose a move to be played instead of the agent.  However, this approach has a major problem.  The agent puts an emphasis on making legal moves over optimal moves.

* Solution Two: Ignore illegal moves and only look at training games.
This approach avoids the infinite loop of illegal moves problem since during training, the agent will always eventually try a legal move for any given board state.   The disadvantage of course is that the agent can never be brought out of training as a completed model.  

After solution one failed, I continued with my second solution.  I tried various different reward functions and neural network architectures, and I trained my model for millions of moves.  However, my neural network never performed exemplorarily, only achieving the 512 tile at best.

### My Final Approach

Given my neural network's short comings, I then implemented a monte carlo algorithm.  Interestingly enough, it did not play like a human would.  Human players typically try to keep their largest tile in the corner <img src="https://github.com/philipkleinrodick/2048_AI/blob/master/Readme_Images/2048_Example_Large.png" alt="Large example game" width="250"/> with the successively large tiles around it.  However, my monte carlo algorithm frequently kept its largest tile in the middle of the board.  Nevertheless, it performed quite well.  

### Monte Carlo Algorithm Results:

Here is a gif of my monte carlo alogirthm running.  The scores above the board indicate which move will be played next based on the random games played.

<img src="https://github.com/philipkleinrodick/2048_AI/blob/master/Readme_Images/2048_GIF.gif" alt="Large example game" width="250"/>

I have ran my monte carlo algorithm using 10 random games per move and 100 random games per move.  Note the games were run from the same starting position for both categories.

![Statistics Table](https://github.com/philipkleinrodick/2048_AI/blob/master/Readme_Images/Monte_Carlo_Statistics.png)

### Future work

I would like to continue playing with my deep q learning approach.  I believe its current short comings are due to too little training and potentially an overly simplistic reward function.  I also can toy with different neural network architectures ( the number of neurons, hidden layers, activation functions, etc).

Regarding the monte carlo approach, I would like to implement multiprocessing or even rewrite my code in C++ in order to speed up my code.  This will allow me to increase the number of random games ran per move.  I also would like to try implementing a depth limit where the random games will end after n moves for some n.

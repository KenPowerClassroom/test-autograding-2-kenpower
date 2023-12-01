# Refactoring exercise

Examine the code in `TicTacToe.cpp` and the tests in `test.cpp`. It has a simple implementation of a TicTacToe game.
Notice that the `winner()` method is simplified: you win by getting three in a row horizontally. 
Notice also that the heuristics for what to play are primitive: win if you can, play any valid move otherwise. 
We’ll migrate toward something capable of more sophisticated strategies.

## Before you change any code, make sure all the tests run and are green. If not, ask for help.

## Smells

Go through this code and identify smells (code which which make the project less maintainable). Do you understand what all the methods do? Do you understand what each loop is for? If the answer to the previous questions is "No", then maybe the code could become clearer? 

## Easy changes

It’s not always easy to know what to do with code. Let’s fix some of the easy things first.
Fix them one at a time. **Run the tests after each change**.

- [ ] The name `move()` isn’t descriptive enough. Change it to `bestMoveFor()`. Use  `CRTL-R, CTRL-R` key.
- [ ] Run the tests (still green? If not, undo changes from previous step and try again)
- [ ] The variable `i` doesn’t explain much either. It's not just an index variable, it represents something the game world. Change it to `possibleMove`. Use `CRTL-R, CTRL-R` key shortcut.
- [ ] Run the tests (still green? If not, undo changes from previous step and try again)
- [ ] The value -1 is a flag value; create a constant `NoMove` to represent it.
- [ ] Run the tests (still green? If not, undo changes from previous step and try again)
- [ ] The check for a board character being a ‘-’ is really a check that the square is unoccupied. Extract a method to do this, and name it appropriately.
- [ ] Run the tests (still green? If not, undo changes from previous step and try again)
- [ ] Can the method you just created to check an unoccupied square be used elsewhere to avoid duplication?
- [ ] Run the tests (still green? If not, undo changes from previous step and try again)
- [ ] What does the `t` object represent in the `move` function? Should it have a better name?
- [ ] Run the tests (still green? If not, undo changes from previous step and try again)

## Fuse loops (**Do not proceed with this step unless you have finished the "Easy Changes" above**)

We have two “for” loops: one to find a winning move, the other to find a default move (default == no winning move so pick any valid move).

The loops have the same number of iterations. Maybe it is redundant visiting every part of the grid twice?
One way to handle this would be to merge the two loops and handle things in one pass through the possible moves.

**“Fuse Loops”** means combine two loops into one. Do so in small steps, in such a way that you maintain safety (keeps tests passing) as you do it. 
When is it safe to merge two loops?

**Many refactorings are too complicated to perform or understand in a single step. The refactoring often becomes clearer if it is broken into multiple steps (test should still pass between steps)**

One step along the way to fuse loops might be to assign a value to a temporary variable rather than return it right away. 
You might have made the second loop look like this:

```
 defaultMove = NoMove;
 for (int i = 0; i < 9; i++) {
 if (board[i] == ‘-‘)
   if (defaultMove == NoMove)
     defaultMove = i;
 }
 ```
 We still have two loops, but we have made a step closer to fusing them. And our tests are still passing (have you checked???)
 
 That was the safest approach, used because we did not want our refactoring to change behavior. 
 To be equivalent to the original, we need the guard clause to make sure we haven’t assigned a `defaultMove` yet.
 But let’s put on a development hat: we don’t really care which default move we make, so we could delete the “defaultMove==NoMove” condition. 
 It’s not necessary to stop when we find a viable move. (That is, there’s no harm in trying each possible move provided we prefer wins to defaults.) 
 So you can delete the “break” tests that exit early. Run the tests again and be sure you haven’t changed anything important.
 
 (**You may now have failing tests, but the methods are returning valid results. You may have to change the tests**. What does this tell you?)
 
 Now we have a single loop, but the condition to decide what to return is still a little complicated:
 
 ```
   if (winningMove != NoMove)
     return winningMove;
   if (defaultMove != NoMove)
     return defaultMove;
   return NoMove;
 ```
 
 How would you simplify the above?
 
 *Hint: use a single `result` var to return the correct move. Also no need to continue the loop if a winning move is found*
 
 ## Next refactorings
 
 Before reading on, have a look at your code. What should be the next refactor to tackle? Or an easier question, "Which part of the code is the stinkiest?"
 
 There are still a lot of “magic numbers” floating around. 
 The winner() routine is full of them, and we still have a “9” in the main loop of bestMoveFor().
 What does "9" mean in this game?
 
 Also there is a lot of duplication in the winner() method. **Eliminate this duplication**
 
 ## More ways to win
 
To assess your previous changes, switch back to a development hat. 
A change we need to make is that we’re not playing full tic-tac-toe yet because we’re only allowing horizontal 3-in-a-rows. 
Extend the `winner()` routine to allow vertical and diagonal wins. **Write tests for these cases first!!**
Was it easy to change given your refactoring?

 ## Finding the Best move
 
 Currently, we’re just looping through possible moves, trying to select the best one. 
 Right now, we have a simple rule: wins are best, 
 anything else is acceptable. But wins are rare; we’d like to pick a good intermediate move. 
 (Some moves are better than others, implies move has a "value")
 
 We can think of each move as having a score: "how good is it?". 
 Just to have something to work with, we’ll call a win worth 100 points, and any other move 0 points.
 (We can imagine a winning move by the other player being worth -100 points, but we don’t check for those — yet.)
 
 A smarter program would be able to score each valid move: There might be moves woth 100(win), moves worth -100(lose) and moves with scores inbetween.
 
 With scoring in place we would like to return the *best* available move, the move with the higest score.
 
 With this idea, moves are not just a `position`, but have a score also. Move has out-grown it's primitive. **Introduce a 'Move' class.** (put it in `TicTacToe.cpp`). Finding the best move is like finding the highest integer, but will need to be able to compare "Moves": `if(move1.isBetterThan(move2))` (**write tests for this**).
 
 After the move class is in place, modify the program to calculate scores for moves (winning = 100, others = 0), and return the position for the move with the best score. 

 # Submission instructions
 
 ### One of the pair push the project to the github repo

 ### BOTH PEOPLE IN THE PAIR SHOULD Upload the file `TicTacToe.cpp` & `test.cpp` to the blackboard "Refactoring Lab" assignment on their own BB account
 
 ## [Advanced & Optional] Evaluate the opponent's move
 
 So far we score a winning move as 100 and "non-winning" moves as 0. How can we choose which "non-winning" move to play? One way would be to check if the oppoent could win following a "non-winning" move. if a "non-winning" move allows the opponent to win, the we can score that move as -100.
 
Add another feature: (write a test first) use the min-max algorithm. Instead of just saying "non-wins are all the same," you say "Choose my best move, assuming the opponent makes the move that's worst for me." The opponent uses the same rule. Write a test to check that it doesn't give me a move which leaves the opponent with a winning move. 
 
 In artificial intelligence circles, the approach we’re using is known as min-max. When it’s our turn, we try to maximize our score. When it’s the opponent’s turn, they try to minimize our score. How is this reflected in this code? Is it a “trick”?
 
 
 
 
 
 

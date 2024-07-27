# Reinforcement Learning Assignments

This repository contains two assignments for a reinforcement learning course. The first assignment focuses on working with multi-armed bandits, while the second involves a 4x4 grid with reward pots where you will apply a Markov Decision Process (MDP) to determine the optimal policy.

## Table of Contents

- [Description](#description)


## Description

### Project part 1:
This involved solving the Unbearable Revenge. First I thought of just hovering over the bears and be done with it, but then realised that the bears shoot too. Then I thought of removing the shooting phase entirely. This involved looking for keywords in BinaryNinja, and all the functions which had the words like "Stand" or "Shoot" in it. I tried to make them all dummy definitions. But that didn't work out too. It looked like the server had its own version of what it thinks should happen. Although interestingly, the changes to these functions had no effect in the Client's side too. 
But then with the tp function, I could go underground too. Since the bears look for targets and only then shoot them, I thought they may not attack if they don't see the player. And that worked out.


### Project part 2: 
First I went around looking for anything in Binary Ninja related to Golden Eggs, and noticed a bunch of GoldenPickup<1> sort of functions. Since they inherited from the Actor Class, I thought I could access it, I might be able to print its position and then simply tp to the position and collect the egg. But this turned out to be a bit difficult. I then went back to the World Object where we had the list of all actors. It only had 22 elements with it. I wondered whether it was just NPCs and other default creatures which came under that and was doubtful whether the eggs came under this. Moreover I didn't know how to access the set. But then I later looked it up, and this turned out to be the way. If I had known how to iterate over the set, I could've figured this out on my own. But as for the last egg, I saw the CanUse functions and tried to change it. But they kept throwing some error regarding some death message not being present. I later noticed that there was something called the Ballmer Secret and above that was CowBoy Coder. I had no clue what that had to do with the Poster or the Egg for I didn't know the gun existed(I had it at some point but my game reset after I close the server so I forgot about it). I saw the damage function and wondered if I did some damage with something, something would happen. But nothing happened. I had to look up what the CowBoy Coder meant(which in hindsight I could've just looked at Binary Ninja) and then it struck me. After that it was just a matter of picking the egg up.


## Contact
For any further details, contact hars8756@gmail.com!

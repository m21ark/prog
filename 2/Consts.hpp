//T07_G07
#pragma once

const char PLAYER_ALIVE = 'H';
const char PLAYER_DEAD = 'h';
const char ROBOT_ALIVE = 'R';
const char ROBOT_DEAD = 'r';
const char ROBOT_STUCK = 'r';
const char POST_ELEC = '*';
const char POST_NONELEC = '+';
const char EXIT_GATE = 'O';

/*
Please note that if you switch any of these values for another default one some errors will 
occurr... for example, don't switch ROBOT_DEAD to 'R' or PLAYER_ALIVE to '*'.
I have decided to code it this way so you can change the displayed characters here without 
having to change the maps, although if you do change the maps 
(following at least that one rule) it will also work
*/
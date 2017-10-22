# Jetpack Game

This game is being build for Professor Pieter Peers' Introduction to Video Game Design (CSCI437) class at The College of William & Mary.

## Executive Summary

Jetpack Game takes place in the future on a spaceship, run by a seemingly benevolent AI, that serves as a place to test new technology. Our main character, TECH-17, is testing a jetpack and must navigate through a sequence of physics-based test chamber puzzles to discover the truth about the AI as the ship slowly degrades around him. This game takes one of the most successful physics puzzle games of all time, Portal, and splits it into bite-size chunks for the casual gamer while removing the unnecessary complexity of portals and adding the fresh new jetpack mechanic.

## Build

### Requirements

- SFML 2.4.2
- C++11 Compiler
- Cmake
- Make

### Instructions

```bash
git clone --recursive https://github.com/tz0/game
cd game
git submodule init && git submodule update
mkdir Release
cd Release
cmake ..
make
./game
```

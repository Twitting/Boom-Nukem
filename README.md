## Doom_Nukem

> Desctiption
> 
> This project is final project in first graphic branch of School 21 (Ecole 42). There we made
> a game engine, similar with Doom and Duke Nukem 3d. This is much harder to understand and to
> code also engine than Wolf3d. We have manage with walls set in gamespace with float numbers, which
> makes it render, collision and texturing really fun (not really fun when facing it first time).
> When the render was ready, the real fun started: gameplay, animations, enemies, level design, sounds,
> HUD, inventory and other stuff. It was easy to add, but put the perception of game to next level.
> In current state, the game is not very interesting to play, but shows all the engine features.
> To make a real game of that, one must only expand current resources.


### how to install:
```shell
make & make clean
```
### how to start:
```shell
./doom_nukem
./doom_nukem map
./map_editor/map_editor
```
There we can see start screen, with difficult mode choice, save and load options:

![boom.start](https://github.com/Twitting/Other/blob/master/img/doom/gamestart.gif)

Gameplay is set like in old classic shooters, you can jump, crouch, look at all directions and shoot:

![boom.0](https://github.com/Twitting/Other/blob/master/img/doom/game0.gif)

Also there are light control tools, and the gameplay uses it as well - enemies move faster in darker rooms, and slower in lighter - and you can turn on and off the light in room using switches:

![boom.1](https://github.com/Twitting/Other/blob/master/img/doom/game1.gif)

To get to the finish of game, you must find and pick up the key to open the gate:

![boom.2](https://github.com/Twitting/Other/blob/master/img/doom/game2.gif)

Of course, you can die, if you are not very fast in shooting approach enemies. There are some more objects in the world, such as barrels, medkits, terminal and so on.

This level was created by map_editor program, located on:
```shell
./map_editor/
```

![boom.map](https://github.com/Twitting/Other/blob/master/img/doom/edit.gif)

With it, respecting the rules, you can define all kinds of levels, portal-oriented engine provides all opportunities to manage even with non-euclidian geometry levels, infinite corridors, ladders and many other fun stuff.

### authors:
##### ME
##### [Ксения](https://github.com/odnaks)
##### [Карим](https://github.com/ebednar)
##### [Лев](https://github.com/PolyakovLev)

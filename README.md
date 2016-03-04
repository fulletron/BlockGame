Portfolio and BlockGame
=========

Want to build this project?

[Windows Instructions](https://github.com/fulletron/BlockGame/blob/master/not%20src/Windows%20Instructions.txt)

[Linux Instructions](https://github.com/fulletron/BlockGame/blob/master/not%20src/Linux%20Instructions.txt)

This is the newest version of my 3D game. I'm currently working on the base data structures (from Game Programming Gems books) and portability (cMake, boost, soil, glfw).

Unfortunately it doesn't have flashy visuals like the DirectX project does (yet), but the code is much better now. Might be a wee bit- according to "Game Engine Architecture" by Jason Gregory (Uncharted and The Last Of Us), having every game object inheret from an interface with draw(), input(), and update() is wrong (or just not right). He then goes into the two common ways games are set up, one of which I am now trying to emulate.It's a fairly large step away from what I was previously doing. 

I have it compiling in Windows and Linux! Mac is having issues with boost, but I'm shelfing that.

[This is what the DX version looked like](https://github.com/fulletron/BlockGame/wiki/What-the-DirectX-version-looked-like:)

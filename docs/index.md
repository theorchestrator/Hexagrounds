## Hexagrounds - Software-architecture & Features


Our game name is Hexagrounds. It is a basic 1v1 versus turnbased 2D game written in object oriented C++ using the “Simple and Fast Multimedia Library” (SFML)

The game consists of a modular tile-based hexagon map, obstacles (trees, cactuses, and leftover logs), the player / selected player, weapons and the enemy AI.

Currently the code is divided into 17 classes and 16 header files since we wanted to make the game in C++. We decided for C++ because it is maintained better than the C# version of it. Also there are more code examples.

<div style="float:left"><img src="https://user-images.githubusercontent.com/8648557/30786042-330a1030-a170-11e7-81ef-bcd6469e3660.PNG" style="margin-right: 5px;" /></div>

<div style="float:left">
<img src="https://user-images.githubusercontent.com/8648557/30786043-33232822-a170-11e7-9b47-2e132d138119.PNG" style="margin-right: 5px;" hspace="20"/></div>

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

For the texture loading we wrote our own texture manager class, so that we just need to specify the name and it automatically loads the .png texture from the asset folder.
The scene manager draws / displays the current scene and is able to easily switch the scene to other levels or menus.


## Player selection and movement

If the player is clicked, the shirt turns into a different color and the ground color switching indicated the possible walk options for the current move.


<div style="float:left"><img src="https://user-images.githubusercontent.com/8648557/30755570-8a6fb51e-9fc7-11e7-9750-a806038a7fca.png" style="margin-right: 5px;" /></div>

<div style="float:left">
<img src="https://user-images.githubusercontent.com/8648557/30755572-8a742716-9fc7-11e7-9d81-7ff5b5e35870.png" style="margin-right: 5px;" hspace="20"/></div>

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

## Pickup

Both player and AI can pick up weapons that are randomly placed on a hexagon-tile. If picked up, the player or the AI can shoot once a turn at the “enemy” if they are in the range the weapon can shoot.

Weapons pickup is the M4 rifle.

<div style="float:left">
<img src="https://user-images.githubusercontent.com/8648557/30755571-8a72652a-9fc7-11e7-9c87-249ad1b4910f.png" style="margin-right: 5px;" hspace="20"/></div>

&nbsp;

&nbsp;

&nbsp;

## Fog of war

The “fog of war” adds another obstacle / “enemy” to the game. The player can only see a certain amount of tiles surrounding him. It has the effect that the position of the enemy and the weapons remain unknown until the player walks in the viewing- range (2 tiles).

<div style="float:left">
<img src="https://user-images.githubusercontent.com/8648557/30786440-bac9adbe-a175-11e7-8c06-3e5aea125360.PNG" style="margin-right: 5px;" hspace="20"/></div>

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

## Spawning

The player can spawn on any tile on the map. The enemy AI spawn randomly near the player on the grid as well. The M4 will spawn also randomly near the player.

<div style="float:left">
<img src="https://user-images.githubusercontent.com/8648557/30786428-9cfc2942-a175-11e7-9c11-eead348ab9d0.PNG" style="margin-right: 5px;" hspace="20"/></div>

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

## UI

The UI is displayed on the right side of the screen. It indicates whose turn it is and has a button to finish the turn.


<div style="float:left"><img src="https://user-images.githubusercontent.com/8648557/30786438-bac79088-a175-11e7-8bd2-d25f656e4199.PNG" style="margin-right: 5px;" /></div>

<div style="float:left">
<img src="https://user-images.githubusercontent.com/8648557/30786439-bac95080-a175-11e7-8acb-6f4c7c5135a2.PNG" style="margin-right: 5px;" hspace="20"/></div>

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

## AI

The AI takes a turn right after the player finished his. The first thing the AI does, is to find the quickest path to the weapon if the player is not around. Otherwise it will keep distance.


## Preliminary weapon stats

## M4:
  - Texture m4
  - Damage 20 per bullet
  - Shoots 1x per round

## Trajectory:
-	M4 bullets travel 3 tiles


## Possible Turn Sequence / One round

-	Player spawns 
-	AI spawns on the opposite side
-	Player starts with the first round, can move 2 tiles max.
-	Turn ends
-	AI can move equally as much tiles as player (2)
-	Round ends
-	Player moves 2 tiles again & picks up weapon
-	Turn ends
-	AI moves 2 tiles & picks up weapon
-	Player encounters AI (is in range) and shoots with M4
-	AI gets hit with M4

... AI dies
... Player wins


## Preliminary Class structure (UML)


<div style="float:left"><img src="https://user-images.githubusercontent.com/8648557/30755567-8a6e2f78-9fc7-11e7-8ae6-8fabd6c9eba0.png" style="margin-right: 5px;" /></div>



## Organization

Google Drive Texture folder. Everyone was able to upload textures. 
Every Texture is 100x100 pixel in size

<div style="float:left"><img src="https://user-images.githubusercontent.com/8648557/30755599-a2bbf998-9fc7-11e7-8bdf-3c4dd4b795e0.PNG" style="margin-right: 5px;" /></div>

&nbsp;

Game structuring and idea managing was done via a private Trello board.

<div style="float:left"><img src="https://user-images.githubusercontent.com/8648557/30755600-a2bee78e-9fc7-11e7-978b-40bdaa2957c0.PNG" style="margin-right: 5px;" /></div>

&nbsp;

The drag and drop feature was very useful.


## Other documents


-  <a href="https://github.com/infomediadesign/2017-programmierung2-vr-spieleprojekt-theorchestrator/files/1327249/Pattern_Description_Code_Hexagrounds.docx">Pattern Description w Code Examples</a>

-  <a href="https://github.com/infomediadesign/2017-programmierung2-vr-spieleprojekt-theorchestrator/files/1327248/Coding_Style_Guide_Hexagrounds.docx">Coding Style Guide for Hexagrounds</a>


- Code Documentation (COMING SOON™ ...)

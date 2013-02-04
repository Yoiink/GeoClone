//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//              YouTube Video of Geometry Wars: http://youtu.be/d31d1HR_aUg             //
//                      In slow motion to see detail...                                 //
//                                                                                      //
//              	Check List: http://goo.gl/lzLSX					//
//                                                                                      //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//											//
//			~~~THIS GAME IS FOR DEMO PURPOSES ONLY~~~			//
//		CREDIT GOES TO THESE PEOPLE FOR THE FOLLOWING CONTENT:			//
//			Music: All from Geometry Wars Evolved 2				//
//		Sounds: All from Geometry Wars Evolved apart from menu sound		//
//		Art: Created by myself with ideas from Geometry Wars apart from...	//
//			Controller Art: http://goo.gl/sO8mJ				//
//											//
//////////////////////////////////////////////////////////////////////////////////////////


Bug Fix 04/02/2013
Keith ran the game in the lecture theater and there was an obvious bug. This was due to
me testing the game with an Xbox Controller plugged in all the time and when testing to
see if the controller had been unplugged I just simply unpluged "Oh it works" and plugged
it back in.

Anyhow, when there ISNT a controller plugged in, the variables are all wierd and trigger
menues to be switched and even if you get passed that, the gameplay is all wrong.

Anyhow, this is a fix to address the issue.


Update 04/01/2013

New Functionality
-----------------

- Highscore for each game mode
- Added lives/specific mode mechanics
- Game mode tweaks + Orange Enemy
- New "Waves" game mode
- More spawn waves on Deadline/Evolved

Code Additions
--------------

- Changed how the highscore works as now the game modes know what their own highscore file is called
  so they read/write to the correct one.
- Lives can now be done within the game mode. So if Geo is marked dead, it checks with the game mode
  to see if should still be alive.
- New orange enemy that moves in a linear way over the grid. Had to change the enemy class a little to
  allow this to work but it's all good.
- Due to the new enemy, there's a new mode called "Waves" which is pretty much waves of the orange enemy
  plus some of the others thrown in to make it a little harder.

Tests
-----

- Highscore test was simple, just had to check if the data loading/writing was correct.
- Lives/specific game mode mechanics were obvious too.
- Had to make sure the orange enemy works as expected. Checked particles, if collision works, spawn cooldown
- Lots of play testing to test the Waves mode.

Notes
-----
I'm quite glad I got the above features in as it makes the game feel a lot more fun now with the choice of
game types. I would still like to have added some more enemies but I think they may be a bit of a pain due
to how they work.

______________________________________________________________________________________________________


Update (FINAL ICA HAND IN?) - 03/01/2013 (Happy New Year)

New Functionality
-----------------

- Spawn cooldown
- Updated How to Play

Code Additions
--------------

- Added a further if check in the collision function to check if the player is colliding with an enemy
  that is in cooldown.

Tests
-----

- Just had to test if I could collide with an enemy that had just spawned which I can't.

Notes
-----
Overall there is still a lot that I would have liked to add such as player lives and further tweaks to
the game modes. I would have also liekd to add more enemy spawning waves but the general idea is there
it's just getting the idea of more waves which would be easier if there were more enemies which is another
thing I would liked to have added.

The game is mostly all there now though and is playable.

______________________________________________________________________________________________________

Update - 31/12/2012

New Functionality
-----------------

- Highscores

Code Additions
--------------

- Added a couple of functions to read and write to a highscore text file.
- Fixed up the sound manager as I noticed it was creating memory for every sound I played instead
  of playing a pre-loaded file.

Tests
-----

- Had the game running for a while to see if memory was still getting allocated from the audio which it
  no longer is.

Notes
-----
For future updates, I need to really start adding some more enemy spawning waves and try get the
second game mode working. Also need to think where I could add some animation as I don't really need
any at the moment. 

Could do with sorting out enemy spawns so that they don't just spawn and kill the player instantly so 
I'll add a cooldown or something which I have been playing with already.

______________________________________________________________________________________________________

Milestone 5 - 20/12/2012

New Functionality
-----------------

- Menus
- Grid warping
- Sound Manager

Code Additions
--------------

- The grid has changed on how it's drawn. Now every intersection is a point in a vector.
- Each entity is checked against every point on the grid to see if it should distort it.
- Menu systems have been added in place to give the game a more solid feel. Also will be used
  to allow the use of switching game modes.
- Changed the line drawing function as the one I wrote was slightly broke at certain times as I
  found when the grid warping started to work. 
- Added a sound manager for loading and playing audio using FMOD. I may be using this in future if
  I get the time to slow/speed up the music depending on power ups (If I add them too...)

Tests
-----

- Various tests were done on the menues as switching between them is the main point in them so I've
  tested them a lot and think they're solid enough...
- The grid tests were simple too, mainly just shooting bullets and moving about to see how I affected
  each point on the grid.

Notes
-----
No real milestones anymore, just fixing stuff. I would like to move to pre-allocated memory for entities
and such but I think I'll leave that to the very last thing as it could cause big problems.

______________________________________________________________________________________________________

Milestone 4 - 10/12/2012

New Functionality
-----------------

- Enemies no longer overlap (of the same type)
- Particles

Code Additions
--------------

- Enemies will no longer overlap creating a ball like group.
- New class ParticleEmitter which has information on different particle systems
- Fixed parallax by calculating offset and then adding them to the entities while I am updating.
- Memory leaks fixed

Tests
-----

- Parallax test was simple to test, just move about and the enemies should retain there position on the grid.

Notes
-----
Next milestone (20/12/2012):
# Grid warping
# Menu system

______________________________________________________________________________________________________


Milestone 3 <V9> - 02/12/2012

New Functionality
-----------------

- Animation
- Parallax background

Code Additions
--------------

- LoadAnimation()
- Parallax
- Re-structured the classes a little
- Added const correctness (I think!)

Tests
-----

- Coded the LoadAnimation on a 64*64 texture, so tried a 128*64 texture and it loaded the animation.
- Parallax test simply just moving Geo around.

Notes
-----

Bugs:
# Parallax not working as intended. Enemies + bullets shoudld retain an X and Y relative to the
  background. Currently they do not and it just looks wrong.
# Seems to be memory leaks from texures. Can get rid of them if I delete the texture early, but that
  means no texture. If I delete in the destructor, it also doesn't work...

Milestone 4 aims (10/12/2012) - Workload permitting!:
## PRIORITY TASKS ###
# Fix the parallax effect so everything moves relative to the grid. Apart from Geo...
# Fix memory leaks from the textureData

## BONUS ##
# Enemies of the SAME TYPE should NOT overlap. So, enemies will have a set radius that no other entity
  can be in. This should make them form "clusters"
# Enemies should have time to spawn where the player does NOT collide. Currently, if an enemy spawns
  on the player, they're dead. Not fun.
# As above, there should be some sort of way to allow specific animations. So possibly an animation
  manager or just a simple spawn animation.
# Particles? For explosions..

______________________________________________________________________________________________________

Milestone 2 <V8> - 12/11/2012 -- (HAND IN)

New Functionality
-----------------

- N/A


Code Additions
--------------

- N/A

Tests
-----

- N/A

Notes
-----

Just commented out game code to demonstrate that I had met the Milestone. You can go off the screen
using the Xbox Controller but WASD will stop you at the game bounds. Due to commenting out some code
bullets will not be deleted if they go off the screen so don't shoot too many or the game will slow
down.

______________________________________________________________________________________________________

Milestone 2 <V8> - 28/10/2012

New Functionality
-----------------

- AI spawning system in place
- Asset loading with error check
- GameState for possible future game mode(s)/menu(s)?
- Delta Time so everything stays moving at around the same speed when lower FPS


Code Additions
--------------

- GameState Class
- EvolvedGame : GameState
- GameState loads assets
- Xbox controller unplug check
- FMOD, as I would like to possibly play around with music frequency... 

Tests
-----

- Most testing was play testing, with the Delta Time, I simply just spawned enemies so the FPS
  slowed down and I started to notice movement lag/big jumps so I know that's working.
- Asset error check, simply renamed a texture and the game shows a messagebox and then returns.
      - Checked no memory leaks.

Notes
-----

- If compiling and DLL error, move the correct DLL (fmodexL.dll/fmodex.dll) to the Debug/Release folder.
- With FMOD, I wish to possibly add a slow down powerup or maybe ajust the music frequency depending on
  how much is on screen. So if there's a lot of enemies, the music will be faster for example.

______________________________________________________________________________________________________

Milestone 2 <V7> - 28/10/2012

New Functionality
-----------------

- Enemies
- Chase AI
- Texture Handling
- Collision


Code Additions
--------------

- Enemy Class
- Enemy::Chase() - Contains a chase AI
- Changed how everything is stored. They are all in one std::list which is easier(?) for collision
  checking as you can just loop over the list to check each object.

Tests
-----

- Texture tests were simply moving the player off the screen to see if it was handles correctly.
- Enemy spawn if there's less than 10 objects spawned.
- Collision may possibly be a little iffy when shooting enemies as bullets seem to hit even when
  the bullet is above the enemy.


Notes
-----

- I changed a lot of the structure and it all seems to be working still, however I still would like
  to move the render function else where as it is almost duplicate code in GameObject and Bullet.

______________________________________________________________________________________________________

Milestone 1 <V6> - 21/10/2012

New Functionality
-----------------

- Adding textures
- Drawing Textures
- Drawing Textures wih rotation
- Alpha blending
- Geo now rotates to direction.
- Bullets are now affected by how fast Geo is going


Code Additions
--------------

- drawGridBox()
- GameObject::Render() - Containts blending code
- GameObject::Rotate() - May move this, simply updates two variables with the rotated data

Tests
-----

- I created a 36 * 36 image with Red, Green, Blue and Yellow squares on it. Each square had different
  Alpha values so I could test the alpha correctly. As well as making sure the colours were correct.
- Visual test of moving Geo to check rotation
- Visual test to see if bullets are affected by speed


Notes
-----

- Bullets are affected by Geo's speed, however if moving right and shooting left, the bullets should
  be slower due to the ships speed. I will try fix this up a later date.

______________________________________________________________________________________________________

Milestone 1 <V5> - 16/10/2012 
--------------------------------

New Functionality
-----------------

- Now able to draw lines on the screen as a background


Code Additions
--------------

- DrawLine() function
- Draw class - Sets up the screen and various other drawing functions will be in it.

Tests
-----

- I tried generating 1000 lines and it wouldn't seem to load.

Notes
-----

I changed the threshold values on the analog sticks for shooting. Bullets now remove when they hit
screen boundry.

______________________________________________________________________________________________________

Milestone 1 <V4> - 15/10/2012 
--------------------------------

New Functionality
-----------------

- Shooting of bullets - Fixed
- Generation of stars


Code Additions
--------------

- Nothing too new, just re-arranged.

Tests
-----

- Mainly visual tests
- Generate 100,000 stars - Drops frame rate to 60 fps
- Generate 1,000,000 stars - Drops frame rate to 15 fps

Notes
-----

Fixed bullets, just has to change it from &Bullet to new Bullet (Woops)

______________________________________________________________________________________________________


Milestone 1 <V3> - 10/10/2012 
--------------------------------

New Functionality
-----------------

- Shooting of bullets


Code Additions
--------------

- GameObject - Will be using it for all entities in the game.
- Bullet class - Inherits from GameObject
- Analog shooting - excellent resouce at: http://goo.gl/mrWA0
- Chrono timer - To slow the time that bullets shoot

Tests
-----

- I ran a for loop vs memcpy and it seems that a for loop is quicker than a memcpy in Release mode.

Notes
-----

I found out I could remove the SDF files and a few other files to reduce the folder
size of my backup versions. Also, I found a way to stop VS from storing the SDF files
in the project all together at: http://goo.gl/2QS8j

______________________________________________________________________________________________________

08/10/2012 - Version 2:


Milestone 1 <V2> - 08/10/2012
--------------------------------

New Functionality
-----------------

- Screen clearing to different colours


Code Additions
--------------

- Screen clearing for loop/memcpy

Tests
-----

- I ran a for loop vs memcpy and it seems that a for loop is quicker than a memcpy in Release mode.

Notes
-----

NA

______________________________________________________________________________________________________

Milestone 1 <V1> - 03/10/2012
--------------------------------

New Functionality
-----------------

In this version, I simply played around with the API getting to know how it worked.
	
I managed to get "Hello World" bouncing around the screen as well as being able to
control the XY with the Xbox 360 Controller. As well as that I got the font colour
to change depending on the A, B, X and Y buttons as well as stop moving when pulling
LT.
	
I also played with getting a sound to work when moving the RS.


Code Additions
--------------

- HAPI Text
- Controller
- Sound

Tests
-----

- Bouncing text around screen
- Using the controller to move the text off the screen. Continues "bouncing" out of screen bounds.

Notes
-----

NA

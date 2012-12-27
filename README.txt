//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//              YouTube Video of Geometry Wars: http://youtu.be/d31d1HR_aUg             //
//                      In slow motion to see detail...                                 //
//                                                                                      //
//              	Check List: http://goo.gl/lzLSX					//
//                                                                                      //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//											//
//		Music: Majority of music borrowed from Geometry Wars			//
//			Music Created by: http://goo.gl/LwUWn				//
//////////////////////////////////////////////////////////////////////////////////////////


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

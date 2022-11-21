# GameEngine - 8INFI935 UQAC - Minh-Quân BUI, Jade Cothenet & Enzo Medina

Creation of a game engine from scratch with C++ / OpenGL / ImGUI
Logbook : https://docs.google.com/document/d/1gO0A0eiWZre2mizhjX-k-oEfsNzs0ubsiu3VJYyi8Rw/edit?usp=sharing

# Installation :

+ Open Visual Studio code
+ Click on "Create a new repos" 
+ Use this link "https://github.com/emkyu404/GameEngine.git" to clone the repos
+ When the project is open, click on the "main.cpp" then on the green arrow to execute the code.
+ A window will pop

If it's not working
+ Click right on "Game_Engine"
+ Then click on "regenerate"
+ Execute the main.cpp


# Phase 1 - Guide

+ A window is displayed with a triangle
+ Triangles represents particles
+ User is able to add up to 10 particles, with the same mass
+ User is able to enable gravity to be applied
+ User is able to enable another force to be applied (X, Y & Z values can be changed)
+ User is able to reset the initial position of particles

![image](https://user-images.githubusercontent.com/55577930/192173999-031dc309-1ec7-45a4-b9fa-180e8ec56033.png)

# Phase 2 - Guide 

+ User is able to remove particles
+ User is able to rotate and to move the camera with ZQSD/Arrows 
+ User is able to set the camera speed
+ User is able to see position/velocity/acceleration of each particle
+ User is able to add classic forces to each particles
+ User is able to add a spring force between particles
+ Particles have collisions now 

![image](https://user-images.githubusercontent.com/58985300/197421682-68e2c9ee-c746-476a-acd5-a45e87f72b2f.png)

# Phase 3 - Guide
+ User is able to influence physic objects position with sliders (X, Y and Z axis)
+ Camera is locked by default. To move the camera please press space bar
+ The demo scene has been setup in code. SpringForces for rigidbodies cannot be added otherwise for now
+ The demo sccene include 3 rigidbodies. Only the first one has forces applicated to it. You shall see one rigidbody rotating around the axis X. 
+ The forces used are : 2 spring forces, anchored at the side of the rigidbody. Grabity and drag forces are also used
+ Collisions have been disabled

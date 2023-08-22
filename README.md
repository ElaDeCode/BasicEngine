# BasicEngine

This program is a graphics/physics engine powered by OpenGL.

Press 'f' and move the mouse to rotate the cube.

To change the default scene, modify the sceneManager.c file.
(It contains the loadDefaultScene function.)

CMake is configured. If the project gains traction, I'll provide detailed installation instructions.

# dependencies:
  glfw3

# Engine is capable of:
  - Hard coded scene
  - Drawing nested cuboids, all located at (0,0,0).
  
  - You can move the camera by pressing 'f'.
          When you first press, the camera might jump to another angle.
          Hold 'f' to control rotation; mouse centers until release.
          so jumping is an artifact of the setting mouse position to center
  
  - (I accidentally deleted the live shader update part (with f5), but) the shaders are compiled at runtime.
  
  - Manual resource cleaning.
  - Cuboids can be easily added using code.
  - Easy to build with cmake
  
# todo:
  - Live updates (i have the code i just accidentally deleted)
  - Modify the projection matrix for better use of the OpenGL rendering area. (It causes objects outside the rendering box to disappear.)
  - Automatic resource cleaner

# long term goal:
  - Learning how to develop a substantial project.
  - Learning the fundamentals of live rendering
  - Mastering the c language
  - Creating a tool with 2D and 3D capabilities to enhance the efficiency of future project development.

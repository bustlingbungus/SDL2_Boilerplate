## SDL2 Boilerplate

This boilerplate will help serve as a starting point for developing projects with the SDL2 graphics libraries.

Thanks to [Robert Bruce](https://github.com/rdbruce) for sharing the majority of the LWindow and LTexture classes.

This code has been compiled and tested on a Windows 10 machine. While SDL is portable to other OS, this boilerplate has not been tested elsewhere.

## Included in this boilerplate are the following

### LWindow.hpp/cpp

- A basic window class that will hold global SDL variables, and will serve as the window that the programs actually gets rendered to and takes input from.
- Includes a gFont member, which will load a default font from file. This font will be used to render text when no font is provided.
    - Currently, this default font is [Press Start 2p](https://fonts.google.com/specimen/Press+Start+2P)
- When created, an LWindow will initialise SDL, and closes SDL in it's deconstructor. Therefore, only one LWindow can be created per project, and no SDL methods can be used when said window goes out of scope.

### LTexture.hpp/cpp

- A class that holds a SDL_Texture and a shared pointer to an LWindow. Member functions can be used to render the texture onto the window. Stores the dimensions of the texture.
- Member functions allow creation of textures by loading an image from a provided filename, creating a texture from a string of text, and creating a texture of solid colour.
- Frees itself when creating a new texture, and in it's deconstructor, ensuring no memory leaks. 
- The 'render' functions can be used to either render the texture into a specified rect on the window, or to render the texture at an (x,y) coordinate, rendered to fill the texture's dimensions.
    - The 'render' member functions include more parameters for more rendering options.

### LAudio.hpp/cpp

- A class that holds a Mix_Chunk audio pointer. By default will play it's stored audio to the next open audio channel.
- Allows for creation of an audio object by loading from a specified filepath, ```must be a .wav file!!!```
- Frees itself when loading new audio, and in it's destructor, to handle memory leaks.
- ```play``` will begin playing the audio from the next open channel by default. Only call this function once to begin playing audio.
    - Parameter 1 allows you to specify which channel to play the audio from. Channel 0 will not be used by default (specify 0 to use channel 0). This is to allow one channel to be reserved for things like music
        - If no channel is provided, the next open channel (excluding 0) will be used. By default, 8 different channels will be used. This can be changed by modifying the ```g_channel``` member in ```LAudio.cpp```
    - Parameter 2 allows you to specify the number of times the audio will loop. 0 by default (audio will play once). Set to -1 to have the audio loop infinitely.

### main.cpp

- The file that contains the program's entry point, do not change the name of this file. 
- Creates a new window, and enters a window loop until the user requests quit. Creates and renders a generic text texture, as an example.
- When creating a project, ```tex``` and ```tex->render``` in main.cpp can and should be removed. Everything else, (the window, the main loop, the event handling) should not be removed.
- Add code after the creation of ```window```. Add code into the main loop that will execute every frame. 
- For code that involves rendering, add it between the ```SDL_RenderClear``` and ```SDL_RenderPresent``` (where ```tex->render``` is).


## Build Instructions

### Dependencies
- C++ Compiler
- CMake
- Installation of ```SDL2```, ```SDL2_Image```, ```SDL2_ttf```, and ```SDL2_mixer```

### Instructions
Ensure there is a 'build' folder in your directory. Change to this directory with ```cd build```. From the build folder, run these commands:
```
cmake ..
cmake --build . --verbose
```
Then, run ```cd bin``` to go to the output directory, and run ```./project.exe``` to launch the game.

On VSCode, pressing ```ctrl+shift+b``` to run the included default build tasks should also work.

When developing your own projects, be sure to go to ```CMakeLists.txt```, and on line 7, replace 'project' with the name of your project. After doing this, wou will run your project with ```./[yourProjectName].exe```. If using build tasks to automate the build process, be sure to update line 37 in ```tasks.json``` to reflect this name change.
# SDL2 Boilerplate

This boilerplate will help serve as a starting point for developing projects with the SDL2 graphics libraries.

Thanks to [Robert Bruce](https://github.com/rdbruce) for sharing the majority of the LWindow and LTexture classes.

This code has been compiled and tested on a Windows 10 machine. While SDL is portable to other OS, this boilerplate has not been tested elsewhere.

## Included in this boilerplate are the following

### LWindow.hpp/cpp

- A basic window class that will hold global SDL variables, and will serve as the window that the programs actually gets rendered to and takes input from.
- Includes a gFont member, which will load a default font from file. This font will be used to render text when no font is provided.
  - Currently, this default font is 18 pt Arial
- When created, an LWindow will initialise SDL, and closes SDL in it's deconstructor. Therefore, only one LWindow can be created per project, and no SDL methods can be used when said window goes out of scope.

### LTexture.hpp/cpp

- A class that holds a SDL_Texture and a shared pointer to an LWindow. Member functions can be used to render the texture onto the window. Stores the dimensions of the texture.
- Member functions allow creation of textures by loading an image from a provided filename, creating a texture from a string of text, and creating a texture of solid colour.
  - On some systems there is a crash related to the `loadFromRenderedText` function, see the `Build Fix` section of this file.
- Frees itself when creating a new texture, and in it's deconstructor, ensuring no memory leaks.
- The 'render' functions can be used to either render the texture into a specified rect on the window, or to render the texture at an (x,y) coordinate, rendered to fill the texture's dimensions.
  - The 'render' member functions include more parameters for more rendering options.
- A texture may be rendered onto another texture using ```render_toTexture```, but note that this will only work if the target texture was created with ```SDL_TEXTUREACCESS_TARGET```. The only included method for this is ```solidColour```, but target access textures can be created with custom modifications to this code.

### LAudio.hpp/cpp

- A class that holds a Mix_Chunk audio pointer. By default will play it's stored audio to the next open audio channel.
- Allows for creation of an audio object by loading from a specified filepath, ```must be a .wav file!!!```
- Frees itself when loading new audio, and in it's destructor, to handle memory leaks.
- ```play``` will begin playing the audio from the next open channel by default. Only call this function once to begin playing audio.
  - Parameter 1 allows you to specify which channel to play the audio from. Channel 0 will not be used by default (specify 0 to use channel 0). This is to allow one channel to be reserved for things like music
    - If no channel is provided, the next open channel (excluding 0) will be used. By default, 8 different channels will be used. This can be changed by changing the definition of ```NUM_AVAILABLE_CHANNELS``` in ```LAudio.hpp```
  - Parameter 2 allows you to specify the number of times the audio will loop. 0 by default (audio will play once). Set to -1 to have the audio loop infinitely.

### LFont.hh/cpp

- A class used for font management. Contains a `TTF_Font` pointer that can be accessed with `get()`
- Contains methods for loading new fonts into the same object, as well as changing font size (which is done by reloading the same font file with a different point size).

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

``` bash
cmake ..
cmake --build . --verbose
```

Then, run ```cd bin``` to go to the output directory, and run ```./project.exe``` to launch the game.

On VSCode, pressing ```ctrl+shift+b``` to run the included default build tasks should also work.

When developing your own projects, be sure to go to ```CMakeLists.txt```, and on line 7, replace 'project' with the name of your project. After doing this, wou will run your project with ```./[yourProjectName].exe```. If using build tasks to automate the build process, be sure to update line 37 in ```tasks.json``` to reflect this name change.

### Build Fix

On some systems, there may be an issue when static linking to the SDL_ttf library. If you are getting a CMake error message about an `undefined reference to '_setjmp'`, there is likely an issue with your installation of the C standard library. Make sure you have a valid C++ compiler for your system , and that it is properly referenced in VSCode and CMake (This process is a huge pain, I'm sorry if this happens to you).

You can also try dynamically linking to SDL_ttf instead, by removing the `-static` property from line 26 of `CMakeLists.txt`. Line 26 should look like this for dynamic linking:

``` CMake
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)
```

Note that if you were having the `undefined reference to '_setjmp'` error, This fix might allow you to build the project, but will likely create a new error where calling the `loadFromRenderedText` function more than once will crash your application. If this is happening to you, again, you need to make sure your C++ compiler and the C standard library are both installed properly.

Hopefully this fix works!

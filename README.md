# Conway's Game of Life
### A recreation of the classic cellular automaton running on the GPU.
This project leverages the power of the fragment shaders in OpenGL 4.6 to update the cell state. It uses two SSBOs as maps for the cell state.

## How to compile this project

[MSYS2](https://www.msys2.org/) has been used to compile this project. You will need:
- gcc: `pacman -S mingw-w64-ucrt-x86_64-gcc`
- make: `pacman -S make`
- git: `pacman -S git`
- glm: `pacman -S mingw-w64-ucrt-x86_64-glm`
- glfw: `pacman -S mingw-w64-ucrt-x86_64-glfw`

**If you are compiling outside the msys2 environment, be sure to add `msys64\ucrt64\bin` and `msys64\usr\bin` to your environment variables' path**

**If you installed the above dependencies, you should have glm and GLFW folders in `msys64/ucrt64/include`, copy them into the project `include` directory.**

### Steps:

1. Clone this repository.
2. Run `make` in the root directory.
3. Run the executable *gol.exe*.

Crisp8-sdl is a reference frontend for the [crisp8](https://github.com/ahellqui/crisp8) backend using SDL2 for audio, video, input and things.

## Usage
Run the program and supply a rom file:

```sh
crisp8-sdl --rom <path-to-rom>
```

More options will arrive eventually.

## Building
Building crisp8-sdl requires a c compiler (mingw gcc on windows or you're on your own), make, cmake, SDL2 and SDL2_mixer. If you're on linux I trust you can install the libraries with your package manager, windows is more complicated.

First and foremost you have to clone this git repository to your local machine and cd into it, afterwards follow the instructions for your OS.

### Steps for Linux based operating systems
1. Create a build directory and cd into it
```sh
mkdir build
cd build
```
2. Execute cmake. This will also compile and set up linking to crisp8 which is included as a submodule. If you don't want this the easiest way is probably to remove the add\_subdirectory part of CMakeLists.txt. Now that I think about it I should probably add an option for that..
```sh
cmake ..
```
3. Execute make
```sh
make
```
4. Optionally execute make install to install the program to wherever you defined CMAKE\_PREFIX\_DIR to be
```sh
make install
```

If you only want to install crisp8-sdl and not crisp8 you can run
```sh
make install/local
```

5. Profit?

### Steps for windows
I appologize in advance to everyone who tries this. It works, but it is not fun.

1. Install the SDL2 development libraries for mingw from [here](https://www.libsdl.org/download-2.0.php) to a directory of your choice.
2. Install the SDL2_mixer development libraries for mingw from [here](https://www.libsdl.org/projects/SDL_mixer/) to a directory of your choice.
3. Create a build directory in your cloned crisp8-sdl directory and cd into it
```sh
mkdir build
cd build
```
4. Execute cmake and set `SDL2_DIR` to `<your-sdl2-installed-dir/cmake>`, `SDL2_MIXER_PATH` to `<your-sdl2_mixer-installed-dir>`
```
cmake -DSDL2_DIR:PATH="<your-sdl2-installed-dir>/cmake" -DSDL2_MIXER_PATH:PATH="<your-sdl2_mixer_installed_dir>" ..
```
5. Execute make (or mingw32-make or whatever you have installed)
```
mingw32-make
```
6. Execute make install. You *have* to do this on windows for it to find the libraries properly. Run make install/local If you only want to install crisp8-sdl and not crisp8 (this is probably what you want).
```
mingw32-make install
```
Or:
```
mingw32-make install/local
```

## NAQ (Never Asked Questions)
Q: Why doesn't this use the debugging interface of crisp8?

A: I didn't feel like writing a debugger.

Q: Why doesn't this include my question?

A: Asked questions don't belong in this section.

## License
GPL3

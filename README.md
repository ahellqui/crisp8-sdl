Crisp8-sdl is a reference frontend for the [crisp8](https://github.com/ahellqui/crisp8) backend using SDL2 for audio, video, input and things.

## Usage
Run the program and supply a rom file as the only argument.

```sh
crisp8-sdl <rom>
```

More options will arrive eventually.

## Building
Building crisp8-sdl requires a c compiler, make, cmake and SDL2.

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
5. Profit?

## NAQ (Never Asked Questions)
Q: Why doesn't this use the debugging interface of crisp8?

A: I didn't feel like writing a debugger.

Q: Why doesn't this include my question?

A: Asked questions don't belong in this section.

## License
GPL3

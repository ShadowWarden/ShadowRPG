# ShadowRPG

## Requirements for Development
- A linux distro. Preferably Ubuntu 14.04 or later. We've tested it on Ubuntu 14.04 64 Bit.
- Clone this Repository using git.  
`git clone git@github.com:ShadowWarden/ShadowRPG.git`
- Install the following SDL packages on your system.  
`sudo apt install libsdl2-2.0.0 libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-image-dev`
- Check out the relevant branch that you are working on or create a new one as desired.

## Instructions for using the Genesis map editor
- Navigate to src/genesis and make
- Navigate back to the root directory and run the program using ./genesis
- Type in the name of the map file to be imported (do NOT give the full path, only the file name).
- Move with wasd to replace tiles with '.'s and move with arrow keys to replace tiles with '#'s
- Press q to quit. You will be asked for a save name (which you have to provide. Discard changes will be patched in shortly). Again, only give the file name and not the path.

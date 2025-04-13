# Inverse kinematics

This is a proof of concept for an inverse kinematic arm with organic material linked to it
the inspiration comes from this plant in a 2D world, I only tried to recreate something similar in 3D https://rainworld.miraheze.org/wiki/Monster_Kelp#/media/File:Kelp_transparent.gif

To have the dangling part, I simply used my already existing [cloth simulation](https://github.com/emecdelam/cloth_sim)

The arm is made using FABRIK with a single iteration, it works pretty well for any simple and organic movement


[![Watch the video](https://img.youtube.com/vi/iIbM4RvuPs0/0.jpg
)](https://youtu.be/iIbM4RvuPs0)

# Red dot

The red dot is the target, right now it is only moving in a circular pattern


# Run it yourself :)

Simply download it and run
```sh
make
```
then

```sh
make run
```

If you have raylib installed, it should work


# General note

This is made as a proof of concept, there is a alot more work to make it usable in a game for example, I wouldn't recommend using the code for anything else than interest, if you plan on using this, try to remake it in a cleaner way, there are lots of way to make it faster, cleaner and more consistent
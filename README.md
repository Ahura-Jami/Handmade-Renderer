This repository contains all the records of me learning graphics programming and also building a
minimalist cross-platform library to be used in future projects.

# Dependencies

* X11 and xorg-dev

    GLFW requires X11 which on a linux system can be installed as follows:
    ```sh
    sudo apt-get install libx11-dev xorg-dev libglu1-mesa-dev
    ```
    see:
    > http://www.glfw.org/docs/latest/compile_guide.html#compile_deps_x11
    >
    > https://github.com/openMVG/openMVG/issues/85

    To find the OpenGL version on the machine run
    
    > glxinfo | grep "OpenGL version"
    
    if the `glxinfo` command is not found, instal the mesa-utils and try again.
    > apt-get install mesa-utils


#### Resources

* https://learnopengl.com/ - An amazing OpenGL tutorial website created by Joey de Vries.


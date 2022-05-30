# PLOTXT - Plot column arranged data from text files
The container provided in .devcontainer can be used to run ROOT and compile the macro.
To build the container:
```
$ docker build .devcontainer -t tridas-context:root -f Dockerfile-fedora
```
To run the container with display capabilities using X11 server on Linux:
```
$ docker run -it -v <absolute-path-to-this-dir>:/plot -v <absolute-path-to-data-dir>:/data --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" tridas-context:root
```
Data directory is a separate folder containing text files with data to plot.
Then, to compile:
```
$ mkdir build
$ cd build
$ g++ ../myplot.cpp `root-config --cflags --libs` -o myplot -lboost_program_options
```
And to see the usage and help

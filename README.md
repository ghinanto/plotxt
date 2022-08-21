# PLOTXT - Plot column arranged data from text files
The container provided in .devcontainer can be used to run ROOT and compile the macro.
To build the container:
```
$ docker build .devcontainer -t <name>
```
To run the container with display capabilities using X11 server on Linux:
```
$ ./set-graphics.sh docker run -it -v <absolute-path-to-this-dir>:/plot -v <absolute-path-to-data-dir>:/data --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" <name>
```
Data directory is a separate folder containing text files with data to plot.
Then, to compile:
```
$ mkdir build
$ cd build
$ g++ ../plotxt.cpp `root-config --cflags --libs` -o plotxt -lboost_program_options
```

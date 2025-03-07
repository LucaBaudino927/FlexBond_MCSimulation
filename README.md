## Compiling and launching
Open a terminal and change corrent directory to the project BUILD directory.
```bash
cd /home/luca/Progetto
mkdir build
cd build

```

First of all, load all libraries from the Geant4 install directory using:

```bash
source /home/luca/geant4-v11.3.0-install/bin/geant4.sh

```

Then to compile the program use:
```bash
cmake -DGeant4_DIR=/home/luca/geant4-v11.3.0-install/lib/Geant4-11.3.0/ -S /home/luca/Progetto/ -B .

```

```bash
make -j4

```

Finally, to launch the program and the GUI:
```bash
./exe_name

```


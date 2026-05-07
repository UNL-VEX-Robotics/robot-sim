# Robot Sim
This robot sim is created and used by members of the VURC team 'SKERS'. The purpose of the simulation is to aid in the development of localization and control algorithms for neblib. This simulation is 2-dimensional, preventing any use of cameras or other 3-dimensional localization algorithms.

## Dependencies
#### SFML
This simulation uses SFML 3.0.2 for windows and graphics. Developers must download SFML 3.0.2 and configure CMake with the location of this folder. A link to the download page can be found here:  https://www.sfml-dev.org/download/sfml/3.0.2/
#### nlohmann/JSON
This simulation uses nlohmann/JSON to read the `configure.json` file. This file is used to configure the simulation with information about the robot, fps, and more. CMake should automatically create a copy of the repository at https://github.com/nlohmann/json to use in `robot-sim/external/`.

## Assets
#### Fonts
`Arial-Rounded.ttf` - Font titled 'Arial Rounded'

## Config
#### `Mode`
Either `Localization` or `Movement`. Using localization will allow you to control the robot manually and is intended to be used to develope and test localization algorithms. Using movement will disable manual control of the robot but is intended to be used to develope autonomous movement algorithms.

#### `Framrate`
Integer for the max framerate. The VEX brain refreshes every 10 mS, a framerate of 100 FPS. Using 0 will result in an unlimited framerate, which is not recommended.

## VS Code Tasks
VS Code Tasks are git ignored. It is recommended to use at least these 3 tasks:
- CMake Configure
- Build
- Run

#### CMake Configure
```JSON
{
    "label": "CMake Configure",
    "type": "shell",
    "command": "cmake",
    "args": [
        "-S",
        "${workspaceFolder}",
        "-B",
        "${workspaceFolder}/build",
        "-DSFML_ROOT=D:/CodeProjects/Libraries/SFML-3.0.2"
    ]
}
```
Example CMake Configrue task.  
This task is important as it tells CMake where the SFML-3.0.2 folder is located.

#### CMake Build
```JSON
{
    "label": "CMake Build",
    "type": "shell",
    "command": "cmake",
    "args": [
        "--build",
        "${workspaceFolder}/build",
        "--config",
        "Debug"
    ],
    "group": {
        "kind": "build",
        "isDefault": true
    },
}
```
Example CMake Build task.  
This task builds the project into a single `.exe` file. By making the task the default build task, it becomes much simpler to use hotkeys to run the command. Build and Run are separated to allow the use of a debugger, which requires the project to be built.

#### Run
```JSON
{
    "label": "Run",
    "type": "shell",
    "command": "${workspaceFolder}/build/Debug/robot_sim.exe",
    "dependsOn": "CMake Build",
    "group": {
        "kind": "test",
        "isDefault": true
    }
}
```
Example Run task.  
This task will call the build task and then launch the resulting `.exe` file.

## elements.json
You can configure the different elements (buttons, etc) using JSON. You still need to call the constructor using the the title of the object, but the other information will automatically get read from the JSON file.
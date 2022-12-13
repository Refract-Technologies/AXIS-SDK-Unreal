
  
# Introduction

Axis is a real time Low-latency Full-body Tracking system. To use the plugin, you must have Axis Control Center installed and running, and also must have calibrated your Axis System.

# About

This README contains a short tutorial on how to use the Axis Unreal SDK plugin.

## Supported Platforms 
This plugin was built against **Unreal Engine 4.25**. It currently only works on Windows and we plan to make it available on other platforms in the future.

## How To Use

You use this plug-in as a project plug-in.

First, choose a **C++ Project** in Unreal. Then in your newly created project folder, create a Plugins directory with a AxisPlugin folder in it. Clone this repository into the _Plugins/AxisPlugin_ directory.  The directory will look something like this.

```
|_ Plugins
	|_ AxisPlugin
		|_ Contents
		|_ Source
		|- AxisPlugin.uplugin
```

Take note that a C++ code project is required for this to work as you have to build the plugin based on Unreal Version.

After cloning, you are required to re-open the unreal project so that the plugin can be build be re-configured. (The plug-in is configured to be enabled by default once it's in your game's plug-in directory.)

Once the project is opened, There is a demo scene in Axis Plugin content's Demo folder called **Axis_Demo_Brain_Mannequin** which you can explore.

In the World Outliner, you will find **X_bot** actor and **khan_character01** actor. Both have the Axis mannequin component attached. If you have already turned on and calibrated your Axis set, you can press Play button and the characters will move according to your movements. Once done testing and you want to make changes, press Stop Button to stop playback.

In Axis mannequin, you can find 4 variables you can toggle, which are 

- *Hub multiplier*
	 > value to control the distance moved by the mannequin. For example, 1 meter in real life translate to 2 meter in-game.
- *Update position*
	> boolean flag - If enabled, actor's position will be updated based on phone position. If false, actor's position will NOT be updated.
- *Update hub rotation*
	 > boolean flag - If enabled, the actor's bone that is bind to the Hub will be updated based on phone position. If false, actor's bone will NOT be updated.
- *Update Nodes*
	 >  boolean flag - If enabled, the actor's bone that is bind to the Nodes will be updated based on Nodes rotation. If false, actor's bone will NOT be updated.

In the World Outliner, there is an Actor called **Brain** and it have a **Axis_Brain** Component attached to it. This is the main component which receives Nodes and Hub movement data from the hardware. 

Additionally, it contains a list of actors with an **Axis Mannequin** component that will receive the data of the nodes and the hub.  Kindly note that **only the actors in this list will get updated node and hub data**.

Lastly, to make the mannequin move, it requires an **Animation Blueprint** attached to the Actor's SkeletalMeshComponent. There is a BP_Axis_X_Bot which you can see as a reference.

In the BP_Axis_X_Bot Animation Blueprint, there is a **Axis Mannequin Pose Node** which is connected to the Output Pose. In the details of the Axis Mannequin Pose, you will find the nodes that are bind to the specific bones of the skeleton.

This Axis Mannequin Pose Node can be found by right clicking anywhere in the animation blueprint and search under **Axis Tab**.



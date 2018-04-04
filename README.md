“I am [Adrià Ferrer](www.linkedin.com/in/AdriaFerrerC), student of the
[Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/).
This content is generated for the second year’s subject Project 2, under supervision of lecturer
[Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).”

Explanation on the current existing cutscene editors

Data driven code with generic approach

TODOs to both use and code the system

# Cutscenes
<p align="center">
“A cutscene is a sequence in a video game that is not interactive, breaking up the gameplay.”
</p>

They are usually used to show conversation between characters, set the mood and introduce new gameplay features or incoming events.
There are two main types of cutscenes.

The ones rendered in **real time** that use the game graphic enginge to create scripted events and **pre-rendered** video or "cinematic".
<p align="center"> 
<img src="https://j.gifs.com/Q0q4G7.gif" width="400">
<img src="https://i.ytimg.com/vi/FfQ2GCgCFQ8/maxresdefault.jpg" width="400">
</p>

Although, there are some more types like:

  - **Live-action cutscenes**, which are recorded like a film.
<p> 
<img src="https://i.ytimg.com/vi/dnC87rzStIo/maxresdefault.jpg" width="400">
</p>

  - **Mixed media cutscenes**, which, as the name says mixes real time and pre-rendered graphics.
<p> 
<img src="https://j.gifs.com/wm8W6m.gif" width="400">
</p>

  - **Interactive cutscenes** also known as quick time events.
<p> 
<img src="https://i.kinja-img.com/gawker-media/image/upload/s--UjIyKaTi--/c_fill,f_auto,fl_progressive,g_center,h_675,q_80,w_1200/18grs10k0sa5pjpg.jpg" width="400">
</p>

# Pre-rendered vs Real-time
Let's see and compare the pros and cons of both pre-rendered and real-time cutscenes.

The pros of pre-rendered cutscenes are mainly based on the higher capability of creating stuff without resources restriction, just limited to human imagination and ability and to create complex animations, for example physics simulations like fluids or cloth deformation.

In the other hand, real-time has more freedom of what to show in screen, for example if the player has chosen to equip his character with a blue cape instead of a red one, it will be seen in the cutscene, whereas in pre-rendered, the characters and the environment is fixed at the moment it is created and will not change whatever the player does.

However, real-time graphics are limited to the game graphic engine which is suposed to have worse quality than pre-rendered graphics (although nowadays this difference is becoming less and less) and the animations are also limited to the ones "in-game", which tend to be much simplier.
For the same reason, when swapping from gameplay to real-time cutscenes, there is no noticeable change in graphic quality and helps the player to keep immersed into the game. By contrast, with pre-rendered scenes, adding that the characters appearance could change from the gameplay, the player could lose his focus and as a result the feeling of immersion.

Talking about the resources spent for every kind of cutscene, pre-rendered use disk memory as it weights much more than the code lines but if compresed too much, it will lose a lot of quality and could look even worse than in-game graphics.
Real-time, consumes RAM and CPU usage as it is making calculations and moving things at the moment.

With all the factors seen above, we can conclude that pre-rendered cutscenes are usefull for advertising as they can look really fancy and cool, for the presentation or the end of the game as well as some scenes at the beginning of specific misions where it does not crash with the gameplay graphics and even it is used to mask loading times, as it does not consume much resources it can be executed simlutaneously while the program is loading the next map/scene and the player will not be exasperated or bored of waiting too much time.
Finally, real-time is good for "in-game" scenes so the player feels a continuity and do not lose the focus. Even more if there is a huge degree of personalization on the environment or the characters/weapons used as it can be easily represented in the cutscene.

The problem with real-time cutscenes, is that there are a lot of factors that could influentiate the behaviour of the scene, for example things or characters that should not be there as we saw in the example of GTA V above. Also, every bug that can happen during the game, can happen during the cutscene for example with colliders, where a character can be stuck and then teleport or stretch in an inhuman way.

As higher is the degree of freedom of the game, the higher the chances that some nasty things occur during the cutscene.
Is for that reason, that the cutscene manager is a really important tool and needs to be well designed and give as much control over every single element as possible.

# Existing cutscene editors
Now we are going to look at two existing engines and their different approach for creating cutscenes.

### Unity
Since Unity version 2017.2 it includes a native cutscene editor called "Timeline" it is a sequencer of multitracks that allows to create gameplay sequences controling game objects, it is prepared to work with a free plugin called [Cinemachine](https://assetstore.unity.com/packages/essentials/cinemachine-79898) which is a procedural camera system that grants absolute control over camera movements, transitions between several ones and effects.

Also, there are some paying plugins created by community developers that can do the same or even more.
For example [Cinema Director](https://assetstore.unity.com/packages/tools/visual-scripting/cinema-director-timeline-cutscene-editor-19779) which through the same use of a timeline, allows to control game objects, camera position and switches, sound effects and transitions in an easy and intuitive way.
### Unreal Engine
In Unreal engine, there is a tool called Matinee, it works pretty similar to the Unity one. There is a timeline where you can crate multiple tracks, each related to a game asset. There, you can add keyframes with a different state in each and the engine will create a smooth transition between them and a cinematic effect.

## The common use of a timeline
Both of them have something in common, they use a timeline to create the cutscenes; however, they use it differently.
Unity uses "blocks" with some function related, they have a start time and a duration. They can also be overlapped between them in order to create a smooth fadding transition when changing.
As in this example image. We can see in blue, the animations that will be executing for the attacker 1, in orange, each sound effect or music and in green, whether a game object will be active or not. It is like any simple video editor.
<p align="center"> 
<img src="https://forum.unity.com/attachments/timelineexample-dark-png.218796/" width="800">
</p>

Then you can access a game object, specially used with cameras and enter the animation function, which allows you to create an animation by saving keyframes of the state of the object and then use it in the timeline. This function is basically what is used in Unreal engine, where you do not create blocks of functions/events but save keyframes of the different changes that happen during the scene to create a "big animation".
<p align="center"> 
<img src="https://i.imgur.com/wTcMqjL.png" width="800">
</p>
<p align="center"> 
  <em> Each red arrow is a keyframe </em>
</p>


# Let's code
### Which is our objective
(How our manager will work)
(data driven from xml)
### What we need and what we have
(Explain the base code)
### Coding main functionalities
(Start reading the xml, explain the syntax used and code at least one function to show how it is suposed to be done)
### Code yourself
(Some tasks so they understand and internalize the manager and the code)
#### TODO 1
#### TODO N

# Bibliography
[https://en.wikipedia.org/wiki/Cutscene](https://en.wikipedia.org/wiki/Cutscene)

[https://wiki.unrealengine.com/Matinee_Basics:Creating_Your_First_Matinee_Sequence](https://wiki.unrealengine.com/Matinee_Basics:_Creating_Your_First_Matinee_Sequence)

[https://unity3d.com/es/learn/tutorials/topics/animation/using-timeline-overview?playlist=17099](https://unity3d.com/es/learn/tutorials/topics/animation/using-timeline-overview?playlist=17099)

[https://docs.unity3d.com/Manual/TimelineSection.html](https://docs.unity3d.com/Manual/TimelineSection.html)

[https://docs.unity3d.com/Manual/TimelineOverview.html](https://docs.unity3d.com/Manual/TimelineOverview.html)

[https://docs.unrealengine.com/en-us/Engine/Matinee](https://docs.unrealengine.com/en-us/Engine/Matinee)

[https://unity3d.com/es/learn/tutorials/topics/animation/cinemachine-clear-shot-camera-tutorial](https://unity3d.com/es/learn/tutorials/topics/animation/cinemachine-clear-shot-camera-tutorial)
## Interesting links:
[Cutscene as an information system](https://link.springer.com/chapter/10.1007/978-3-319-07626-3_62)

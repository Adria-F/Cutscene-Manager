“I am [Adrià Ferrer](www.linkedin.com/in/AdriaFerrerC), student of the
[Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/).
This content is generated for the second year’s subject Project 2, under supervision of lecturer
[Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).”

Wide intro into the pros/cons of different cutscene systems

Explanation on the current existing cutscene editors

Data driven code with generic approach

TODOs to both use and code the system

# Cutscenes
<p align="center">
“A cutscene is a sequence in a video game that is not interactive, breaking up the gameplay.”
</p>

They are usually used to show conversation between characters, set the mood and introduce new gameplay features or incoming events.
There are two main types of cutscenes.

- The ones rendered in **real time** that use the gameplay graphics to create scripted events.
<p align="center"> 
<img src="https://j.gifs.com/Q0q4G7.gif" width="600">
</p>

- **Pre-rendered** video "cinematic".
<p align="center"> 
<img src="https://i.ytimg.com/vi/FfQ2GCgCFQ8/maxresdefault.jpg" width="600">
</p>

Although, there are some more types like:

- **"Live-action cutscenes"**, which are recorded like a film.
<p align="center"> 
<img src="https://i.ytimg.com/vi/dnC87rzStIo/maxresdefault.jpg" width="600">
</p>

- **"Mixed media cutscenes"**, which, as the name says mixes real time and pre-rendered graphics.
<p align="center"> 
<img src="https://j.gifs.com/wm8W6m.gif" width="600">
</p>

- **"Interactive cutscenes"** also known as quick time events.
<p align="center"> 
<img src="https://i.kinja-img.com/gawker-media/image/upload/s--UjIyKaTi--/c_fill,f_auto,fl_progressive,g_center,h_675,q_80,w_1200/18grs10k0sa5pjpg.jpg" width="600">
</p>

# Pre-rendered vs Real-time
The problem with pre-rendered graphics is that they cannot change according to the game state. However, real time cutscenes are specially thought for that, so the components of the scene will change in order to visualize the game state and the action that the player has done, so he feels more relevant to the game and more immersed. For example, if he has chosen to equip his character with a blue cape instead of a red one, it will be seen in the cutscene.
So, we will focus on the creation of a real time cutscene manager.

# Bibliography
Links
## Interesting links:
[Cutscene as an information system](https://link.springer.com/chapter/10.1007/978-3-319-07626-3_62)

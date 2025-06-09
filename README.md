# KanderCraft

**KanderCraft** is a game inspired by Minecraft. It is made in **C** using the **Raylib** graphics library and **stb\_perlin** for Perlin noise generation.

---

## Features and Optimization

This game includes some useful features and optimizations that help it run better.

### Optimization

#### Face Culling

Only the outside faces of blocks are drawn. Hidden faces inside blocks are not shown. This improves the game's speed.

#### Frustum Culling

A big performance improvement comes from [Frustum Culling](https://learnopengl.com/Guest-Articles/2021/Scene/Frustum-Culling). The camera creates a view area (frustum) with a near and far plane. Chunks have collision boxes. If a chunk is inside the frustum, it will be drawn.

![game2](https://github.com/user-attachments/assets/c67ef9d4-6da0-4d78-97cb-c75ada7bbc3e)

```bash
        _________ <-- far plane
        \   :)  /
         \     /        <-- FOV cone
          \   /
           \ /
           ---          <-- near plane
       camera (you)
```

---

## World System

The world is saved as chunks. Each chunk has:

* A collision box
* A list of blocks

Each block has properties like:

* Visible
* Solid
* Opaque
* And others...

Each block also has its own small collision box, used for detecting hits.

---

## Camera Ray System

A ray is used to destroy or place blocks, similar to Minecraft.

* The ray hits a block and saves it to a `Collision` structure.
* Left click: destroy the block.
* Right click: place a block **next to** the one hit.

The `GetHitNormal` function helps by checking which side of the block was hit, and moves the position one block outward.

**Debug camera view:**
![game3](https://github.com/user-attachments/assets/d95d747e-83c4-4954-8776-863b35725277)

**All block collision boxes shown:**
![game4](https://github.com/user-attachments/assets/89f9b3a3-d3a9-483b-a816-e55e04e7b6c7)

---

## World Generator

* The world is made with Perlin noise, which creates smooth hills.
* The hills are stretched to make a mostly flat world.
* Each chunk is saved as a `.dat` file.

![game1](https://github.com/user-attachments/assets/f6b7d000-d436-42b1-90ef-b67eedb7afb3)
![game5](https://github.com/user-attachments/assets/4f8bc3ae-777f-476c-968c-1f43cfea8385)

---

## Controls

| Key         | Action                   |
| ----------- | ------------------------ |
| F3          | Toggle debug menu        |
| U           | Toggle debug camera      |
| Hold H      | Show all collision boxes |
| Mouse Wheel | Change block type        |
| J / N       | Change camera FOV        |
| F11         | Toggle window borders    |
| W A S D     | Move                     |

* You can change the world icon: go to `WorldFiles/[your world name]/Icon/Icon.png`
* In the `game_settings` folder, you can set your player position or render distance.

![menu1](https://github.com/user-attachments/assets/53ce94fb-92ec-4ba6-9a9c-310b0750a4a8)

---

## Known Issues / To Do

* World size is small: only 8x8 chunks
* Add fog
* Improve the menu
* More optimization

---

Not everything is explained here. You can look at the code or try the game.
If you have ideas or find bugs, contact me :) :

**Email:** [jansa063@gmail.com](mailto:jansa063@gmail.com)

---

**Made by Kander (Jakub Jansa)**
Free software under the **BSD-2-Clause license**

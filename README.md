
---

# 🎮 ULTRA MEGA SUPER DUPER PONG

> *"The legend returns. 8 years in the making. The definitive revival of the game that started it all."*

---

## 🧾 Overview

**PONG: Resurgence** is a fully-featured modern reimagining of the classic arcade game, developed natively for the Nintendo Switch Homebrew ecosystem. Built from the ground up with `libnx`, this project honors the pure spirit of *PONG*, while introducing sleek game modes, responsive controls, and refined mechanics — all in a lightweight, responsive native app.

This is not just another port.
This is a rebirth.

---

## 🚀 Features

* 🎮 **Two Game Modes**
  Choose between:

  * **Single Player**: Battle against a calculated AI opponent.
  * **Two Player Mode**: Challenge a friend in couch competition — using a single Joy-Con!

* 🧠 **Adaptive AI (Single Player Mode)**
  The CPU moves with subtle imperfection, creating a fair and exciting challenge — not just blindly chasing the ball.

* 👥 **Two Player Controls**

  * Player 1: Uses D-Pad or Left Stick (Up/Down)
  * Player 2: Uses `X` (up) and `B` (down)

* 🖼️ **Clean UI**

  * Elegant start screen with "Press + to Start"
  * Game mode selection with smooth transitions
  * Score display always visible at the top

* 🧱 **Polished Gameplay**

  * Solid collision mechanics
  * Speed scaling for balanced difficulty
  * Visual top/bottom boundaries as white lines

* 💾 **Built with libnx**
  Runs directly on real Nintendo Switch hardware — no emulation, no SDL layers. Pure performance.

---

## 🕹️ Controls

| Action           | Button                |
| ---------------- | --------------------- |
| Start Game       | `+`                   |
| Quit Game        | `-`                   |
| Move Paddle (P1) | `↑ / ↓`               |
| Move Paddle (P2) | `X` / `B`             |

---

## 📦 Installation

1. Build using [devkitPro](https://devkitpro.org) and `libnx`.
2. Place the `.nro` file on your SD card.
3. Launch via `hbmenu`.

**Optional**: Add `icon.jpg` and NACP metadata to customize how the game appears in the Homebrew Menu (see Makefile settings).

---

## 🔧 Build Details

* Language: **C**
* Library: **libnx**
* Platform: **Nintendo Switch (Homebrew)**
* Input: `padConfigureInput`, `padUpdate`, `padGetButtonsHeld`
* Rendering: `consoleUpdate` (text mode)

---

## 📜 Credits

* **Developer**: *Kriperovih*
* **Concept**: Inspired by Atari's original PONG
* **Engine**: Custom-built using `libnx`
* **Special Thanks**: The [devkitPro](https://devkitpro.org) and [switchbrew](https://switchbrew.org) communities

---

## 🌌 Legacy

> "We waited. We hoped.
> And now, in the year 2025, PONG is reborn."

PONG: Resurgence is a love letter to the origins of video games — carefully reengineered for a modern handheld generation. Whether you're reliving your childhood or discovering the magic of minimalist gaming for the first time, **PONG: Resurgence** invites you to one simple promise:

> No microtransactions.
> No loading screens.
> Just pure, competitive fun.

---

## 🧠 Fun Fact

i make this game in 3 months and 1 hour:

2 months of learning c

1 mounth of learning devkitpro

1 hour of making the game

---

Let me know if you'd like this bundled into a `README.md` file or want to include screenshots, GitHub badges, or even gameplay GIFs!

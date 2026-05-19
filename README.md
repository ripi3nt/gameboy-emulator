# 🎮 gb-term

> A Game Boy emulator that runs in your terminal.

---

## ⚠️ Disclaimer

This is a **learning project**. It was built to explore emulator development, low-level CPU emulation, and terminal rendering. As such:

- There **will be bugs and inaccuracies** in the emulation
- Some games may not run correctly or at all
- Performance is **not yet optimized** — expect rough edges
- Accuracy to the original hardware is a work in progress

This project is not intended to be a production-quality emulator. It's a hands-on way to learn how the Game Boy works from the ground up.

---

## 📖 About

`gameboy-emulator` is a Game Boy (DMG) emulator written in C/C++ that renders entirely in the terminal.

---

## ✨ Features

- **CPU**: Sharp SM83 (LR35902) instruction set emulation
- **Display**: Rendered in-terminal via Terminal graphics protocol
- **Input**: Keyboard-mapped Game Boy controls
- **Memory**: Basic MBC1/ROM-only cartridge support
- **Audio**: *(planned / not yet implemented)*

---

## 🖥️ Requirements

- A Unix-like system (Linux / macOS)
- A terminal with 256-color support
- Terminal supporting `Terminal graphics protocol` (ex. kitty)
- `gcc` or `clang` with C11 support (or C++ equivalent)
- `make`

Install kitty on Debian/Ubuntu:
```bash
sudo apt install kitty
```
---

## 🔧 Building

```bash
git clone https://github.com/ripi3nt/gameboy-emulator.git
cd gameboy-emulator
make
```

The binary will be output to `./build/gb-term`.

---

## 🚀 Usage

```bash
./build/gb-term path/to/rom.gb
```

### Controls

| Key         | Game Boy Button |
|-------------|-----------------|
| `Arrow keys`| D-Pad           |
| `Z`         | A               |
| `X`         | B               |
| `Enter`     | Start           |
| `Backspace` | Select          |
| `Q`         | Quit            |

---
## 🧠 References & Learning Resources

These resources were invaluable while building this emulator:

- [Pan Docs](https://gbdev.io/pandocs/) — The definitive Game Boy technical reference
- [gbdev.io](https://gbdev.io/) — Community resources and test ROMs
- [Blargg's test ROMs](https://gbdev.gg8.se/files/roms/blargg-gb-tests/) — For validating CPU accuracy

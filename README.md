# Stock Fish of My Heart

A UCI-compatible chess engine written in C++20 from scratch, with a bitboard
board representation, magic-bitboard move generation, and an alpha-beta
search stack with iterative deepening.

## Features

**Move generation**
- Bitboard board representation (one 64-bit board per piece type/color)
- Magic bitboards for sliding piece (rook/bishop/queen) attack generation
- Full legal move generation (pseudo-legal generation + check filtering)
- Castling, en passant, and promotion all handled

**Search**
- Alpha-beta negamax
- Iterative deepening with time control (searches until the clock runs out,
  not to a fixed depth)
- Quiescence search at leaf nodes (capture-only extension, with full
  check-evasion handling when the side to move is in check)
- Transposition table (Zobrist hashing, exact / lower-bound / upper-bound
  entries)
- Move ordering: hash move, MVV-LVA for captures, killer moves, history
  heuristic
- Threefold repetition and fifty-move-rule draw detection

**Evaluation**
- Material counting
- Tapered piece-square tables (separate midgame/endgame tables, blended by
  game phase)
- Bishop pair bonus
- Rook on open/semi-open file bonus

**Interface**
- Speaks the [UCI protocol](https://en.wikipedia.org/wiki/Universal_Chess_Interface),
  so it works with any standard chess GUI
- Perft utility (`Preft.cpp`) for verifying move generation correctness
  against known node counts (see [Testing move generation](#testing-move-generation))

## Building

Requires a C++20 compiler and CMake 3.21+.

### Visual Studio 2022 (Windows)

1. Open the folder in Visual Studio: **File → Open → CMake...**
2. Select the **windows-msvc** configure preset.
3. Pick a build configuration (Debug / Release / Dist) from the toolbar.
4. Build with **Ctrl+Shift+B**.

The binary lands at `out/build/windows-msvc/App/<config>/App.exe`.

### VS Code (Windows, macOS, or Linux)

1. Install the **CMake Tools** extension (and the **C/C++** extension for
   IntelliSense).
2. Install [Ninja](https://ninja-build.org/) and make sure it's on your
   `PATH`:
   - Windows: `choco install ninja` (or let CMake Tools auto-download it
     when prompted)
   - macOS: `brew install ninja`
   - Linux: `sudo apt install ninja-build` (or your distro's equivalent)
3. Open the project folder in VS Code.
4. Run **CMake: Select Configure Preset** from the command palette and
   choose **default**.
5. Run **CMake: Select Variant** (or use the status bar) to pick
   Debug / Release / Dist.
6. Build with **Ctrl+Shift+B**, or via the CMake Tools status bar.

The binary lands at `out/build/default/App/<config>/App` (or `App.exe` on
Windows).

> `CMAKE_EXPORT_COMPILE_COMMANDS` is enabled in the `default` preset, so
> IntelliSense/clangd will pick up the project's actual include paths and
> defines automatically.

### Command line (any OS)

```sh
cmake --preset default
cmake --build out/build/default --config Release
```

> **Always build Release or Dist for actual play or testing.** Debug builds
> are significantly slower and will reach far less search depth in the same
> time budget — this matters a lot for a chess engine specifically, since
> playing strength is directly tied to nodes searched per second.

## Usage

`App` speaks UCI. Load it into a GUI, or drive it manually from a terminal:

```
uci
isready
position startpos
go wtime 60000 btime 60000 movestogo 30
```

It should respond with `id name`/`id author`, `uciok`, `readyok`, and
eventually a `bestmove` line.

### Recommended: use a GUI

Typing raw UCI commands is fine for quick checks, but a GUI lets you
actually watch the engine play and makes bugs far easier to spot visually.
Good free options that speak UCI:


- [CuteChess](https://cutechess.com/) (cross-platform support)
- [Nibbler](https://github.com/rooklift/nibbler)

Point the GUI's "install engine" dialog at your built `App`/`App.exe`.


## License

See [UNLICENSE.txt](UNLICENSE.txt).

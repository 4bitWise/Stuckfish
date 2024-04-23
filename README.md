# Stuckfish

Stuckfish is intended to be a desktop application (potentially available through a website via our Makefile WASM compilation). It's a chess game reviewer written in C++ with Dear ImGui. Our goal is to develop a software that is both fast and free, featuring an appealing user interface and delivering precise game analysis.

## Installation

We’ve made the .exe file available directly in the repository “Releases”.

### **Build from source**

**Windows requirements**

- On windows, you need to install **[Emscripten](https://emscripten.org/docs/getting_started/index.html)**. “*Emscripten is a complete [Open Source](https://emscripten.org/docs/introducing_emscripten/emscripten_license.html#emscripten-license) compiler toolchain to WebAssembly.*” It allows us to “*compile C and C++ code, or any other language that uses LLVM, into [WebAssembly](https://developer.mozilla.org/en-US/docs/WebAssembly), and run it on the Web, Node.js, or other Wasm runtimes. Practically any **portable** C or C++ codebase can be compiled into WebAssembly using Emscripten, ranging from high-performance games that need to render graphics, play sounds, and load and process files, through to application frameworks like Qt. Emscripten has already been used to convert a very long list of real-world codebases to WebAssembly, including commercial codebases like the [Unreal Engine 4](https://blog.mozilla.org/blog/2014/03/12/mozilla-and-epic-preview-unreal-engine-4-running-in-firefox/) and the [Unity](https://blogs.unity3d.com/2018/08/15/webassembly-is-here/) engine.*”
In order to get Emscripten on windows, you need to run the `emsdk.bat` commands using an elevated shell (you can execute the cmd.exe as administrator). Otherwise, the path is not updated. [Get Emscripten now !](https://emscripten.org/docs/getting_started/Tutorial.html#running-emscripten)
- Install `make` on windows using `chocolatey` (a package manager). This installation **absolutely** necessitates executing the commands in an elevated shell to update your system path variable. (Run the `powershell.exe` as admin)

### **Troubleshooting**:
For the WASM aspect, we've chosen a frequently asked question and provided the same response found in Emscripten's FAQ.

✨ **How do I run a local webserver for testing / why does my program stall in "Downloading…" or "Preparing…"?** <br/> 
That error can happen when loading the page using a `file://` URL, which works in some browsers but not in others.
Instead, it’s best to use a local webserver. For example, Python has one built in, `python -m http.server` in Python 3 or `python -m SimpleHTTPServer` in Python 2.
After doing that, you can visit `http://localhost:8000/`. You can also use `emrun FILENAME.html` (which will run a python webserver for you).
When doing quick local testing, another option than a local webserver is to bundle everything into a single file, using `-sSINGLE_FILE` (as then no XHRs will be made to `file://` URLs).

### **Features we are working on**:

- List all the games played in the current month using the [Chess.com](http://Chess.com) API and player username.
- Implement a "<" button on the list popup page to view the games from previous months.
- Click on a game from the list to load it onto the board.
- Notify when the game evaluation is complete.
- Ability to define the depth of Stockfish's analysis.
- Buttons to navigate to the next move or go back to the previous one.
- Display the opening played by each player.
- Display the summary of the game's movements in the form of a [chess.com](http://chess.com/) list, detailing the precision of both players and indicating the winner.
- Display the status for each move (blunder, inaccuracy, miss, good, great, excellent, brilliant).

PS: We are still in the development phase and work on it during our spare time.

**Stockfish API docs**: [StockfishOnline | Stockfish REST API](https://stockfish.online/docs.php) <br/>
**Chess.com API docs**: [Published-Data API - Chess.com](https://www.chess.com/news/view/published-data-api)

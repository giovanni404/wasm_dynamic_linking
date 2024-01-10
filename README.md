# wasm_dynamic_linking

WebAssembly Dynamic Linking using [**Emscripten**.](https://emscripten.org/docs/compiling/Dynamic-Linking.html)

## Background

While the goal is to show how to build a WASM application that links to its WASM modules dynamically at run time, first we'll show how to statically link the WASM modules to the WASM application at time of build, for comparison purposes.

[Read this slightly outdated article for additional background.](https://yushulx.medium.com/webassembly-building-standalone-and-dynamic-linking-modules-in-windows-bd4492d0688f) Then look below for sequence of commands and updated arguments.

## Main Project Files

1. main.c - WASM application
2. foo1.c - WASM module
3. foo2.c - WASM module
4. pre.js - Contains the list of WASM modules that need to be preloaded (for dynamic linking to at run time) when the WASM application runs in a Web Browser

## Build a standalone WASM application containing WASM modules statically linked at buildtime:

### For running in a WASI Runtime (e.g., **wasmtime**)

```
$emcc main.c foo1.c foo2.c -o main.wasm
```

The generated wasm file doesn’t depend on an Emscripten JS runtime. We can run it in wasi-supporting runtimes, such as **wasmtime**:

```
$wasmtime main.wasm 
hello world 3
```

### For running in a Web Browser (e.g., **Chrome**)

```
$emcc main.c foo1.c foo2.c -o main.html
```

In this case the generated WASM file depends on a JavaScript Engine for execution. Run the HTML and WASM files using a Web Browser like **Chrome**:

```
$emrun main.html --browser "/mnt/c/Program Files (x86)/Google/Chrome/Application/"chrome.exe
```

#### Web Browser Output

![Web Browser Output image is supposed to appear here](images/browser.png "Web Browser Output")

## Build a WASM application and the WASM modules it needs to link to (independantly of each other):

### For running in a WASI Runtime (e.g., **wasmtime**)

```
TODO: Figure out how dynamic linking works in a WASI environment.
```

### For running in a Web Browser (e.g., **Chrome**)

```
$emcc foo1.c -s SIDE_MODULE=1 -o foo1.wasm
$emcc foo2.c -s SIDE_MODULE=1 -o foo2.wasm
```

These SIDE_MODULE can be dynamically linked to the WASM application a.k.a. MAIN_MODULE, in 2 ways:

1. Dynamically link WASM modules to WASM application at load time

```
$emcc main.c -s MAIN_MODULE=1 foo1.wasm foo2.wasm -o main.html
```

2. Dynamically link WASM modules to WASM application at run time

```
$emcc main.c -s MAIN_MODULE=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 --pre-js pre.js -o main.html
```

In both cases, the generated WASM file depends on a JavaScript Engine for execution. Run the HTML and WASM files using a Web Browser like **Chrome**:

```
$emrun main.html --browser "/mnt/c/Program Files (x86)/Google/Chrome/Application/"chrome.exe
```

#### Web Browser Output

**Note:**
For both these 2 cases, Web Browser output should be identical to that of the standalone WASM application (shown above), however for dynamic linking at run time to work, the modified main.js source code with the list of 'dynamicLibraries' to preload, must successfully execute!

![JavaScript Source Code image is supposed to appear here](images/js-src.png "Modified JavaScript source code containing list of 'dynamicLibraries' that must be preloaded")

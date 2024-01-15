# wasm_dynamic_linking

WebAssembly Dynamic Linking using [**Emscripten**.](https://emscripten.org/docs/compiling/Dynamic-Linking.html)

## Background

There are 3 way to do dynamic linking with WebAssembly:
1. Your C or C++ code can manually link to a module by using the ```dlopen``` function.
2. You can instruct Emscripten that there are WebAssembly modules to link to by specifying them in the ```dynamicLibraries``` array of Emscripten’s generated JavaScript file. When Emscripten instantiates the WebAssembly module, it will automatically download and link modules that are specified in this array.
3. In your JavaScript, you can manually take the exports of one module and pass them in as imports to another using the WebAssembly JavaScript API.

**Reference:** 
Chapter 7. Dyamic linking: The basics, from [WebAssembly in Action](https://www.manning.com/books/webassembly-in-action) by Gerard Gallant, published by Manning Books.

## Purpose

While the goal is to show how to build a WASM application that links to its WASM modules dynamically at run time, first we'll show how to statically link the WASM modules to the WASM application at time of build, for comparison purposes.

[Read this slightly outdated article for additional background.](https://yushulx.medium.com/webassembly-building-standalone-and-dynamic-linking-modules-in-windows-bd4492d0688f) Then look below for sequence of commands and updated arguments.

## Main Project Files

1. main.c - WASM application
2. foo1.c - WASM module
3. foo2.c - WASM module
4. pre.js - Contains the list of WASM modules that need to be preloaded (for dynamic linking to at run time) when the WASM application runs in a Web Browser

## Create a standalone WASM application containing WASM modules statically linked at build time:

### For running in a WASI Runtime (e.g., **wasmtime**)

```
$emcc main.c foo1.c foo2.c -o main.wasm
```

As this generates only a WASM file, we can run it in wasi-supporting runtimes, such as **wasmtime**:

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

## Create a WASM application and the WASM modules it needs to link to (independantly of each other):

### For running in a WASI Runtime (e.g., **wasmtime**)

**wasi-sdk** - The WASI-enabled WebAssembly C/C++ toolchain does not yet support dynamic libraries. See [notable-limitations](https://github.com/WebAssembly/wasi-sdk?tab=readme-ov-file#notable-limitations) for specific details.

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
In both cases, Web Browser output should be identical to that of the standalone WASM application (shown above), however for dynamic linking at run time to work, the modified main.js source code with the list of 'dynamicLibraries' to preload, must successfully execute!

![JavaScript Source Code image is supposed to appear here](images/js-src.png "Modified JavaScript source code containing list of 'dynamicLibraries' that must be preloaded")

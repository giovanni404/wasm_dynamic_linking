# wasm_dynamic_linking
WebAssembly Dynamic Linking using [**Emscripten**.](https://emscripten.org/index.html)

## Background

While the goal is to show you how to build a WASM application that links to its WASM modules dynamically at runtime, first we'll show how to do it using static linking, so that you can compare it to dynamic linking.

[Read this slightly dated article for some background.](https://yushulx.medium.com/webassembly-building-standalone-and-dynamic-linking-modules-in-windows-bd4492d0688f) Then follow on from here for updated methods.

## Main Project Files
1. main.c - To become the WASM MAIN_MODULE
2. foo1.c - To become a WASM SIDE_MODULE
3. foo2.c - To become a WASM SIDE_MODULE
4. pre.js - Contains list of WASM SIDE_MODULEs that need to be preloaded when running WASM MAIN_MODULE in a Web Browser

## Build a standalone WASM MAIN_MODULE (executable) containg statically linked WASM SIDE_MODULEs:

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
In this case the generated wasm file depends on an Emscripten JS runtime. The the HTML and WASM files need to be served by a local Web Server like **Chrome**:

```
$emrun main.html --browser "/mnt/c/Program Files (x86)/Google/Chrome/Application/"chrome.exe
```
![alt text](https://github.com/giovanni404/wasm_dynamic_linking/images/browser.png "Web Browser Output")

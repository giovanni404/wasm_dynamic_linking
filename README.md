# wasm_dynamic_linking
Examples for building WebAssembly Dynamic Linking with **Emscripten**.

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
hello world 3
```

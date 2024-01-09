# wasm_dynamic_linking
Examples for building WebAssembly Dynamic Linking with **Emscripten**.

## Project Files
1. main.c - WASM MAIN_MODULE
2. foo1.c - WASM SIDE_MODULE
3. foo2.c - WASM SIDE_MODULE

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
$emcc main.c foo1.c foo2.c -o main.wasm
```
The generated wasm file doesn’t depend on an Emscripten JS runtime. We can run it in wasi-supporting runtimes, such as **wasmtime**:

```
$wasmtime main.wasm 
hello world 3
```

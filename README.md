# wasm_dynamic_linking
WebAssembly Dynamic Linking Example using Emscripten

## Build a standalone wasm file:
<code>
$emcc main.c foo1.c foo2.c -o main.wasm
</code>
The generated wasm file doesn’t depend on an Emscripten JS runtime. We can run it in wasi-supporting runtimes, such as wasmtime:
<code>
$wasmtime main.wasm 
hello world 3
<code>

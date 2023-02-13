const wasmBuffer = require('fs').readFileSync('grains.wasm');
WebAssembly.instantiate(wasmBuffer).then(wasmModule => {
  const { square } = wasmModule.instance.exports;
  const ans = square(1);
  console.log('square1: ', ans);
});

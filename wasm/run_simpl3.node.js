const fs = require('fs');

const wasmBuffer = fs.readFileSync('simple3.wasm');
WebAssembly.instantiate(wasmBuffer).then(wasmModule => {
  // Exported function live under instance.exports
  const { add } = wasmModule.instance.exports;
  const sum = add(33, 28);
  console.log(sum);
});

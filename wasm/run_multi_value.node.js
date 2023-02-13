const wasmBuffer = require('fs').readFileSync('multi_value.wasm');
WebAssembly.instantiate(wasmBuffer).then(wasmModule => {
  const { add_two_numbers } = wasmModule.instance.exports;
  const ans = add_two_numbers();
  console.log(ans);
});

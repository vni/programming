const fs = require('fs');

const wasmBuffer = fs.readFileSync('getAnswerPlus1.wasm');
WebAssembly.instantiate(wasmBuffer).then(wasmModule => {
  const { getAnswerPlus1 } = wasmModule.instance.exports;
  const ans = getAnswerPlus1();
  console.log(ans);
});

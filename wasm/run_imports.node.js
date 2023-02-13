var importObject = {
  console: {
    log: function(arg) {
      console.log(arg);
    }
  }
};

//const fs = require('fs');
const wasm = require('fs').readFileSync('imports.wasm');

WebAssembly.instantiateStreaming(fetch('logger.wasm'), importObject)
  .then(obj => {
    obj.instance.exports.logIt();
  });

WebAssembly.instantiate(wasmBuffer).then(wasmModule => {
  // Exported function live under instance.exports
  const { add } = wasmModule.instance.exports;
  const sum = add(33, 28);
  console.log(sum);
});

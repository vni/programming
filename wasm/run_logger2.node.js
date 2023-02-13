/*
var memory = new WebAssembly.Memory({initial:1});

var importObject = { console: { log: consoleLogString }, js: { mem: memory } };

WebAssembly.instantiateStreaming(fetch('logger2.wasm'), importObject)
  .then(obj => {
    obj.instance.exports.writeHi();
  });
*/




var memory = new WebAssembly.Memory({ initial : 1 });

function consoleLogString(offset, length) {
  var bytes = new Uint8Array(memory.buffer, offset, length);
  var string = new TextDecoder('utf8').decode(bytes);
  console.log(string);
}

var importObject = {
  console: {
    log: consoleLogString
  },
  js: {
    mem: memory
  }
};

const logger2_wasm = require("fs").readFileSync("logger2.wasm");

WebAssembly.instantiate(logger2_wasm, importObject)
.then(obj => {
  obj.instance.exports.writeHello();
});

var importObj = {
  js: {
    memory: new WebAssembly.Memory({initial: 1}),
    table: new WebAssembly.Table({initial: 1, element: "anyfunc"}),
  }
};

const fs = require('fs');

Promise.all([
  WebAssembly.instantiate(fs.readFileSync('shared0.wasm'), importObj),
  WebAssembly.instantiate(fs.readFileSync('shared1.wasm'), importObj),
]).then(results => {
  console.log(results[1].instance.exports.doIt());
});

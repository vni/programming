var global = new WebAssembly.Global({value: "i32", mutable: true}, 444);

WebAssembly.instantiate(
  require("fs").readFileSync("globals.wasm"),
  { js: { global } }
).then(obj => {
  const { getGlobal, incGlobal, incGlobal2 } = obj.instance.exports;

  console.log("initial global: ", getGlobal());
  incGlobal();
  console.log("global after: ", getGlobal());
  incGlobal();
  console.log("global after: ", getGlobal());
  incGlobal();
  console.log("global after: ", getGlobal());

  incGlobal2();
  console.log("incGLobal2: ", getGlobal());

  incGlobal2();
  console.log("incGLobal2: ", getGlobal());
});

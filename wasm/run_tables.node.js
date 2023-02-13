/*
  function() {
  // table section
  var tbl = new WebAssembly.Table({initial:2, element:"anyfunc"});

  // function sections:
  var f1 = ... // some imported WebAssembly function
  var f2 = ... // some imported WebAssembly function

  // elem section
  tbl.set(0, f1);
  tbl.set(1, f2);
};
*/

WebAssembly.instantiate(require('fs').readFileSync('tables.wasm'))
  .then(obj => {
    console.log(obj.instance.exports.callByIndex(0)); // returns 42
    console.log(obj.instance.exports.callByIndex(1)); // returns 13
    //console.log(obj.instance.exports.callByIndex(2)); // returns an error, because there is no index position 2 in the table
  });

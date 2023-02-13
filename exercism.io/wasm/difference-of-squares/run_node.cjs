const wasmBuffer = require('fs').readFileSync('difference-of-squares.wasm');
WebAssembly.instantiate(wasmBuffer).then(wasmModule => {
  const { squareOfSum, sumOfSquares } = wasmModule.instance.exports;

  console.log('squareOfSum(1): ', squareOfSum(1));
  console.log('squareOfSum(5): ', squareOfSum(5));
  console.log('squareOfSum(10): ', squareOfSum(10));
  console.log('squareOfSum(100): ', squareOfSum(100));

  console.log('\n\n');

  console.log('sumOfSquares(1): ', sumOfSquares(1));
  console.log('sumOfSquares(5): ', sumOfSquares(5));
  console.log('sumOfSquares(10): ', sumOfSquares(10));
  console.log('sumOfSquares(100): ', sumOfSquares(100));
});

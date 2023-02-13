// not finished

let memory = new WebAssembly.Memory({initial:10, maximum:100, shared:true});

memory.buffer // returns SharedArrayBuffer

// in wat file:
// max memory size (in 64K quantity) is mandatory
(memory 1 2 shared)


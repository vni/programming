struct CustomVec {
    ptr: *mut u8,
    len: usize,
    cap: usize,
}

impl std::fmt::Display for CustomVec {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(
            f,
            "CustomVec {{ ptr: {:p}, len: {}, cap: {} }};",
            self.ptr, self.len, self.cap
        )
    }
}

fn main() {
    // let vec = vec![1u8, 2, 3, 4, 5, 6, 7, 8];
    // let transmuted /* CustomVec */ = unsafe { std::mem::transmute::<Vec<u8>, CustomVec>(vec) };
    // // transmuted = 55;

    // println!("{}", transmuted);

    // let ascii: &[u8] = unsafe { std::mem::transmute("Hello") };
    // println!("ascii: {:?}", ascii);
    // println!("ascii.len: {}", ascii.len());

    // let tf32: u32 = unsafe { std::mem::transmute(0.0_f32) };
    // println!("transmuted f32: 0x{:x}", tf32);

    // struct V3(*mut usize, usize, usize);

    // let vec = vec![1u8, 2, 3, 4, 5, 6, 7, 8];
    // let vec_ptr: V = unsafe { std::mem::transmute::<Vec<u8>, V>(vec) };
    // println!("");

    // println!("vec_ptr: {:p}", &unsafe { *vec_ptr.0 }); //unsafe { vec_ptr.0 as *mut usize })

    /*let mut vec = vec![1u8, 2, 3, 4, 5, 6, 7, 8];
    let first: *mut u8 = &mut vec[0] as *const u8 as *mut u8;
    // unsafe { std::mem::transmute(vec[0])}
    println!("first: {:p}", first);
    println!("&vec[0]: {:p}", &vec[0]);*/

    //#[repr(C)]
    struct V3{
        cap: usize,
        ptr: *mut usize,
        len: usize
    }

    let mut vec = vec![1, 2, 3, 4, 5];
    println!("&vec[0]: {:p}", &vec[0]);
    let ptr = vec.as_ptr();
    println!("ptr: {:?} {:p}", ptr, ptr);
    println!("*ptr    [0]: {}", unsafe { *ptr });
    println!("*ptr.add(1): {}", unsafe { *ptr.add(1) });
    println!("*ptr.add(2): {}", unsafe { *ptr.add(2) });
    println!("*ptr.add(3): {}", unsafe { *ptr.add(3) });
    println!("*ptr.add(4): {}", unsafe { *ptr.add(4) });
    println!("*ptr.add(5): {}", unsafe { *ptr.add(5) });
    println!("*ptr.add(6): {}", unsafe { *ptr.add(6) });

    use std::mem::transmute;

    vec.push(33);
    vec.push(34);
    vec.push(35);

    println!();
    unsafe {
        let v: V3 = transmute(vec);
        println!("v.0: {}", v.cap);
        println!("v.1: {:p}", v.ptr);
        println!("v.2: {}", v.len);
    }

    println!("\n\nvector slice");
    let vec = vec![1,2,3,4];
    println!("&vec[0]: {:p}", &vec[0]);
    let vslice = &vec[..];
    struct XSlice { ptr: *mut u32, len: usize }
    let vsp: XSlice = unsafe { transmute(vslice) };
    println!("vsp.ptr: {:p}", vsp.ptr);
    println!("vsp.len: {}", vsp.len);
    println!("*vsp.ptr.add(0): {}", unsafe { *vsp.ptr.add(0) });
    println!("*vsp.ptr.add(1): {}", unsafe { *vsp.ptr.add(1) });
    println!("*vsp.ptr.add(2): {}", unsafe { *vsp.ptr.add(2) });
    println!("*vsp.ptr.add(3): {}", unsafe { *vsp.ptr.add(3) });
}

use std::io::{Read, Result, Write};

pub struct ReadStats<'a, R: Read> {
    // _phantom_data: ::std::marker::PhantomData<R>,
    bytes_count: usize,
    reads_count: usize,
    reference: &'a R,
}

impl<'a, R: Read> ReadStats<'a, R> {
    // _wrapped is ignored because R is not bounded on Debug or Display and therefore
    // can't be passed through format!(). For actual implementation you will likely
    // wish to remove the leading underscore so the variable is not ignored.
    pub fn new(wrapped: R) -> ReadStats<'a, R> {
        ReadStats {
            bytes_count: 0_usize,
            reads_count: 0_usize,
            reference: &wrapped,
        }
    }

    pub fn get_ref(&self) -> &R {
        self.reference
    }

    pub fn bytes_through(&self) -> usize {
        self.bytes_count
    }

    pub fn reads(&self) -> usize {
        self.reads_count
    }
}

impl<'a, R: Read> Read for ReadStats<'a, R> {
    fn read(&mut self, buf: &mut [u8]) -> Result<usize> {
        let sz = self.reference.read(&mut buf)?;
        self.bytes_count += sz;
        self.reads_count += 1;
        Ok(sz)
    }
}

pub struct WriteStats<W>(::std::marker::PhantomData<W>);

impl<W: Write> WriteStats<W> {
    // _wrapped is ignored because W is not bounded on Debug or Display and therefore
    // can't be passed through format!(). For actual implementation you will likely
    // wish to remove the leading underscore so the variable is not ignored.
    pub fn new(_wrapped: W) -> WriteStats<W> {
        unimplemented!()
    }

    pub fn get_ref(&self) -> &W {
        unimplemented!()
    }

    pub fn bytes_through(&self) -> usize {
        unimplemented!()
    }

    pub fn writes(&self) -> usize {
        unimplemented!()
    }
}

impl<W: Write> Write for WriteStats<W> {
    fn write(&mut self, buf: &[u8]) -> Result<usize> {
        unimplemented!("Collect statistics about this call writing {:?}", buf)
    }

    fn flush(&mut self) -> Result<()> {
        unimplemented!()
    }
}

# Rna Transcription

Welcome to Rna Transcription on Exercism's WebAssembly Track.
If you need help running the tests or submitting your code, check out `HELP.md`.

## Instructions

Given a DNA strand, return its RNA complement (per RNA transcription).

Both DNA and RNA strands are a sequence of nucleotides.

The four nucleotides found in DNA are adenine (**A**), cytosine (**C**),
guanine (**G**) and thymine (**T**).

The four nucleotides found in RNA are adenine (**A**), cytosine (**C**),
guanine (**G**) and uracil (**U**).

Given a DNA strand, its transcribed RNA strand is formed by replacing
each nucleotide with its complement:

- `G` -> `C`
- `C` -> `G`
- `T` -> `A`
- `A` -> `U`

## Reserved Memory

Bytes 64-189 of the linear memory are reserved for the input string.

The input string can be modified in place if desired.

## Source

### Created by

- @bushidocodes

### Based on

Hyperphysics - http://hyperphysics.phy-astr.gsu.edu/hbase/Organic/transcription.html
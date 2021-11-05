# HW 1 2021-1

## Requirements

Having installed ```libpng``` library in C for reading images like matrixes.  
It can be installed with
```sudo apt install libpng-dev```

## Important files

*Warning: they are in spanish*

- [HW1 Instructions](./docs/Instructions.pdf)
- [My HW1 Report](./docs/Report.pdf)
- [HW1 Report Guideline](./docs/Report_guideline.pdf)

## Objectives

- Investigate about the 'Max Tree' & 'Component Tree'.
- Represent an image as a tree and apply filters on it.

## Compile and ejecution

The C programng can be complie using:
```make```

and ejecuted using:
```./filters <input.png> <output.png> <filter_type> <A G | D>```

## Examples

Filter nodes with area higher than 200 pixels and grayish higher than 50:
```./filters tests/hard/campus.png out.png area 200 50```

Filter nodes with delta lower than 0.5:
```./filters tests/hard/campus.png out.png delta 0.05```

## Run all

To generate every file use:
```python3 gen.py```

and to check them:
```python3 compare.py```

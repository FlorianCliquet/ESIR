# What You Need to Know in Bash

This README provides a brief overview of bash scripting concepts illustrated through a series of image processing scripts. These scripts demonstrate how to check file arguments, create functions, handle errors, and process images efficiently.

## Table of Contents
- [Function](#function)
- [Conditional Branch](#conditional-branch)
- [Loops](#loops)
- [String Operations](#string-operations)
- [Error Handling](#error-handling)
- [Image Processing Scripts](#image-processing-scripts)

## Function

### Declare a Function
```bash
name_of_function() {
    # Content
}
```

### Call a Function
```bash
name_of_function arg1 arg2 ...
```

### Function Arguments

- "$#": Number of arguments passed to the script.
- "$x": The xth argument passed to the script.
- "$@": Special variable that holds all arguments passed to the script.

## Conditional Branch

### Syntax

```bash
if [ condition ]; then
    # commands
fi
```

### Example
```bash
if [ "$#" -ne 1 ]; then
    echo "Need 1 argument"
    exit 1
fi
```

### Comparator

- -ne: Not equal to
- -eq: Equal to
- ! -f filepath: Check if it's not a file (use -d for directories).


## Loops

### For Loop Syntax

```bash
for variable in list; do
    # commands
done
```

## String Operations

You can perform string manipulations using various techniques in bash, such as:

-  ${variable#pattern}: Remove shortest match of pattern from the beginning.
-  ${variable##pattern}: Remove longest match of pattern from the beginning.
-  ${variable%pattern}: Remove shortest match of pattern from the end.
-  ${variable%%pattern}: Remove longest match of pattern from the end.

## Error Handling

Using functions to handle errors improves code readability and maintainability. Here's a common pattern:

```bash
error_exit() {
    echo "$1" >&2 # Redirect to stderr
    exit 1
}
```

### Example Usage
```bash
if [ ! -f "$image_file" ]; then
    error_exit "Error: File not found!"
fi
```

## Image Processing Scripts

## Image Processing Functions

### Find the Smallest Dimension
Use the **identify** command from ImageMagick to get the smallest dimension of the image (width or height) for cropping.
```bash
smallest_dim=$(identify -format "%[fx:min(w,h)]" "$image_file")
```

### Convert to Square Image

Crop the image to a square shape centered on the image using the smallest dimension found using **convert**.

```bash
convert -gravity center -crop "${smallest_dim}x${smallest_dim}+0+0!" "$image_file" "$output_square"
```

### Convert to PDF

Use **img2pdf** to convert the cropped square image into a PDF format.

```bash
img2pdf --output "$output_pdf" --pagesize 10cmx10cm "$output_square"
```

### Merge Multiple PDFs into a Single One

Use **pdfunite** to combine multiple PDF files into a single PDF.

```bash
pdfunite "$temp_dir"/*.pdf "$album_pdf"
```

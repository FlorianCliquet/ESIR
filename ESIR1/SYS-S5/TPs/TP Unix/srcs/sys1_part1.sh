#!/bin/bash

# Check if the file argument is provided
# "$#" is the number of arguments passed to the script
# -ne is a comparison operator that checks if two values are not equal
# So basically, we check if "$#" is not equal to 1, which means the file argument is not provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <image_file>"
    exit 1
fi

# Store the image in a variable for better readability
image_file="$1"

#Check if the file exists
# -f checks for the file existence
# ! is a logical NOT operator
# because if we don't use the logical NOT operator it will exit when the file exists
if [ ! -f "$image_file" ]; then
    echo "Error: File not found!"
    exit 1
fi

# Get the smallest dimension of the image
# identify is used with -format option in order to get the smallest dimension
# %[fx:min(w,h)] means that we take the minimum value between the width and the height
smallest_dim=$(identify -format "%[fx:min(w,h)]" "$image_file")

# Create the output file names
# %.jpg removes the .jpg extension from the file name
# and we append _square.jpg and .pdf to the file name
output_square="${image_file%.jpg}_square.jpg"
output_pdf="${image_file%.jpg}.pdf"

# Crop the image to a square
# convert is used to crop the image
# -gravity center is used to crop from the center of the image
# -crop "${smallest_dim}x${smallest_dim}+0+0!" is used to crop the image to a square shape
# "{smallest_dim}x{smallest_dim}" is the size of the square
# +0+0! is the offset from the top left corner
convert -gravity center -crop "${smallest_dim}x${smallest_dim}+0+0!" "$image_file" "$output_square"

# Convert the cropped image to a PDF
# img2pdf is a pip package to convert to PDF image
# --output is straightforward
# --pagesize 10cmx10cm is also straightforward
img2pdf --output "$output_pdf" --pagesize 10cmx10cm "$output_square"

# Print the output file name
echo "PDF output $output_pdf"

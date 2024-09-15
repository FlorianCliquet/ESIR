#!/bin/bash

# We don't give too much explanation of the code here, as it is already explained
# in the previous parts.
# The main difference is the usage of function to handle multiple files.


# Function to process a single image it will enhance the readability of the code and will be better to process mutliples files at once
process_image() {
    # Store the imagePATH in a variable for better readability
    local image_file="$1"
    
    # Check if file exists
    if [ ! -f "$image_file" ]; then
        echo "Error: File $image_file not found!" >&2
        return
    fi

    # Create output filenames
    local output_square="${image_file%.jpg}_square.jpg"
    local output_pdf="${image_file%.jpg}.pdf"

    # Check if the output files already exist
    if [ -f "$output_square" ]; then
        echo "Error: Intermediate file $output_square already exists." >&2
        return
    fi
    if [ -f "$output_pdf" ]; then
        echo "Error: Output PDF $output_pdf already exists." >&2
        return
    fi

    # Get the smallest dimension of the image
    local smallest_dim=$(identify -format "%[fx:min(w,h)]" "$image_file")

    # Crop the image
    convert -gravity center -crop "${smallest_dim}x${smallest_dim}+0+0!" "$image_file" "$output_square"

    # Convert to PDF
    img2pdf --output "$output_pdf" --pagesize 10cmx10cm "$output_square"

    echo "Processed: $output_pdf"
}

# Loop through all arguments (image files)
# "$#" is the number of arguments passed to the script
# -eq is a comparison operator that checks if two values are equal
# So basically, we check if "$#" is equal to 0, which means no arguments were passed
if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <image_file1> <image_file2> ..."
    exit 1
fi

# For loop to process each image file
# the "$@" is a special variable that holds all arguments passed to the script
for image_file in "$@"; do
    process_image "$image_file"
done

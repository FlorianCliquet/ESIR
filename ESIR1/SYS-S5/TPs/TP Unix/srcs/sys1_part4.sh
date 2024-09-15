#!/bin/bash

# We don't give too much explanation of the code here, as it is already explained
# in the previous parts.
# The main difference is the usage of function mkdir and rm to create a temp folder
# and clean it up after the script is done.


# Function to process a single image
process_image() {
    local image_file="$1"
    local temp_dir="$2"
    
    if [ ! -f "$image_file" ]; then
        echo "Error: File $image_file not found!" >&2
        return
    fi

    # "##*/" removes the longest match of */ from the beginning
    # In this case, it removes the directory part of the path
    # It is used to get the filename from the full path
    local output_square="${temp_dir}/${image_file##*/}"
    output_square="${output_square%.jpg}_square.jpg"
    local output_pdf="${temp_dir}/${image_file##*/}"
    output_pdf="${output_pdf%.jpg}.pdf"

    # || is a logical OR operator so that if one of the file isn't valid we return an error
    if [ -f "$output_square" ] || [ -f "$output_pdf" ]; then
        echo "Error: Intermediate or output files already exist." >&2
        return
    fi

    local smallest_dim
    smallest_dim=$(identify -format "%[fx:min(w,h)]" "$image_file")
    
    convert -gravity center -crop "${smallest_dim}x${smallest_dim}+0+0!" "$image_file" "$output_square"

    img2pdf --output "$output_pdf" --pagesize 10cmx10cm "$output_square"

    echo "Processed: $output_pdf"
}

# Create a temporary working directory
temp_dir="./work_album"
if [ -d "$temp_dir" ]; then
    echo "Error: Temporary directory $temp_dir already exists!"
    exit 1
fi

mkdir "$temp_dir" || { echo "Error creating directory $temp_dir"; exit 1; }

# Process each image file
if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <image_file1> <image_file2> ..."
    rm -r "$temp_dir"
    exit 1
fi

for image_file in "$@"; do
    process_image "$image_file" "$temp_dir"
done

# Create album.pdf by combining all PDFs
album_pdf="assets/album.pdf"
if [ -f "$album_pdf" ]; then
    echo "Error: Album file already exists!" >&2
    rm -r "$temp_dir"
    exit 1
fi

# pdfunite is used to combine multiple PDF files into one
# "$temp_dir"/*.pdf is a wildcard that matches all PDF files in the temp directory
# The output is saved to album.pdf
# Pretty straightforward
pdfunite "$temp_dir"/*.pdf "$album_pdf" || { echo "Error creating album PDF"; rm -r "$temp_dir"; exit 1; }

echo "Album created: $album_pdf"

# Clean up
rm -r "$temp_dir"
echo "Temporary directory cleaned up."

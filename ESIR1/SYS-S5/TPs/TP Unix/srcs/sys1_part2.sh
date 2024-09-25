#!/bin/bash

# We don't give too much explanation of the code here, as it is already explained
# in the previous parts.
# The main difference is the usage of function.


# Function to print error messages and exit , made for better readability
error_exit() {
    echo "$1" >&2 # Redirect to stderr , aka standard error output
    exit 1 # Exit status method 1 means failure
}

main() {
	# Store the image in a variable for better readability
	image_file="$1"

	# Check if file exists
	if [ ! -f "$image_file" ]; then
	    error_exit "Error: File not found!"
	fi

	# Create output filenames
	output_square="${image_file%.jpg}_square.jpg"
	output_pdf="${image_file%.jpg}.pdf"

	# Check if the output files already exist to avoid overwriting and weird interactions
	[ -f "$output_square" ] && error_exit "Error: Intermediate file $output_square already exists."
	[ -f "$output_pdf" ] && error_exit "Error: Output PDF $output_pdf already exists."

	# Get the smallest dimension of the image
	smallest_dim=$(identify -format "%[fx:min(w,h)]" "$image_file")

	# Crop the image
	convert -gravity center -crop "${smallest_dim}x${smallest_dim}+0+0!" "$image_file" "$output_square"

	# Convert to PDF
	img2pdf --output "$output_pdf" --pagesize 10cmx10cm "$output_square"

	# Write the name of the PDF file to stdout
	echo "Processing completed: PDF saved as $output_pdf"
}

# Check if exactly one argument is provided
if [ "$#" -ne 1 ]; then
        error_exit "Usage: $0 <image_file>"
fi

main "$1"

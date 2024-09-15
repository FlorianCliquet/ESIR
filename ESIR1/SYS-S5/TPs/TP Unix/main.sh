#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                                              #
#    Rendu TP Bash                                                             #
#                                                                              #
#    By: Florian Cliquet et Pierre Bertholom                                   #
#                                                                              #
#    Created: 2024/09/13 15:02:42 by Florian                                   #
#    Updated: 2024/09/13 18:23:04 by Florian                                   #
#                                                                              #
# **************************************************************************** #



# Progress bar function
progress_bar() {

    # Fancy progress bar
    # The function takes a single argument, which is the progress percentage 
    # and displays a progress bar in the terminal
    # It is made up of "#" characters that represent the progress
    # it use the printf function to format the output
    # \r is used to return the cursor to the beginning of the line
    # The progress bar is updated by changing the number of "#" characters based on the progress percentage

    local progress=$1
    local bar_width=30  # Width of the progress bar

    # Calculate the number of filled and empty segments
    local filled_length=$((bar_width * progress / 100))
    local empty_length=$((bar_width - filled_length))

    # Create the progress bar string
    # we use tr to replace the spaces with "#" characters
    # printf "%-30s" "#" creates a string of 30 characters filled with "#"
    local bar=$(printf "%-${filled_length}s" "#" | tr ' ' '#')
    local empty=$(printf "%-${empty_length}s")

    # Display the progress bar
    # "\r[%s%s] %d%%" is the format string
    # %s is a placeholder for a string like %d is a placeholder for a number
    printf "\r[%s%s] %d%%" "$bar" "$empty" "$progress"
}
# Check if the required dependencies are installed
function check_dependencies(){

    # the "if ! command -v <command> $> /dev/null"
    # checks if the command is not found and then installs it
    # we redirect the output to /dev/null to avoid printing the output to the terminal

    # Track progress in steps
    local step=0
    local total_steps=4  # Define the total number of steps

    update_progress() {
        step=$((step + 1))
        local progress=$((step * 100 / total_steps))
        progress_bar $progress
    }
    echo "Checking dependencies..."
    # Check if fzf is installed
    if ! command -v fzf &> /dev/null
    then
        sudo apt install fzf -y &> /dev/null
        echo "fzf installed" 
    fi
    update_progress

    # Check if imagemagick is installed
    if ! command -v identify &> /dev/null
    then
        sudo apt-get install imagemagick -y &> /dev/null
        echo "imagemagick installed"
    fi
    update_progress

    # Check if img2pdf is installed
    if ! command -v img2pdf &> /dev/null
    then
        pip install img2pdf -y &> /dev/null
        echo "img2pdf installed"
    fi
    update_progress

    # Check if pdfunite is installed
    if ! command -v pdfunite &> /dev/null
    then
        sudo apt-get install poppler-utils -y &> /dev/null
        echo "poppler-utils installed"
    fi
    update_progress
    echo -e "\nDependencies are installed."
}

function main() {
    # Clear the terminal screen
    clear
    # Check the dependencies because the script requires them to run
    # for example if we don't have fzf install, if we go further in this code it'll crash
    check_dependencies
    local image_file=$(get_random_image)
    # / ! \ It'll crash here without fzf / ! \
    part=$(echo -e "5. All Parts\n4. Part4\n3. Part3\n2. Part2\n1. Part1" | fzf --ansi --prompt="Select a part to run: " --height=7)
    # it's a simple switch case to run the selected part
    # like we can find in many programming languages like C the best language ever
    case $part in
        "1. Part1")
            run_part1
            ;;
        "2. Part2")
            run_part2
            ;;
        "3. Part3")
            run_part3
            ;;
        "4. Part4")
            run_part4
            ;;
        "5. All Parts")
            run_all_parts
            ;;
        *)
            echo "Invalid option"
            ;;
    esac
}

# Chose a random image file from the assets directory
function get_random_image() {
    # find command is used to search for files in a directory hierarchy
    # assets is the directory where the image files are stored
    # -type f is used to search for files only
    # -name "*.jpg" is used to search for files with the .jpg extension
    local image_files=($(find assets -type f -name "*.jpg"))
    # $RANDOM is a bash variable that generates a random number
    # ${#image_files[@]} is used to get the length of the image_files array
    # @ is used to get all the elements of the array
    # % is the modulo operator, it returns the remainder of the division
    # So that in final we get a random index in the image_files array
    # thanks to the modulo operator even if RANDOM is greater than the length of the array
    # we'll get a valid index
    local image_file=${image_files[$RANDOM % ${#image_files[@]}]}
    echo "$image_file"
}

# First code snippet is meant to extract the smallest dimension of an image file and then crop the image to a square shape.
# and then convert the cropped image to a pdf file.
function run_part1(){
    local image_file=$(get_random_image)

    # if the script isn't executable, make it executable
    # -x is used to check if the file is executable
    if [ ! -x ./srcs/sys1_part1.sh ]; then
        # chmod is used to change the permissions of a file
        # +x is used to add the executable permission
        # it's equivalent to chmod 755 , 755 is a reference to the binary representation of the permissions
        # 7 is the binary representation of 111 which means read, write and execute permissions
        # 5 is the binary representation of 101 which means read and execute permissions
        # so 755 means read, write and execute permissions for the owner and read and execute permissions for the group and others
        chmod +x ./srcs/sys1_part1.sh
    fi
    ./srcs/sys1_part1.sh "$image_file"
}

# Second code snippet is meant to extract the dominant color of an image file using the color-thief-python library.
function run_part2(){
    local image_file=$(get_random_image)

    # if the script isn't executable, make it executable
    if [ ! -x ./srcs/sys1_part2.sh ]; then
        chmod +x ./srcs/sys1_part2.sh
    fi
    ./srcs/sys1_part2.sh "$image_file"
}

# Third code snippet is meant to extract the text from an image file using the pytesseract library.
function run_part3(){
    local image_file=$(get_random_image)
    local image_file1=$(get_random_image)
    local image_file2=$(get_random_image)
    local image_file3=$(get_random_image)

    # if the script isn't executable, make it executable
    if [ ! -x ./srcs/sys1_part3.sh ]; then
        chmod +x ./srcs/sys1_part3.sh
    fi
    ./srcs/sys1_part3.sh "$image_file" "$image_file1" "$image_file2" "$image_file3"
}

# Fourth code snippet is meant to extract the text from an image file using the pytesseract library.
function run_part4(){
    local image_file=$(get_random_image)
    local image_file1=$(get_random_image)
    local image_file2=$(get_random_image)
    local image_file3=$(get_random_image)
    local image_file4=$(get_random_image)
    local image_file5=$(get_random_image)

    # if the script isn't executable, make it executable
    if [ ! -x ./srcs/sys1_part4.sh ]; then
        chmod +x ./srcs/sys1_part4.sh
    fi
    ./srcs/sys1_part4.sh "$image_file" "$image_file1" "$image_file2" "$image_file3" "$image_file4" "$image_file5"
}

function run_all_parts() {
    # Check if every script is executable and make them executable if not
    for script in ./srcs/sys1_part{1..4}.sh; do
        if [ ! -x "$script" ]; then
            echo "Making $script executable..."
            chmod +x "$script"
        fi
    done

    # Get a random image file
    local image_file=$(get_random_image)
    local image_file1=$(get_random_image)
    local image_file2=$(get_random_image)
    local image_file3=$(get_random_image)
    local image_file4=$(get_random_image)
    local image_file5=$(get_random_image)
    local image_file6=$(get_random_image)
    local image_file7=$(get_random_image)
    local image_file8=$(get_random_image)
    local image_file9=$(get_random_image)
    local image_file10=$(get_random_image)

    echo "Starting the execution of all parts..."
    echo "---------------------------------------------"

    delay() {
        sleep 2  # Adjust the delay as needed, this is made just so that the progress bar is useful
        # Because if the script is too fast the progress bar will be useless
        # and she is so beautiful, and pretty cool
    }

    # Track progress in steps
    local step=0
    local total_steps=4  # Define the total number of steps

    update_progress() {
        step=$((step + 1))
        local progress=$((step * 100 / total_steps))
        progress_bar $progress
    }
    echo "Executing Part 1 with image file: $image_file."
    echo "Executing Part 2 with image file: $image_file1."
    echo "Executing Part 3 with image files: $image_file2, $image_file3, $image_file4, $image_file5, $image_file6..."
    echo "Executing Part 4 with image files: $image_file7, $image_file8, $image_file9, $image_file10..."

    # Run Part 1 and redirect output to /dev/null to avoid printing the output and keep the progress bar clean
    run_part1 "$image_file" &> /dev/null
    update_progress
    delay

    # Run Part 2 and redirect output to /dev/null to avoid printing the output and keep the progress bar clean
    run_part2 "$image_file1" &> /dev/null
    update_progress
    delay

    # Run Part 3 and redirect output to /dev/null to avoid printing the output and keep the progress bar clean
    run_part3 "$image_file2" "$image_file3" "$image_file4" "$image_file5" "$image_file6" &> /dev/null
    update_progress
    delay

    # Run Part 4 and redirect output to /dev/null to avoid printing the output and keep the progress bar clean
    run_part4 "$image_file7" &> /dev/null
    update_progress
    delay

    echo -e "\nAll parts have been executed successfully."
    echo -e "Detailed Output Locations:"
    echo -e "1. Part 1: Output image in assets directory named ${image_file%.jpg}_square.jpg, PDF file: ${image_file%.jpg}.pdf"
    echo -e "2. Part 2: Output image in assets directory named ${image_file1%.jpg}_square.jpg, PDF file: ${image_file1%.jpg}.pdf"
    echo -e "3. Part 3: Processed images in assets directory named ${image_file2%.jpg}_square.jpg, ${image_file3%.jpg}_square.jpg, ${image_file4%.jpg}_square.jpg, ${image_file5%.jpg}_square.jpg, ${image_file6%.jpg}_square.jpg, with associated PDF files ${image_file2%.jpg}.pdf, ${image_file3%.jpg}.pdf, ${image_file4%.jpg}.pdf, ${image_file5%.jpg}.pdf, ${image_file6%.jpg}.pdf"
    echo -e "4. Part 4: Final output PDF is album.pdf in the assets directory."
}

#entry point of the script
main
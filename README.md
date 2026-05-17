# Contact Book System

## What it does
This is a command-line application I built in C to manage and organize contacts permanently. It lets you add, search, update, delete, and view contact details like names, phone numbers, and emails. 

Instead of just using basic text files, this system saves contacts into a binary format using file handling, so your list stays completely secure and intact even after closing the program.

## Why I built this
I built this project to take my file handling skills in C to the next level. Working on this project helped me master:
1. **Binary File Handling:** Moving away from standard text-based file operations (`fprintf`/`fscanf`) and working with raw blocks of memory using `fwrite` and `fread`.
2. **Data Manipulation:** Learning how to modify or delete a specific record inside a file by using positioning functions like `fseek` and `ftell`.
3. **Advanced String Matching:** Implementing substring searching using `strstr` so users can search for a contact even if they only remember a part of the name or phone number.

## Features
- **Full CRUD Support:** Add new contacts, read them in a clean table format, update details, or delete old ones.
- **Contact Categorization:** Group your contacts cleanly into specific labels: *Friend, Family, Work, or Other*.
- **Smart Searching:** Search through your entire address book instantly by matching names or numbers.
- **Persistent Binary Storage:** Saves all records into a local file using optimized binary chunks to save space and read data faster.

## Concepts Used
- **Custom Structures (`struct`):** Tying names, emails, phone numbers, and categories together under a single contact profile template.
- **Binary I/O Operations:** Utilizing `fread`, `fwrite`, `fseek`, and `ftell` to navigate and modify file data on the hard drive.
- **String Parsing:** Using standard C string functions like `strstr` for searching, `strcmp` for exact matching, and `strcspn` to clean up newline inputs.

## How to run it
1. Open your terminal or command prompt inside this project folder.
2. Compile the source file using a standard C compiler:
   gcc contact_book.c -o contact_book

3. Run the compiled executable:
   ./contact_book

4. Interact with the menu options to manage your contacts!

## Tech Used
- **Language:** C
- **Compiler:** GCC
- **Core Focus:** Advanced File I/O, Struct Handling, and String Algorithms

## Author
Shafin Alam
GitHub: [shafinalam07](https://github.com/shafinalam07)

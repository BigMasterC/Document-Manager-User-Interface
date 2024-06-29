Certainly! Here are the GitHub README files for Project 3 and Project 4:

---

### Project 3: Text-Based User Interface for Document Management System

#### Overview
This project involves developing a text-based user interface for a document management system. The interface allows users to load and save documents, parse command-line inputs, and handle errors for invalid commands.

#### Objectives
- Practice text parsing and file I/O in C.
- Enhance functionality from the previous project.
- Implement robust error handling and validation.

#### Features
- **Load and Save Documents:** Load documents from files and save them back to files.
- **Command Parsing:** Support for various commands such as adding paragraphs, lines, and printing documents.
- **Error Handling:** Robust handling of invalid commands and error messages.

#### Technologies Used
- **C Programming Language**
- **Makefile**

#### How to Run
1. **Clone the repository:**
   ```sh
   git clone <repository-url>
   cd project3
   ```
2. **Compile the program:**
   ```sh
   make
   ```
3. **Run the program:**
   ```sh
   ./user_interface [filename]
   ```

#### Commands
- `add_paragraph_after <PARAGRAPH_NUMBER>`
- `add_line_after <PARAGRAPH_NUMBER> <LINE_NUMBER> *<LINE>`
- `print_document`
- `quit`
- `exit`
- `append_line <PARAGRAPH_NUMBER> *<LINE>`
- `remove_line <PARAGRAPH_NUMBER> <LINE_NUMBER>`
- `load_file <FILENAME>`
- `replace_text "<TARGET>" "<REPLACEMENT>"`
- `highlight_text "<TARGET>"`
- `remove_text "<TARGET>"`
- `save_document <FILENAME>`
- `reset_document`

#### Example Usage
```sh
# Start the interface
./user_interface

# Commands to add a paragraph and a line, then print the document
> add_paragraph_after 0
> add_line_after 1 0 *This is the first line.
> print_document
> quit
```

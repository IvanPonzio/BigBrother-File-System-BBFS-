# BigBrother File System

The BigBrother File System is a modified user-space FAT file system that adds new functionalities on top of the original implementation. This repository contains the source code for the BigBrother File System, which is based on the FAT file system implementation available in [this repository](https://github.com/ebiggers/fat-fuse).

## Description

The BigBrother File System enhances the standard FAT file system by incorporating additional features and capabilities. It introduces the following key functionalities:

1. **Surveillance**: The file system creates a secret log file, `/fs.log`, to record all file read and write operations performed by the user. The log file is invisible to commands like `ls`, but it can be accessed using commands like `cat` or through file redirection.

2. **Hidden Log File**: The log file is hidden from other tools that mount devices in FAT format by utilizing an orphan directory. This ensures that the log file remains inaccessible to the native operating system or other file system utilities. The orphan directory is marked in a special way, making it recognizable during system loading.

3. **File and Directory Deletion**: The file system allows the deletion of files and directories. When a file or directory is deleted, the corresponding clusters are marked as free, and the directory entry is updated accordingly. The in-memory directory tree is also updated to reflect the changes.

The BigBrother File System provides an enhanced user experience by introducing these additional functionalities while maintaining compatibility with the FAT file system format.

## Usage

To use the BigBrother File System, follow these steps:

1. Clone this repository to your local machine.
2. Build and compile the file system source code.
3. Mount the file system on a desired directory using the appropriate commands for your operating system.
4. Perform file operations such as read, write, delete, and create directories as needed. All file read and write operations are logged in the secret log file `/fs.log`.
5. When finished, unmount the file system using the appropriate commands.

Please refer to the documentation and comments within the source code for detailed instructions on building, mounting, and using the BigBrother File System.

## Contributing

Contributions to the BigBrother File System are welcome! If you have any ideas, bug fixes, or enhancements, please submit a pull request. Be sure to follow the existing code style and guidelines.

## License

The BigBrother File System is released under the [MIT License](link-to-license-file). Feel free to use, modify, and distribute the code in accordance with the terms of the license.

For more details, please refer to the [License](link-to-license-file) file.

## Acknowledgments

We would like to thank the contributors to the original FAT file system implementation for providing a solid foundation for this project. Their efforts and dedication are greatly appreciated.

## Contact

For any questions, suggestions, or inquiries, please contact the project maintainer at [email protected]


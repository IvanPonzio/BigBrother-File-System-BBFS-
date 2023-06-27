
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

---

#### Compilation and Running

To compile and run the BigBrother File System, please follow these steps:

1. Install the required dependencies, including `libfuse-dev`, `glib`, and `check`.
   ```shell
   $ sudo apt-get install libfuse-dev
   ```

2. Clone this repository to your local machine.
   ```shell
   $ git clone [(https://github.com/IvanPonzio/BigBrother-File-System-BBFS-)]

   $ cd bigbrother-file-system
   ```
   or 

   ```shell
   cd fat-fuse
    ```

3. Build and compile the file system source code.
   ```shell
   $ make
   ```

4. Create a directory

 to mount the file system.
   ```shell
   $ mkdir mnt
   ```

5. Mount the file system on the desired directory.
   ```shell
   $ ./bigbrother-fs [path-to-fsfat.img] ./mnt
    ```
    or

    ```shell
   $ ./fat-fuse path/to/fsfat.img ./mnt
   ```

If the program fails unexpectedly, the file system may not be unmounted correctly. In that case, it is necessary to manually unmount it using the native commands of the operating system.



## Creating and Mounting a Test Image


1. To create an empty FAT32-formatted image, first create a file file.img with 35MB of "zeros" inside (for FAT32, the minimum file size is around 33MB):

```shell
$ dd if=/dev/zero of=file.img count=35 bs=1M
```

Then, format the image with the correct format:

```shell
$ mkfs.vfat -F 32 -v ./file.img
```

2. Next, to mount the image and be able to add things, you need to use the system's mount function and give write permissions to all users at the mount point (which requires sudo permissions). First, create the directory where you will see the mounted files. Then, mount the image:

```shell
$ mkdir mnt
```

3. The following command mounts our file.img image to the mnt directory and grants all permissions.
   
```shell
$ sudo mount -t vfat file.img mnt/ -o umask=000
```
Add something to the image:

```shell
$ echo "Hello, this is a file" > mnt/test_file
```

Finally, you need to unmount the image:

```shell
$ sudo umount mnt/
```

If you remount the image, you will see the test_file again.

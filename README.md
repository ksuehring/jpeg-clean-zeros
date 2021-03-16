# jpeg-zero-clean

A simple command line tool for cleaning zero bytes added to JPEG files by a bug in macOS.

The tool allows to display the number of extra bytes and to remove them by lossless rewriting the JPEG image without any re-encoding.

## Background

A bug was found in the JPEG writing functionality of macOS in April 2020, which causes a rather larger number of zero-bytes being added to the end of JPEG picture files.  A common case, in which this problem occurs is transferring HEIF coded pictures from an iPhone to the Mac in compatibility mode. In that mode the captured pictures are converted to JPEG by macOS.  A fix for the JPEG writing function is expected soon, but it seems rather unlikely that this would modify existing JPEG files. 

When displaying images, the file reader usually ignore these zero bytes. But they can take up a huge portion of disk space, especially for larger image libraries.

This tools provides a simple way of fixing existing files without any modification of the actual image or meta data.

## Usage

General parameters are:

```bash
jpeg-zero-clean infile.jpg [outfile.jpg]
```

If only an input file is given, the tools displays the number of bytes preceding the JFIF file end tag. If no end tag is found, a warning is printed.

If an output file is given, the input file is re-written omitting the trailing zero bytes.

It is possible to specify the same file as input and output file, but not recommended.

**Please create a backup of all files before processing.**

## Compiling from source

The project is simple enough for a single source file. CMake config files are provided for convenience.

To compile using `make` on a Unix like OS (Linux, macOS) type:

```bash
cmake
make
```

The binary can be found in the `bin` directory. Optionally you can install with

```bash
make install
```

For generating Visual Studio or Xcode work spaces see the [CMake Documentation](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id11).

## Links

Some media coverage of the problem:

* [MacRumors intial report](https://www.macrumors.com/2020/04/28/macos-image-capture-bug-eats-storage/)
* [MacRumors further details](https://www.macrumors.com/2020/05/01/macos-jpg-truncation-bug-widespread/)
* [heise online initial report (German)](https://www.heise.de/mac-and-i/meldung/iPhone-Fotos-als-Speicherfresser-Fehler-in-Apples-Digitale-Bilder-App-4711304.html)
* [heise online further details (German)](https://www.heise.de/mac-and-i/meldung/Festplatte-voll-wegen-iPhone-Fotos-Bug-Auch-weitere-Apps-betroffen-4713318.html)



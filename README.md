# SoundCloud Downloader

[![Platform](https://img.shields.io/badge/Platform-Windows-blue.svg)](https://microsoft.com/windows)
[![C++Builder](https://img.shields.io/badge/Built%20with-C%2B%2BBuilder%2012-red.svg)](https://www.embarcadero.com/products/cbuilder)
[![yt-dlp](https://img.shields.io/badge/Powered%20by-yt--dlp-red)](https://github.com/yt-dlp/yt-dlp)
[![FFmpeg](https://img.shields.io/badge/Audio%20Engine-FFmpeg-green)](https://ffmpeg.org/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

A lightweight, native Windows desktop application for downloading tracks, sets, and playlists from SoundCloud. Built with **C++Builder 12**, it leverages the power of **yt-dlp** and **FFmpeg** to provide fast audio extraction, seamless MP3 conversion, and real-time download progress tracking.

---

## Features

- **High-Quality Downloads:** Fetch track metadata, artwork, and highest quality audio.
- **Automatic MP3 Conversion:** Integrated FFmpeg support converts streams to standard MP3 format cleanly.
- **Browser Authentication:** Pass cookies from installed web browsers (Chrome, Firefox, Edge, Brave, etc.) to access private tracks or bypass age/region restrictions.
- **Batch Downloading:** Process multiple URLs or full SoundCloud playlists at once.
- **Real-Time Progress Tracking:** Monitor download speed, ETA, and progress bar directly within the native Windows UI.
- **Lightweight & Fast:** Compiled with C++Builder 12 VCL for minimal memory usage and rapid startup times.

---

## Prerequisites

Before running or building the application, ensure you have the following binaries installed or placed in the program directory:

1. **yt-dlp**: Required for fetching stream URLs and metadata.
   - Download from [yt-dlp releases](https://github.com/yt-dlp/yt-dlp/releases).
2. **FFmpeg**: Required for audio extraction and MP3 re-encoding.
   - Download builds from [ffmpeg.org](https://ffmpeg.org/download.html) or via `winget install FFmpeg`.

> **Note:** The application will look for `yt-dlp.exe` and `ffmpeg.exe` in the application root directory or in your system's `PATH`.

---

## Installation & Usage

1. **Download the Latest Release:**
   Go to the [Releases](../../releases) tab and download the latest zip package.

2. **Extract Files:**
   Extract the zip contents to a folder on your Windows PC. Ensure `yt-dlp.exe` and `ffmpeg.exe` are present alongside the main executable.

3. **Run the App:**
   Launch `SoundCloudDownloader.exe`.

4. **Start Downloading:**
   - Paste a SoundCloud track or playlist URL into the input field.
   - Choose your preferred audio output folder.
   - *(Optional)* Select a browser to pass authentication cookies if needed.
   - Click **Download**!

---

## Building from Source

To compile the project yourself:

### Requirements
- **RAD Studio / C++Builder 12** (Community, Professional, or Enterprise Edition).
- C++ VCL (Visual Component Library) framework configured.

### Build Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/soundcloud-downloader.git
   cd soundcloud-downloader
   ```
2. Open `SoundCloudDownloader.cbproj` in **C++Builder 12**.
3. Select the **Release** build configuration and **Win64** (or **Win32**) target platform.
4. Click **Build** (`Shift + F9`) or **Run** (`F9`).

---

## Dependencies & Acknowledgments

This project relies on the following open-source projects:

- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — Command-line audio/video downloader.
- [FFmpeg](https://ffmpeg.org/) — Complete, cross-platform solution to record, convert, and stream audio/video.
- [Embarcadero C++Builder 12](https://www.embarcadero.com/products/cbuilder) — Rapid native C++ application development framework.

---

## License

This project is licensed under the **GNU General Public License v3.0** - see the [LICENSE](LICENSE) file for details.

---

## ⚠️ Disclaimer

This tool is created for educational and personal archival purposes only. Please respect the copyrights of artists and creators on SoundCloud when downloading media.

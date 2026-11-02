# SoundCloud Downloader

A lightweight, native Windows desktop application for downloading tracks, sets, and playlists from SoundCloud. Built with **C++Builder 12**, it leverages the power of **yt-dlp** and **FFmpeg** to provide fast audio extraction, seamless MP3 conversion, and real-time download progress tracking.

## Features

* **High-Quality Downloads:** Fetch track metadata, artwork, and highest quality audio.

* **Automatic MP3 Conversion:** Integrated FFmpeg support converts streams to standard MP3 format cleanly.

* **Browser Authentication:** Pass cookies from installed web browsers (Chrome, Firefox, Edge, Brave, etc.) to access private tracks or bypass age/region restrictions.

* **Batch Downloading:** Process multiple URLs or full SoundCloud playlists at once.

* **Real-Time Progress Tracking:** Monitor download speed, ETA, and progress bar directly within the native Windows UI.

* **Lightweight & Fast:** Compiled with C++Builder 12 VCL for minimal memory usage and rapid startup times.

## Prerequisites

Before running or building the application, ensure you have the following binaries installed or placed in the program directory:

1. **yt-dlp**: Required for fetching stream URLs and metadata.

   * Download from [yt-dlp releases](https://github.com/yt-dlp/yt-dlp/releases).

2. **FFmpeg**: Required for audio extraction and MP3 re-encoding.

   * Download builds from [ffmpeg.org](https://www.gyan.dev/ffmpeg/builds/?utm_source=chatgpt.com) or via `winget install FFmpeg`.

> **Note:** The application will look for `yt-dlp.exe` and `ffmpeg.exe` in the application root directory or in your system's `PATH`.

## Installation & Usage

1. **Download the Latest Release:**
   Go to the [Releases](../../releases) tab and download the latest zip package.

2. **Extract Files:**
   Extract the zip contents to a folder on your Windows PC. Ensure `yt-dlp.exe` and `ffmpeg.exe` are present alongside the main executable.

3. **Run the App:**
   Launch `SoundCloudDownloader.exe`.

4. **Start Downloading:**

   * Paste a SoundCloud track or playlist URL into the input field.

   * Choose your preferred audio output folder.

   * *(Optional)* Select a browser to pass authentication cookies if needed.

   * Click **Download**!

## Building from Source

To compile the project yourself:

### Requirements

* **RAD Studio / C++Builder 12** (Community, Professional, or Enterprise Edition).

* C++ VCL (Visual Component Library) framework configured.

### Build Steps

1. Clone the repository:

   ```
   git clone https://github.com/your-username/soundcloud-downloader.git
   cd soundcloud-downloader
   
   ```

2. Open `SoundCloudDownloader.cbproj` in **C++Builder 12**.

3. Select the **Release** build configuration and **Win64** (or **Win32**) target platform.

4. Click **Build** (`Shift + F9`) or **Run** (`F9`).

## Dependencies & Acknowledgments

This project relies on the following open-source projects:

* [yt-dlp](https://github.com/yt-dlp/yt-dlp) — Command-line audio/video downloader.

* [FFmpeg](https://www.gyan.dev/ffmpeg/builds/?utm_source=chatgpt.com) — Complete, cross-platform solution to record, convert, and stream audio/video.

* [Embarcadero C++Builder 12](https://www.embarcadero.com/products/cbuilder) — Rapid native C++ application development framework.

## Screenshots

<img width="479" height="320" alt="sc_down_main" src="https://github.com/user-attachments/assets/c9ea19da-b148-4756-b726-fcb97d0f8241" />
<img width="478" height="320" alt="sc_down_d" src="https://github.com/user-attachments/assets/ee984f42-15d4-4605-977d-03c9a98e44b1" />

## License

This project is licensed under the **GNU General Public License v3.0** - see the [LICENSE](LICENSE) file for details.

## ⚠️ Disclaimer

This tool is created for educational and personal archival purposes only. Please respect the copyrights of artists and creators on SoundCloud when downloading media.

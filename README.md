# README #

First of all this Repository is a copy from here: https://github.com/NLxAROSA/CREST/tree/CREST2

Thanks Lars for his hard work, but he is no longer developing the project and I hope a can update it to the current Shared Memory Version.

# Introducing CREST2 - also known as the CARS2 REST API #

This project provides a way for developers to have access to the data provided by Project CARS 2 Shared Memory in a more portable and accessible format than a mapped memory file.

It's a windows native command line application (written in C++ and a fair bit of plain old C) that will act as a local web/application server and serve the data via JSON over HTTP by accessing a URL.

Any web browser or HTTP client will be able to access the data both locally and inside the local network, which facilitates easy add-on development in any language (e.g. JavaScript, Java, C, C++, C#, etc. etc.) and platform (e.g. web browser, iOS, Android, Windows Phone or other) with a vast array of client REST libraries at your disposal.

* See https://www.projectcarsgame.com/ for more info on Project CARS.
* Latest binary download is always available at https://drive.google.com/drive/folders/1zx12hGJttkTa0aG1jIO9AZ28VM7cDj-J

# Building from source

1. Download the source code
2. Open it up in Visual Studio 2019

The project won't build without the proper setup of zlib. To properly enable zlib:
1. Download and extract the source code from http://www.zlib.net (Used http://zlib.net/zlib1211.zip)
2. Extract and open .\contrib\vstudio\vc14\zlibvc.sln with Visual Studio
3. Compile as Release and you will find 2 files in the folder .\contrib\vstudio\vc14\x86\ZlibDllRelease:
- zlibwapi.lib - copy this file to the CREST2 source into the folder CREST2\lib
- zlibwapi.dll - After compiling CREST2 this file must be parallel to your CREST2.exe

# Running CREST2

1. Download the executable from https://drive.google.com/drive/folders/1zx12hGJttkTa0aG1jIO9AZ28VM7cDj-J or build it yourself.
2. Start the application by double-clicking it.
3. Windows will complain about security (coming from an unknown/unverified source) both when downloading and starting the application. Please allow/unblock the application in order to allow it to start. Windows Firewall will also ask for permission to access the local network. Please allow it access for proper functioning.
4. If Windows complains about missing DLLs (e.g. MSVCR120.DLL or similar), please download and install the Visual C++ Redistributable Packages for Visual Studio 2019 from https://www.visualstudio.com/de/downloads/ (vcredist_x86.exe, scroll down to "Other Tools and Frameworks"), then start again.
5. Console will show a notification about the server being up and running and display port and URL information.

# Connecting to Project CARS 2

1. Start Project CARS 2.
2. Enable Shared Memory "Project CARS2" mode in the settings
3. Open up a browser (Chrome for best results) and go to http://localhost:8180/crest2/v1/api
4. Profit! F5/Refresh until you drop!


# Advanced usage

The basic URL (http://localhost:8180/crest2/v1/api) will expose the full set of data. If parameters are added to the request URL, the set will be limited to the parameters you specify.

The following parameters are available:

1. buildInfo
2. gameStates
3. participants
4. unfilteredInputs
5. vehicleInformation
6. eventInformation
7. timings
8. flags
9. pitInfo
10. carState
11. motionDeviceRelated
12. wheelsAndTyres
13. carDamage
14. weather

Example:  http://localhost:8180/crest2/v1/api?buildInfo=true will give you just the buildInfo.

Example2: http://localhost:8180/crest2/v1/api?timings=true&carState=true&weather=true will give you timings, carState and weather.

Example3: http://localhost:8180/crest2/v1/api will give you the full set.

NOTE: Sections are always in the order listed, never in the order of the request parameters.

# Compression

CREST can gzip the response body. Just add the following header to the HTTP request: "Accept-Encoding: gzip" and CREST will gzip the response and set the "Content-Encoding: gzip" HTTP response header. Regardless of the header, CREST will not compress output if the response is smaller than 128 bytes, to prevent overhead.

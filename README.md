# Make screenshot and share it!
###QScreenShotter [![Build Status](https://travis-ci.org/sb0y/QScreenShotter.svg?branch=master)](https://travis-ci.org/sb0y/QScreenShotter)

The program QScreenShotter will help you make comfortably any screenshot on your PC and share the link via IM or social networks.

You will need to choose from three ways to take a screenshot:

1. Full screen:

![Linux ScreenShot](http://cs622530.vk.me/v622530253/28df9/0f03mqfKa3I.jpg)

2. Window under mouse

![Taking window](http://cs622530.vk.me/v622530253/28e51/6xpPxV88Ei4.jpg) 

3. Region of the screen

![Taking a region](http://cs622530.vk.me/v622530253/28e64/RRTlbbyZ-gs.jpg)

The next step click on **Export** button. You will need only Access Token that you receive via online through a browser.

Here is preview of the screenshot on the web

![Export to WEB dialog](http://cs622530.vk.me/v622530253/28e07/INFcsOu_LrY.jpg)

![Screenshot in WEB](http://cs622530.vk.me/v622530253/28e6e/FKaFhmw9mkU.jpg)

Сompiles for Linux and Windows.

**How to install on Windows**

Download and run the [installer](https://github.com/sb0y/QScreenShotter/releases/download/0.5b/QScreenShotterInstall.exe).

**How to compile on Windows**

Read the [official manual](http://wiki.qt.io/How-to-build-a-static-Qt-for-Windows-MinGW).

**How to compile and run on Linux**

You will need Qt plugin for QPA. At Ubuntu you can install it using command:

`sudo apt-get install libqt5x11extras5-dev`

1. download the sources `git clone https://github.com/sb0y/QScreenShotter.git`
2. go to the downloaded directory and compile: `cd QScreenShotter && qmake && make`
3. run application `./qsc`

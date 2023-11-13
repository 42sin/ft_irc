<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/42sin/ft_irc">
    <img src="logo.png" alt="Logo" width="128" height="128">
  </a>

<h3 align="center">ft_irc</h3>

  <p align="center">
    Your own IRC Server in C++
    <br />
    <a href="https://github.com/42sin/ft_irc/issues">Report Bug</a>
    ·
    <a href="https://github.com/42sin/ft_irc/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#features">Features</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

#### [Go to Subject PDF]
[![Subject PDF][subjectImage]](en.irc_subject.pdf)

This is a simple IRC server based on the [`RFC 2812`] and following the C++ 98 standard. Even though this project mainly follows the RFC, it was not necessary by the Subject PDF, so some behaviours might differentiate from the original protocol. This is the first big project during our 42 Core Curriculum that we had to write in C++. The Server follows the [`reactor`] design pattern and therefore handles concurrent service requests from one or more inputs by dispatching them synchronously to the associated request handlers.
<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

The Project was mainly tested on macOS.

### Prerequisites

To connect to the server, you need to use an IRC Client that terminates packages with `\r\n`.<br>
I used [`WeeChat`]  as a reference client.
   ```sh
   brew install weechat
   weechat
   ```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/42sin/ft_irc.git && cd ft_irc
   ```
3. Compile the project
   ```sh
   make
   ```
4. Start the server
   ```sh
   ./ircserv <port> <password>
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Features -->
## Features

### Basics:

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
[issues-url]: https://github.com/42sin/ft_irc/issues
[license-url]: https://github.com/42sin/ft_irc/blob/master/LICENSE.txt
[subjectImage]: eval.png
[Go to Subject PDF]: en.ft_irc_subject.pdf
[`RFC 2812`]: https://www.rfc-editor.org/rfc/rfc2812
[`WeeChat`]: https://weechat.org/
[`reactor`]: https://en.wikipedia.org/wiki/Reactor_pattern

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
5. Connect to the server inside of weechat
   ```sh
   /server add <name> <IP-Address>/<port> -password=<password>
   /connect <name>
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Features -->
## Features

### Server:
<ul>
  <li><code>SHUTDOWN</code> Shuts down the server, behaves the same as DIE from the RFC 2812</li>
  <li><code>PING</code> Pings the server, this is done in intervals by WeeChat</li>
  <li><code>PASS</code> Sends the password to the server, WeeChat does this on your first time connecting</li>
</ul>

### User:
<ul>
  <li><code>USER</code> Sets a Username</li>
  <li><code>NICK</code> Sets a Nickname</li>
  <li><code>OPER</code> Sets a new Operator</li>
  <li><code>PRIVMSG</code> | <code>NOTICE</code> Sends a private message</li>
</ul>

### Channel:
<ul>
  <li><code>INVITE</code> Invite someone to a channel</li>
  <li><code>JOIN</code> Join or create a new channel</li>
  <li><code>MODE (t, i, o, k, l)</code> Changes the Channel Mode, see <a href="en.irc_subject.pdf">Subject PDF</a> for more informations</li>
  <li><code>KICK</code> Ejects a client from a channel</li>
  <li><code>TOPIC</code> View or change the channel topic</li>
  <li><code>PART</code> Leave a channel</li>
</ul>




<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See [`LICENSE`] for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
[issues-url]: https://github.com/42sin/ft_irc/issues
[`LICENSE`]: https://github.com/42sin/ft_irc/blob/master/LICENSE
[subjectImage]: eval.png
[Go to Subject PDF]: en.irc_subject.pdf
[`RFC 2812`]: https://www.rfc-editor.org/rfc/rfc2812
[`WeeChat`]: https://weechat.org/
[`reactor`]: https://en.wikipedia.org/wiki/Reactor_pattern

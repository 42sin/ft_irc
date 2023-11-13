# IRC
## Description
This is a simple IRC server inspired by the [`RFC 2812`] and following the C++ 98 standard.

It can be used with a real IRC client to participate in chat rooms, send private messages to one or multiple users and allows for the management of access modes and permissions. 

Although  [`WeeChat`] was used as a reference client during implementation, the server is functional with most clients that sends packets terminated with `\r\n`.

The Server follows the [`reactor`] design pattern and therefore handles concurrent service requests by one or more inputs by dispatching them synchronously to the associated request handlers.

## Installation
Clone the project and `make` the executable

	git clone https://github.com/42sin/ft_irc.git
	cd ft_irc
	make

Launch the server

	./ircserv < port > < password >

Launch  [Weechat]

	brew install weechat
	weechat
Connect to the IRC Server inside weechat

	/server add <name> <IP-address>/<port> -password=<password>
	/connect <name>

## Commands

The following commands are implemented in the server.

| Category        | Commands      
| --------------- | --------------------------------- |
| Server          | `SHUTDOWN`, `PING`, `QUIT`, `PASS` |
| User            | `USER`, `MODE` (i, o), `NICK`, `OPER` |
| Channel         | `INVITE`, `JOIN`, `MODE` (t, i, m, b), `KICK`, `PART`, `TOPIC` |
| Private message | `PRIVMSG`, `NOTICE` 

[`RFC 2812`]: https://www.rfc-editor.org/rfc/rfc2812
[`WeeChat`]: https://weechat.org/
[`reactor`]: https://en.wikipedia.org/wiki/Reactor_pattern
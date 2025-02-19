### 🚧 Project still under development 🚧
This project is still under development.
Do not despair, I promise I will give updates... Soon...

## About the project
Hyprsymbol is a tool created to quickly copy-paste emojis and other unicode symbols to your clipboard. This was highly inspired by the `CTRL + SHIFT + u` shortcut on [kitty](https://sw.kovidgoyal.net/kitty/) and [smile](https://github.com/mijorus/smile).

## Installation
+ Clone the repo
+ run `meson setup build` and `meson compile -c build`
The binary should be located under `build/hyprsymbol`

## Roadmap

#### Cairo graphics
+ [ ] Display unicode symbols and other stuff in the shared buffer
+ [ ] Render unicode symbols

#### Input handling
+ [ ] Mouse scroll input (to lower the emoji list)

#### Improvements
+ [ ] On-the-fly unicode symbols generation
+ [ ] Configuration file (on startup)
+ [ ] Styling file (CSS i guess)

## Contributing
As always, feel free to fork the repo and open a pull request if you have any suggestion. Please keep in mind that I'm absolutely not an expert.

1. Fork the repo
> [!NOTE]
> You can check that you are running a Wayland session with `echo $XDG_SESSION_TYPE`.

2. Run `./scan` to generate the headers and glue code for the protocols. (you should have installed `wayland-scanner` in order to do this)

3. Finally, run `make` to compile the project and generate the binary.

> [!TIP]
> You can enable the debug mode by setting then environment variable `WAYLAND_DEBUG` to `1`
> ```sh 
> $ WAYLAND_DEBUG=1 ./build/hyprsymbol
> ```
### 🚧 Project still under development 🚧
This project is still under development.
Do not despair, I promise I will give updates... Soon...

## About the project
Hyprsymbol is a tool created to quickly copy-paste emojis and other unicode symbols on your needs. This was highly inspired by the `CTRL + SHIFT + u` shortcut on[kitty](https://sw.kovidgoyal.net/kitty/).

## Installation
🚧 ... 🚧

## Roadmap
- [ ] EGL / Cairo graphic design
- [ ] Input handling
    - [ ] Keyboard input
    - [ ] Mouse input
- [ ] Config
- [ ] Styling (the most important)

## Contributing
As always, feel free to fork the repo and open a pull request if you have any suggestion. Please keep in mind that I'm absolutely not an expert and mainly do this as myself to understand how the Wayland ecosystem functions.

1. Fork the repo
> [!NOTE]
> You can check that you are running a Wayland session with `echo $XDG_SESSION_TYPE`.

2. Run `./scan` to generate the headers and glue code for the protocols. (you should have installed `wayland-scanner` in order to do this)

3. Finally, run `make` to compile the project and generate the binary. 
### 🚧 Project still under development 🚧
This project is still under high intensity development.
Do not despair, I promise I will continue to update it :3

- [ ] Check this box if you want to be notified for any update on this project[^1].

[^1]: Just kidding, you can't

---

### If you still want to try it out
First, run `git clone git@github.com:SushiCannibale/hyprsymbol.git` to clone the repo.
`cd` in it.

> [!NOTE]
> You can check that you are running a Wayland session with `echo $XDG_SESSION_TYPE`. 
> Doing this should output `wayland`.

Then, check that you have installed `wayland-scanner`.
(running `whereis wayland-scanner` should do the trick)

Step three, type `./scan` to generate the sources from the prototypes.

Finally, run `make` and execute `hyprsymbol` to be greeted by an empty,
lonely, pointless black box... Y-Y

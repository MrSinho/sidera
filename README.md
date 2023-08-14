# gaia-universe-model

_Check the linux and windows build logs:_

[![linux_badge](.shci/linux/exit_code.svg)](.shci/linux/log.md)
[![windows_badge](.shci/windows/exit_code.svg)](.shci/windows/log.md)

A static 3d representation of of the Gaia (Early) Data Release 3 Universe Model data uploaded by the European Space Agency.

![](docs/media/alphafe_age_mass.png)

---

## Build status

Programs and libraries are frequently being tested on Windows 11, and Linux Mint (wsl and physical machine) with different compilers (`MSVC`, `gcc`), and hardware configurations (`RX580 4GB GDDR5`, `Radeon V Carrizo 500MB`).

 ![](docs/media/age_cf.png)

---

## Documentation

 * [`Quick install`](/docs/quick-install.md)
 * [`Terminal install`](/docs/terminal-install.md)
 * [`Application tutorial`](/docs/application-tutorial.md)

_x: right ascension; y: declination; z: barycentric distance; view mode: polar; color filter: age; shade type: animated_

---

## Features

 * 3d plot customization using `.smd` files, see [`settings.smd`](./gaia-universe-model/smd/settings.smd).
 * After downloading Gaia Universe Model data, load as many celestial bodies as you need in the scene, see [`settings.smd`](./gaia-universe-model/smd/settings.smd).
 * Decide what parameters to read (`xyz` parameter types + color_filter). To find what parameters are compatible, see [`settings.smd`](./gaia-universe-model/smd/settings.smd).
 * Graphics settings options: view modes (cartesian, polar), shade types (pixel, circle, cloud, animated cloud), see [`settings.smd`](./gaia-universe-model/smd/settings.smd). 

 ![](docs/media/logg_cf.png)

---

## Feedback and contributing

I have been personally dedicated to this project since the beginning of 2022, investing a significant amount of my spare time. Should you encounter any issues with the application or wish to introduce new features while addressing existing ones, I welcome your contributions to the repository. You can contribute by either opening an issue or submitting a pull request.

---
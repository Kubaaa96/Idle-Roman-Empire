# Idle Roman Empire Idle Game

[![Actions Status](https://github.com/Kubaaa96/IdleRomanEmpire/workflows/IdleRomanEmpire_x64-linux/badge.svg)](https://github.com/Kubaaa96/IdleRomanEmpire/actions)
[![Actions Status](https://github.com/Kubaaa96/IdleRomanEmpire/workflows/IdleRomanEmpire_x64-windows/badge.svg)](https://github.com/Kubaaa96/IdleRomanEmpire/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub issues open](https://img.shields.io/github/issues/Kubaaa96/IdleRomanEmpire.svg?)](https://github.com/Kubaaa96/IdleRomanEmpire/issues)

- [About Project](#about-project)
- [Building](#building)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [Licence](#licence)
- [Contact](#contact)

## About Project
This will be an idle game based on the Roman Empire where you progress through the census rank starting from being a slave and progressing through many generations. Main objective is to earn money. On Slave phase you can't earn money but get experience in choosen industry related skills. More will be described in future wiki.

## Building

Building this project requires [SFML](https://github.com/SFML/SFML) to be installed. You can either build it from source or acquire it from a package manager like VCPKG.

Clone:
```
git clone https://github.com/Kubaaa96/IdleRomanEmpire.git
```

This project uses cmake, so you can build it simply by first configuring with the build system of choice
```
cmake . -Bbuild -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Release
```
and then compiling
```
cmake --build ./build --config Release --target install
```
Depending on the way you aquired SFML you may need to provide `-DSFML_DIR=<path>` with the path where SFMLConfig.cmake can be found (if cmake cannot locate this file on its own)

You can also refer to github workflows for examples with complete build pipelines.

## Roadmap
See the [open issues](https://github.com/Kubaaa96/IdleRomanEmpire/issues) for a list of proposed features (and known issues).

## Contributing

If you want to implement some features from Issue list or you have your own feel free to do this. You can just open new issue with your idea to discuss with others.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## Licence
Distributed under the MIT License. See `LICENSE` for more information.

## Contact

Jakub Dobrowolski  [![LinkedIn](https://img.shields.io/badge/linkedin-%230077B5.svg?&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/jakub-dobrowolski/)  [![Gmail](https://img.shields.io/badge/gmail-D14836?&logo=gmail&logoColor=white)](jd.kuba96@gmail.com) jd.kuba96@gmail.com

Project Link: https://github.com/Kubaaa96/IdleRomanEmpire
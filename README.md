# u3oko

Открытая в базовой части кроссплатформенная децентрализованная масштабируемая система видеонаблюдения.

### Поддерживаемые операционные системы:
- Windows (x86/ARM)
- Android (ARM)
- Linux (x86/ARM)
- Darwin (x86/ARM)

### Зависимости:
- All platforms
  - [perl](https://strawberryperl.com)
  - [git](https://git-scm.com)
  - wget
  - [python](https://www.python.org)
  - [nasm](https://www.nasm.us)
  - [clang](https://clang.llvm.org)
  - [ninja](https://ninja-build.org)

- Linux {orangepi, android, raspberrypi}:
  - meson
  - autoconf
  - automake
  - libtool
  - pkg-config

- Windows:
  - [msys2](https://www.msys2.org)
  - [cygwin](https://www.cygwin.com/install.html)

```
sudo apt update
sudo apt install build-essential
wget -qO- https://apt.llvm.org/llvm.sh | sudo bash -s -- 23
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-23 100 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-23
sudo apt install clang-format-23
sudo ln -sf /usr/bin/clang-format-23 /usr/bin/clang-format
sudo apt install autoconf automake libtool
sudo apt update && sudo apt-get install pkg-config
sudo apt install meson
sudo apt install ninja-build
sudo apt install -y nasm
sudo apt install libx11-dev
sudo apt install libdrm-dev
#sudo apt-get install pkg-config
sudo apt install libsystemd-dev

#sudo add-apt-repository ppa:pipewire-debian/pipewire-upstream
#sudo apt update
#sudo apt install pipewire-media-session-wireplumber
#sudo apt install libpipewire-0.3-{0,dev,modules}
#sudo apt install pipewire-audio-client-libraries
#sudo apt install libavutil-dev
#sudo apt install libavcodec-dev
#sudo apt install libavformat-dev
#sudo apt install libavfilter-dev
```


### Сборка:

Параметры конфигурации сборки в файле ```mmedia/build/cmake/vals/env-command-line-vals.cmake```
```
git clone https://github.com/uuusoft/u3oko.git
cd u3oko/mmedia/build/cmds
./u3oko-linux-rel-lib-none-clang-ninja.sh
./u3oko-linux-dbg-lib-none-clang-ninja.sh

./u3oko-linux-dbg-lib-address-clang-ninja.sh
./u3oko-linux-dbg-dll-address-clang-ninja.sh
./u3oko-linux-dbg-dll-ub-clang-ninja.sh
```

### [Предсобранные артефакты для ряда плафторм/конфигураций/архитектур/версий](https://github.com/uuusoft/u3oko-3rd-artifacts)

Пример использования
```
git clone https://github.com/uuusoft/u3oko-3rd-artifacts.git
cd u3oko-3rd-artofacts
python3 -m http.server 8011
```
Порт 8011 должен совпадать с переменной cmake ```U3_HOST_PORT``` из файла параметров конфигурации сборки. 
Имя хоста меняется через переменную cmake ```U3_HOST_NAME``` там же.

The installation description is for a Linux based system.
This wont work for a Windof based system. You can try to use WSL2.
Maybe you run into some trouble when it comes to flashing the software.
So for that, the derived repositories which contains the actuall software for the controll-units should have a release which can be directly loaded into the controller via the st-link. 

```
sudo apt install binutils-arm-none-eabi gcc-arm-none-eabi
sudo apt install gdb-multiarch
cd /usr/bin
sudo ln -s gdb-multiarch arm-none-eabi-gdb

# Download this arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz on
# https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

cd /opt
sudo tar Jxvf ~/arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi.tar.xz

export PATH=$PATH:/opt/arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi/bin

sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt update
sudo apt install python3.8

sudo apt install openocd

sudo cp /lib/udev/rules.d/60-openocd.rules /etc/udev/rules.d/
```
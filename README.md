# gtk 테스트 레포지토리
이 레포지토리는 gtk vscode 개발 환경을 구축하고 wayland 위에서 gtk+3.0을 돌리는 테스트 레포지토리 입니다.

.vscode 파일에는 gtk의 인클루드 패스(yocto 프로젝트의 sysroot 디렉토리에서 필요한 인클루드 파일들)가 있습니다.

---

# yocto sdk 설치하기

yocto 프로젝트를 빌드해야 합니다. 이 레포지토리는 라즈베리 파이를 기준으로 설명합니다.

빌드한 리눅스 배포판은 ubuntu 22.04-lts 입니다. (wsl)

먼저 필요한 패키지입니다.

**bash**
```bash
sudo apt-get update
sudo apt install gawk wget git diffstat unzip texinfo gcc build-essential\
 chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils\
 iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev pylint xterm\
 python3-subunit mesa-common-dev zstd liblz4-tool
```

그 다음 레이어를 다운로드 받습니다.

**bash**
```bash
git clone git://git.yoctoproject.org/meta-raspberrypi -b scarthgap
git clone git://git.openembedded.org/poky -b scarthgap
git clone git://git.openembedded.org/meta-openembedded -b scarthgap
```

poky/ 폴더로 이동한 다음 다음 명령을 수행합니다.

**bash**
```bash
source oe-init-build-env ./build-rpi
```
poky/build-rpi/conf 디렉토리로 이동후 local.conf를 수정합니다.

**poky/build-rpi/conf/local.conf**
```bitbake
#머신 라즈베리 파이4 - 64
MACHINE = "raspberrypi4-64"
#라즈베리 파이 uboot 사용
RPI_USE_U_BOOT = "1"
#uart 활성화
ENABLE_UART = "1"
```

이 줄을 추가합니다.

또한

**poky/build-rpi/conf/local.conf**
```bitbake
#gtk 3 이미지 설치
IMAGE_INSTALL:append = " gtk+3"
#wayland 및 pam 배포판 추가
DISTRO_FEATURES:append = " wayland pam"
#weston 빌드를 위해 killswitch 허용
LICENSE_FLAGS_ACCEPTED = "synaptics-killswitch"
#파일시스템 wic 뱉도록 추가
IMAGE_FSTYPES:append = " wic"
```

이 줄을 추가합니다.

**bash**
```bash
bitbake core-image-weston
```

sdk 또한 빌드합니다.

**bash**
```bash
bitbake core-image-weston -c do_populate_sdk
```

이러면 poky/bulild-rpi/tmp/deploy 밑에 2개의 이미지, sdk 폴더가 생성됩니다.

poky/build-rpi/tmp/deploy/sdk 디렉토리로 이동하고 아래 명령을 수행합니다.

**bash**
```bash
./poky-glibc-x86_64-core-image-weston-cortexa72-raspberrypi4-64-toolchain-5.0.10.sh
```

sdk가 설치될 디렉토리를 지정합니다. 기본 값도 괜찮습니다.

설치가 끝났다면 이제 이미지를 sd카드에 플래싱 해야 합니다.

---

# SD카드 플래싱하기

파일 시스템을 wic로 뱉게 만들었습니다. 

poky/build-rpi/tmp/deploy/images/raspberrypi4-64 이 디랙토리로 이동합니다.

**bash**
```bash
cp core-image-weston-raspberrypi4-64.rootfs.wic [윈도우 특정 디렉토리]
```

윈도우 특정 디렉터리에 복사합니다. 보통 "/mnt/c/" 가 윈도우 c 디렉토리 입니다.

blanaetcher를 다운로드 받아 sd카드에 플래싱합니다.

혹은 리눅스 환경인 경우 poky/build-rpi/tmp/deploy/images/raspberrypi4-64 경로에서 다음 명령을 수행합니다.
**bash**
```bash
sudo dd if=core-image-weston-raspberrypi4-64.rootfs.wic of=[sd카드 블록 디바이스 장치노드, 대부분 /dev/mmcblk0] bs=1M stutus=progress
```

이렇게 하면 플래싱도 완료되었습니다.

---

# 파일 옮기기

usb로 마운트 하거나 타겟 디바이스(라즈베리파이) bash에서 zmodem을 사용합니다.

**rpi-bash**
```bash
rz
```

zmodem 전송은 터미널 프로그램을 사용해야합니다.

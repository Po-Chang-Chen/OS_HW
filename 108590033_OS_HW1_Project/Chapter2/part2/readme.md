# Chap 2 Part 2 
### Team members
    - 資工三 108590033 陳柏錩
    - 資工三 108590034 許晉緯
    - 資工三 108590041 楊勝朋
    - 資工三 108590044 何柏憲

### Environment
    - Operating System: Ubuntu 18.04.1 LTS
    - Compiler Version: gcc 7.5.0

### Usage
1. Complie Program
    ```bash
    make
    ```

2. Load Module
    ```bash
    sudo insmod birthday.ko
    ```

3. Unload Module
    ```bash
    sudo rmmod birthday
    ```

4. Check if the specified module is loaded or not
    ```bash
    lsmod | grep birthday
    ```

5. ensure the list is properly constructed once the kernel module has been loaded
    ```bash
    dmesg
    ```

6. Clean file
    ```bash
    make clean
    ```

### Responsibility (100%)
    - 資工三 108590033 陳柏錩 (25%)
    - 資工三 108590034 許晉緯 (25%)
    - 資工三 108590041 楊勝朋 (25%)
    - 資工三 108590044 何柏憲 (25%)
    Everybody does coding, debuging ,and searching information via fully discussion.
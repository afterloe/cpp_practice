第三方C++库
===
> create by afterloe  
> version is 1.0.0   
> MIT License  

### Protobuf
#### 源码安装
```
wget https://codeload.github.com/protocolbuffers/protobuf/zip/refs/tags/v3.20.0
sudo mkdir /usr/local/src/protobuf
cd /usr/local/src/protobuf
mv ~/Download/protobuf-3.20.0.zip .
unzip protobuf-3.20.0.zip
cd protobuf-3.20.0

sudo ./autogen.sh
sudo ./configure
sudo make
sudo make install
sudo ldconfig
```

#### 测试使用
```
cd /usr/local/src/protobuf
cd example
protoc addressbook.proto --cpp_out=./

ls

addressbook.pb.cc
addressbook.pb.h
```

### openssl 安装
通过tar.zip进行源码安装

#### 源码安装
```
wget https://www.openssl.org/source/openssl-1.1.1n.tar.gz
sudo mkdir /usr/local/src/openssl
tar -xzvf openssl-1.1.1n.tar.gz -C /usr/local/src/openssl
cd /usr/local/src/openssl
sudo ./configure
sudo make
sudo make install
sudo ldconfig

openssl version
OpenSSL 1.1.1n  15 Mar 2022
```

#### 二进制文件安装
```
sudo apt install openssl openssl-dev openssl-doc -y
```

### openssl 库使用
```
cd ~/Projects/cpp_practice
clang-11 02_hash_test.c -lcrypto -o openssl_test.out
./openssl_test.out

md5=[f2d72259bdcf57257565788e4b1c3691]
```
# h3 Extension for PHP

[![Build Status](https://travis-ci.org/neatlife/php-h3.svg?branch=master)](https://travis-ci.org/neatlife/php-h3)

PHP binding for Uber's H3 spatial coordinate library write by c extension for php7.

For more information on H3 and for the full API documentation, please see the [H3 Documentation](https://uber.github.io/h3/).

-   Post **bug reports or feature requests** to the [Github Issues page](https://github.com/neatlife/php-h3/issues)
-   Ask **questions** by posting to the [H3 tag on StackOverflow](https://stackoverflow.com/questions/tagged/h3)

## Build from sources

first install official h3 library

```bash
% git clone https://github.com/uber/h3.git
% cd h3
% cmake3 -DBUILD_SHARED_LIBS=ON .
% make -j4
% make install
```

before compile php h3 extension, you may need run this:

```bash
sudo cp /usr/local/lib/libh3.* /usr/local/lib64/
sudo cp /usr/local/lib/libh3.* /usr/lib/
sudo cp /usr/local/lib/libh3.* /usr/lib64/
sudo echo '/usr/local/lib64/' >> /etc/ld.so.conf
sudo echo '/usr/lib64/' >> /etc/ld.so.conf
sudo ldconfig
```

then compile and install h3 php binding:

``` bash
% cd php-h3
% phpize
% ./configure
% make
% make install
```

## Building php_h3 on Windows

building h3 library
[Building H3 on Windows](https://github.com/uber/h3/blob/master/dev-docs/build_windows.md)

```bash
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release -DH3_ALLOC_PREFIX= ..
msbuild ALL_BUILD.vcxproj
msbuild RUN_TESTS.vcxproj
```

Copy h3.dll to php root directory

Add the php root directory to the system environment variable path

download [php-sdk-binary-tools](https://github.com/Microsoft/php-sdk-binary-tools) and php  source,PHP version:PHP 7.0+

building php_h3
[Build your own PHP on Windows](https://wiki.php.net/internals/windows/stepbystepbuild_sdk_2)

c:\php-sdk\phpsdk-vc15-x64.bat

If using Microsoft Build Tools 2019 run phpsdk-vc15-x64.bat,modify php-sdk\bin\phpsdk_setshell.bat to support

Copy php_h3 to source directory \ext\

Copy h3api.h to php_h3 directory

Add the following code to h3.c

```c
#pragma comment(lib, "C:\\php-sdk\\h3-master\\build\\bin\\Debug\\h3.lib")
#pragma comment(linker, "/NODEFAULTLIB:msvcrtd.lib")
```

Enter your PHP source directory


```bash

buildconf
configure --disable-all --enable-cli --enable-h3=shared

```
Copy php_h3.dll to php extension_dir


## Configration

enable h3.so extension in your php configration:

```
extension=h3.so
```



修复原版geoToH3 得到h3index 之后再h3ToGeo得到的值不一样的问题
zend_register_resource（ &indexed, le_h3_index)
后在
H3Index *indexed = (H3Index *) Z_RES_VAL_P(index_resource_zval);
获得的*indexed值不对
此处改为了 zend_register_resource（ indexed, le_h3_index)
H3Index *indexed = (H3Index *) Z_RES_VAL_P(index_resource_zval);
使用indexed 问题解决了  但原理咱不是很懂  有懂的大佬再修复修复其他的

只处理了geoToH3 h3ToLong h3GetResolution h3ToGeo kRing h3ToGeoBoundary h3GetBaseCell h3IsValid h3IsResClassIII h3IsPentagon hexRange方法

h3ToGeoBoundary中原版输出的lat lon 没有进行radsToDegs操作此处增加了

php资源类型用于存储文件句柄，mysql链接等指针类型的数据。把 H3index（int64_t）当成资源类型，在geotoh3存地址后会销毁内存，再取地址就是随机数了，把本身当指针存，取出时自然也不能取地址内的内存。

h3返回H3的索引值H3index最多占63个比特，8字节；php7 以后"l" 对应的c类型为 zend_long 也是一个8字节无符号整形，所以将程序返回类型改为zend_long。

其他返回结构体（如经纬度），在 PHP 中可以使用数组（HashTable）和对象类型，为编码简单选用了数组类型。

部分函数返回结果未经测试，欢迎测试后提交bug或者直接修改。

Windows编译器不支持变长数组，都改为了calloc()，Linux使用可以改为变长数组。


## ☑ TODO

### Global Helpers

- [X] h3ToLong (removed, pls use h3ToString)
- [X] h3FromLong (removed, pls use stringToH3)

### Indexing

- [X] geoToH3
- [X] h3ToGeoBoundary
- [X] h3ToGeo

### Inspection

- [X] h3GetResolution
- [X] h3GetBaseCell
- [X] h3ToString
- [X] h3IsValid
- [X] h3IsResClassIII
- [X] h3IsPentagon

### Neighbors

- [X] kRing
- [X] maxKringSize
- [X] kRingDistances
- [X] hexRange
- [X] hexRangeDistances
- [X] hexRanges
- [X] hexRing

### Distance

- [X] h3Distance

### Hierarchy

- [X] h3ToParent
- [X] h3ToChildren
- [X] maxH3ToChildrenSize
- [X] compact
- [X] uncompact
- [X] maxUncompactSize

### Regions

- [ ] polyfill
- [ ] maxPolyfillSize
- [ ] h3SetToLinkedGeo
- [ ] destroyLinkedPolygon

### Unidirectional Edges

- [X] h3IndexesAreNeighbors
- [X] getH3UnidirectionalEdge
- [X] h3UnidirectionalEdgeIsValid
- [X] getOriginH3IndexFromUnidirectionalEdge
- [X] getDestinationH3IndexFromUnidirectionalEdge
- [X] getH3IndexesFromUnidirectionalEdge
- [X] getH3UnidirectionalEdgesFromHexagon
- [X] getH3UnidirectionalEdgeBoundary

### Miscellaneous

- [X] degsToRads
- [X] radsToDegs
- [X] hexAreaKm2
- [X] hexAreaM2
- [X] edgeLengthKm
- [X] edgeLengthM
- [X] numHexagons

## Examples

```php
$index = geoToH3(40.689167, -74.044444, 10);

var_dump($index);

var_dump(h3ToGeo($index));

var_dump(h3ToGeoBoundary($index));

var_dump(h3GetResolution($index));

var_dump(h3GetBaseCell($index));

var_dump(h3ToString($index, "hello world"));

var_dump(h3IsValid($index));

var_dump(h3IsResClassIII($index));

var_dump(h3IsPentagon($index));

var_dump(kRing($index, 5));

var_dump(maxKringSize(5));

var_dump(kRingDistances($index, 5));

var_dump(hexRange($index, 5));

var_dump(hexRangeDistances($index, 5));

$index1 = geoToH3(341.689167, -173.044444, 10);

var_dump(hexRanges([$index, $index1], 5));

var_dump(hexRing($index, 5));

var_dump(h3Distance($index, $index1));

var_dump(h3ToParent($index, 5));

var_dump(h3ToChildren($index, 2));

var_dump(maxH3ToChildrenSize($index, 2));

var_dump($rads = degsToRads(40.689167));

var_dump(radsToDegs($rads));

var_dump(hexAreaKm2(10));

var_dump(hexAreaM2(10));

var_dump(edgeLengthKm(10));

var_dump(edgeLengthM(10));

var_dump(numHexagons(2));


var_dump(h3IndexesAreNeighbors($index, $index1));
var_dump(getH3UnidirectionalEdge($index, $index1));
var_dump(h3UnidirectionalEdgeIsValid($index));
var_dump(getOriginH3IndexFromUnidirectionalEdge($index));
var_dump(getDestinationH3IndexFromUnidirectionalEdge($index));
var_dump(getH3IndexesFromUnidirectionalEdge($index));
var_dump(getH3UnidirectionalEdgesFromHexagon($index));
var_dump(getH3UnidirectionalEdgeBoundary($index));

var_dump($compacts = h3Compact([$index, $index1]));
var_dump(uncompact($compacts, 2));
var_dump(maxUncompactSize($compacts, 2));
```

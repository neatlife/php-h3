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

## Configration

enable h3.so extension in your php configration:

```
extension=h3.so
```

## ☑ TODO

### Global Helpers

- [X] h3ToLong
- [X] h3FromLong

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

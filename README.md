# h3 Extension for PHP

PHP binding for Uber's H3 spatial coordinate library write by c extension for php.

## Build from sources

first install official h3 library
```bash
% git clone https://github.com/uber/h3.git
% cd h3
% cmake3 .
% make -j4
% make install
```

then install h3 php binding:

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
- [ ] hexRing

### Distance

- [X] h3Distance

### Hierarchy

- [ ] h3ToParent
- [ ] h3ToChildren
- [ ] maxH3ToChildrenSize
- [ ] compact
- [ ] uncompact
- [ ] maxUncompactSize

### Regions

- [ ] polyfill
- [ ] maxPolyfillSize
- [ ] h3SetToLinkedGeo
- [ ] destroyLinkedPolygon

### Unidirectional Edges

- [ ] h3IndexesAreNeighbors
- [ ] getH3UnidirectionalEdge
- [ ] h3UnidirectionalEdgeIsValid
- [ ] getOriginH3IndexFromUnidirectionalEdge
- [ ] getDestinationH3IndexFromUnidirectionalEdge
- [ ] getH3IndexesFromUnidirectionalEdge
- [ ] getH3UnidirectionalEdgesFromHexagon
- [ ] getH3UnidirectionalEdgeBoundary

### Miscellaneous

- [ ] degsToRads
- [ ] radsToDegs
- [ ] hexAreaKm2
- [ ] hexAreaM2
- [ ] edgeLengthKm
- [ ] edgeLengthM
- [ ] numHexagons

## Function

detail function documents please visit official document page: [Documentation](https://uber.github.io/h3/#/documentation/api-reference/indexing)

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

var_dump(hexRanges([$index], 5));

$index1 = geoToH3(341.689167, -173.044444, 10);
var_dump(h3Distance($index, $index1));
```

# h3 Extension for PHP

PHP binding for Uber's H3 spatial coordinate library write by c extension for php.

## Build from sources

first install office h3 library
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

- [ ] kRing
- [ ] maxKringSize
- [ ] kRingDistances
- [ ] hexRange
- [ ] hexRangeDistances
- [ ] hexRanges
- [ ] hexRing

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

* degsToRads  — Indexes the location at the specified resolution.
* h3ToGeoBoundary — Finds the centroid of the index.
* h3ToGeo — Finds the boundary of the index.

### degsToRads

resource $dblink **degsToRads** ( \$lat, \$lon, \$resolution )

```php
$index = degsToRads($lat, $lon, $resolution);
var_dump($index);
```
Returns 0 on error.

### h3ToGeoBoundary

array  **h3ToGeoBoundary** ( \$index )

```php
var_dump(h3ToGeoBoundary($index));
```

### h3ToGeo

array $value **h3ToGeo** ( \$index )

```php
var_dump(h3ToGeo($index));
```

## Examples

```php
$index = geoToH3(40.689167, -74.044444, 10);

var_dump($index);

var_dump(h3GetResolution($index));

var_dump(h3GetBaseCell($index));

var_dump(h3ToString($index, 0));

var_dump($index);

var_dump(h3IsValid($index));

var_dump(h3IsResClassIII($index));

var_dump(h3IsPentagon($index));
```

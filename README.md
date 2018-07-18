# h3 Extension for PHP

PHP binding for Uber's H3 spatial coordinate library write by c extension for php.

## Build from sources

``` bash
% cd php-h3
% phpize
% ./configure
% make
% make install
```

## Configration

h3.ini:

```
extension=h3.so
```

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
// degsToRads
$index = degsToRads($lat, $lon, $resolution);

var_dump($index);
```

```php
// h3ToGeoBoundary
$index = degsToRads($lat, $lon, $resolution);

var_dump(h3ToGeoBoundary($index));
```

```php
// h3ToGeoBoundary
$index = degsToRads($lat, $lon, $resolution);

var_dump(h3ToGeo($index));
```

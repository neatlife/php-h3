<?php

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

echo "hello world\n";

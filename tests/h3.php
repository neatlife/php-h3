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

$lat=40.689167;$lon=-74.044444;
$str="8a2a1072b59ffff";
$h3=stringtoh3($str);
$arr=h3togeo($h3);

if(abs(degsToRads($lat)-degsToRads($arr["lat"]))< (0.000005))
{
	echo "got expected h3ToGeo output<br>";
}

$res=h3GetResolution($h3);
$h2=geotoh3($lat,$lon,$res);
if($h2=$h3)
	echo "got expected geoToH3 output";


$h3="8a2a1072b59ffff";
$h3l=stringtoh3($h3);
$h3b=h3ToGeoBoundary($h3l);
if(abs($h3b[1]["lat"]-40.690058601)<1e-3)
	echo "ok";


//
$h3=stringtoh3("0x890dab6220bffff");
var_dump(h3SetToLinkedGeo([0x89283082813ffff, 0x8928308281bffff, 0x8928308280bffff,
0x8928308280fffff, 0x89283082807ffff, 0x89283082817ffff,
0x8928308289bffff, 0x892830828d7ffff, 0x892830828c3ffff,
0x892830828cbffff, 0x89283082853ffff, 0x89283082843ffff,
0x8928308284fffff, 0x8928308287bffff, 0x89283082863ffff,
0x89283082867ffff, 0x8928308282bffff, 0x89283082823ffff,
0x89283082837ffff, 0x892830828afffff, 0x892830828a3ffff,
0x892830828b3ffff, 0x89283082887ffff, 0x89283082883ffff]));


$geiface=[
"geofence"=>
[["lat"=>37.813318999889,"lon"=>-122.40898669969],
["lat"=>37.786630199907,"lon"=>-122.3805436997],
["lat"=>37.719806199904,"lon"=>-122.3544736997],
["lat"=>37.707613199904,"lon"=>-122.51234369969],
["lat"=>37.783587199903,"lon"=>-122.5247186997],
["lat"=>37.815157199906,"lon"=>-122.4798766997]],

"holes"=>
[[["lat"=>37.786980199908,"lon"=>-122.4471196997],
["lat"=>37.766410199904,"lon"=>-122.4590776997],
["lat"=>37.771068199907,"lon"=>-122.4137096997]]]
];

$a=maxPolyfillSize($geiface,9);
if($a==5613)
echo "got expected max polyfill size";

echo "hello world\n";

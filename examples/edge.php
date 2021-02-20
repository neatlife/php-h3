<?php

// map official examples/edge.c

$origin = stringToH3('0x8a2a1072b59ffff');
$destination = stringToH3('0x8a2a1072b597fff');  // north of the origin

$edge = getH3UnidirectionalEdge($origin, $destination);
printf("The edge is %s\n", h3ToString($edge));

$boundaries = getH3UnidirectionalEdgeBoundary($edge);
foreach ($boundaries as $bundary) {
	printf("Edge vertex #%d: %lf, %lf\n", v,
		   radsToDegs($boundary[0]),
		   radsToDegs($boundary[1]));
}
// Output:
// The edge is 16a2a1072b59ffff
// Edge vertex #0: 40.690059, -74.044152
// Edge vertex #1: 40.689908, -74.045062

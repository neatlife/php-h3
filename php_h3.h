/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/


#ifndef PHP_H3_H
#define PHP_H3_H

extern zend_module_entry h3_module_entry;
#define phpext_h3_ptr &h3_module_entry

#define PHP_H3_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_H3_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_H3_API __attribute__ ((visibility("default")))
#else
#	define PHP_H3_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(h3)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(h3)
*/

/* Always refer to the globals in your function as H3_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define H3_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(h3, v)

#if defined(ZTS) && defined(COMPILE_DL_H3)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

static int le_h3_index;
static int le_h3_boundary;

#endif	/* PHP_H3_H */

//Indexing functions
PHP_FUNCTION(geoToH3);
PHP_FUNCTION(h3ToGeo);
PHP_FUNCTION(h3ToGeoBoundary);

//Index inspection functions
PHP_FUNCTION(h3GetResolution);
PHP_FUNCTION(h3GetBaseCell);
PHP_FUNCTION(stringToH3);
PHP_FUNCTION(h3ToString);
PHP_FUNCTION(h3IsValid);
PHP_FUNCTION(h3IsResClassIII);
PHP_FUNCTION(h3IsPentagon);
PHP_FUNCTION(h3GetFaces);
PHP_FUNCTION(maxFaceCount);

//Grid traversal functions
PHP_FUNCTION(kRing);
PHP_FUNCTION(maxKringSize);
PHP_FUNCTION(kRingDistances);
PHP_FUNCTION(hexRange);
PHP_FUNCTION(hexRangeDistances);
PHP_FUNCTION(hexRanges);
PHP_FUNCTION(hexRing);
PHP_FUNCTION(h3Line);
PHP_FUNCTION(h3LineSize);
PHP_FUNCTION(h3Distance);
PHP_FUNCTION(experimentalH3ToLocalIj);
PHP_FUNCTION(experimentalLocalIjToH3);

//Hierarchical grid functions
PHP_FUNCTION(h3ToParent);
PHP_FUNCTION(h3ToChildren);
PHP_FUNCTION(maxH3ToChildrenSize);
PHP_FUNCTION(h3ToCenterChild);
PHP_FUNCTION(h3Compact);
PHP_FUNCTION(uncompact);
PHP_FUNCTION(maxUncompactSize);

//Unidirectional edge functions
PHP_FUNCTION(h3IndexesAreNeighbors);
PHP_FUNCTION(getH3UnidirectionalEdge);
PHP_FUNCTION(h3UnidirectionalEdgeIsValid);
PHP_FUNCTION(getOriginH3IndexFromUnidirectionalEdge);
PHP_FUNCTION(getDestinationH3IndexFromUnidirectionalEdge);
PHP_FUNCTION(getH3IndexesFromUnidirectionalEdge);
PHP_FUNCTION(getH3UnidirectionalEdgesFromHexagon);
PHP_FUNCTION(getH3UnidirectionalEdgeBoundary);

//Region functions
PHP_FUNCTION(polyfill);
PHP_FUNCTION(maxPolyfillSize);
PHP_FUNCTION(h3SetToLinkedGeo);

//Miscellaneous H3 functions
PHP_FUNCTION(degsToRads);
PHP_FUNCTION(radsToDegs);
PHP_FUNCTION(hexAreaKm2);
PHP_FUNCTION(hexAreaM2);
PHP_FUNCTION(cellAreaKm2);
PHP_FUNCTION(cellAreaM2);
PHP_FUNCTION(cellAreaRads2);
PHP_FUNCTION(edgeLengthKm);
PHP_FUNCTION(edgeLengthM);
PHP_FUNCTION(exactEdgeLengthKm);
PHP_FUNCTION(exactEdgeLengthM);
PHP_FUNCTION(exactEdgeLengthRads);
PHP_FUNCTION(numHexagons);
PHP_FUNCTION(getRes0Indexes);
PHP_FUNCTION(res0IndexCount);
PHP_FUNCTION(getPentagonIndexes);
PHP_FUNCTION(pentagonIndexCount);
PHP_FUNCTION(pointDistKm);
PHP_FUNCTION(pointDistM);
PHP_FUNCTION(pointDistRads);

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
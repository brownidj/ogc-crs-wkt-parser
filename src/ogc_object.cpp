/* ------------------------------------------------------------------------- */
/* Copyright 2013 Esri                                                       */
/*                                                                           */
/* Licensed under the Apache License, Version 2.0 (the "License");           */
/* you may not use this file except in compliance with the License.          */
/* You may obtain a copy of the License at                                   */
/*                                                                           */
/*     http://www.apache.org/licenses/LICENSE-2.0                            */
/*                                                                           */
/* Unless required by applicable law or agreed to in writing, software       */
/* distributed under the License is distributed on an "AS IS" BASIS,         */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  */
/* See the License for the specific language governing permissions and       */
/* limitations under the License.                                            */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* generic (top-level) object                                                */
/* ------------------------------------------------------------------------- */

#include "ogc_common.h"

namespace OGC {

const char * ogc_object :: obj_kwd() { return OGC_OBJ_KWD_OBJECT; }

bool ogc_object :: is_kwd(const char * kwd)
{
   return ogc_string::is_equal(kwd, obj_kwd());
}

/*------------------------------------------------------------------------
 * strict parsing
 */
bool ogc_object :: _strict_parsing = true;

bool ogc_object :: get_strict_parsing()
{
   return _strict_parsing;
}

bool ogc_object :: set_strict_parsing(bool on_off)
{
   bool rc = _strict_parsing;
   _strict_parsing = on_off;
   return rc;
}

/*------------------------------------------------------------------------
 * destroy
 */
ogc_object :: ~ogc_object()
{
}

ogc_object * ogc_object :: destroy(
   ogc_object * obj)
{
   if ( obj != OGC_NULL )
   {
      delete obj;
   }
   return OGC_NULL;
}

/*------------------------------------------------------------------------
 * object from tokens
 */
ogc_object * ogc_object :: from_tokens(
   const ogc_token * t,
   int               start,
   int *             pend,
   ogc_error *       err)
{
   if ( t == OGC_NULL )
   {
      ogc_error::set(err, OGC_ERR_WKT_EMPTY_STRING, obj_kwd());
      return OGC_NULL;
   }

   const char * kwd = t->_arr[start].str;

#  define CHECK(n) \
   if ( ogc_##n::is_kwd(kwd) ) \
      return ogc_##n :: from_tokens(t, start, pend, err)

   CHECK( abrtrans        );
   CHECK( anchor          );
   CHECK( angunit         );
   CHECK( area_extent     );
   CHECK( axis            );
   CHECK( base_engr_crs   );
   CHECK( base_geod_crs   );
   CHECK( base_param_crs  );
   CHECK( base_proj_crs   );
   CHECK( base_time_crs   );
   CHECK( base_vert_crs   );
   CHECK( bbox_extent     );
   CHECK( bearing         );
   CHECK( bound_crs       );
   CHECK( citation        );
   CHECK( compound_crs    );
   CHECK( conversion      );
   CHECK( coord_op        );
   CHECK( cs              );
   CHECK( deriving_conv   );
   CHECK( ellipsoid       );
   CHECK( engr_crs        );
   CHECK( engr_datum      );
   CHECK( geod_crs        );
   CHECK( geod_datum      );
   CHECK( id              );
   CHECK( image_crs       );
   CHECK( image_datum     );
   CHECK( lenunit         );
   CHECK( meridian        );
   CHECK( method          );
   CHECK( op_accuracy     );
   CHECK( order           );
   CHECK( parameter       );
   CHECK( param_file      );
   CHECK( param_crs       );
   CHECK( param_datum     );
   CHECK( paramunit       );
   CHECK( primem          );
   CHECK( proj_crs        );
   CHECK( remark          );
   CHECK( scaleunit       );
   CHECK( scope           );
   CHECK( time_crs        );
   CHECK( time_datum      );
   CHECK( time_extent     );
   CHECK( time_origin     );
   CHECK( timeunit        );
   CHECK( unit            );
   CHECK( uri             );
   CHECK( vert_crs        );
   CHECK( vert_datum      );
   CHECK( vert_extent     );

#  undef CHECK

   ogc_error::set(err, OGC_ERR_WKT_UNKNOWN_KEYWORD, obj_kwd(), kwd);
   return OGC_NULL;
}

/*------------------------------------------------------------------------
 * object from WKT
 */
ogc_object* ogc_object :: from_wkt(
   const char * wkt,
   ogc_error *  err)
{
   ogc_token t;

   if ( ! t.tokenize(wkt, obj_kwd(), err) )
   {
      return OGC_NULL;
   }

   return from_tokens(&t, 0, OGC_NULL, err);
}

/*------------------------------------------------------------------------
 * object to WKT
 */
bool ogc_object :: to_wkt(
   const ogc_object * obj,
   char      buffer[],
   int       options,
   size_t    buflen)
{
   if ( buffer == OGC_NULL )
      return false;
   *buffer = 0;

   if ( obj == OGC_NULL )
      return true;

   return obj->to_wkt(buffer, options, buflen);
}

bool ogc_object :: to_wkt(
   char      buffer[],
   int       options,
   size_t    buflen) const
{
   if ( buffer == OGC_NULL )
      return false;
   *buffer = 0;

   if ( !is_visible() )
      return true;

   switch (_obj_type)
   {
#  define CASE(o,n) \
      case OGC_OBJ_TYPE_##o: \
         return (reinterpret_cast<const ogc_##n *>(this))-> \
                to_wkt(buffer, options, buflen)

      CASE( ABRTRANS,        abrtrans        );
      CASE( ANCHOR,          anchor          );
      CASE( ANGUNIT,         angunit         );
      CASE( AREA_EXTENT,     area_extent     );
      CASE( AXIS,            axis            );
      CASE( BASE_ENGR_CRS,   base_engr_crs   );
      CASE( BASE_GEOD_CRS,   base_geod_crs   );
      CASE( BASE_PARAM_CRS,  base_param_crs  );
      CASE( BASE_PROJ_CRS,   base_proj_crs   );
      CASE( BASE_TIME_CRS,   base_time_crs   );
      CASE( BASE_VERT_CRS,   base_vert_crs   );
      CASE( BBOX_EXTENT,     bbox_extent     );
      CASE( BEARING,         bearing         );
      CASE( BOUND_CRS,       bound_crs       );
      CASE( CITATION,        citation        );
      CASE( COMPOUND_CRS,    compound_crs    );
      CASE( CONVERSION,      conversion      );
      CASE( COORD_OP,        coord_op        );
      CASE( CS,              cs              );
      CASE( DERIVING_CONV,   deriving_conv   );
      CASE( ELLIPSOID,       ellipsoid       );
      CASE( ENGR_CRS,        engr_crs        );
      CASE( ENGR_DATUM,      engr_datum      );
      CASE( GEOD_CRS,        geod_crs        );
      CASE( GEOD_DATUM,      geod_datum      );
      CASE( ID,              id              );
      CASE( IMAGE_CRS,       image_crs       );
      CASE( IMAGE_DATUM,     image_datum     );
      CASE( LENUNIT,         lenunit         );
      CASE( MERIDIAN,        meridian        );
      CASE( METHOD,          method          );
      CASE( OP_ACCURACY,     op_accuracy     );
      CASE( ORDER,           order           );
      CASE( PARAMETER,       parameter       );
      CASE( PARAM_FILE,      param_file      );
      CASE( PARAM_CRS,       param_crs       );
      CASE( PARAM_DATUM,     param_datum     );
      CASE( PARAMUNIT,       paramunit       );
      CASE( PRIMEM,          primem          );
      CASE( PROJ_CRS,        proj_crs        );
      CASE( REMARK,          remark          );
      CASE( SCALEUNIT,       scaleunit       );
      CASE( SCOPE,           scope           );
      CASE( TIME_CRS,        time_crs        );
      CASE( TIME_DATUM,      time_datum      );
      CASE( TIME_EXTENT,     time_extent     );
      CASE( TIME_ORIGIN,     time_origin     );
      CASE( TIMEUNIT,        timeunit        );
      CASE( UNIT,            unit            );
      CASE( URI,             uri             );
      CASE( VERT_CRS,        vert_crs        );
      CASE( VERT_DATUM,      vert_datum      );
      CASE( VERT_EXTENT,     vert_extent     );

#  undef CASE

      default:
         break;
   }

   return false;
}

/*------------------------------------------------------------------------
 * clone
 */
ogc_object * ogc_object :: clone(const ogc_object * obj)
{
   if ( obj == OGC_NULL )
      return OGC_NULL;
   return obj->clone();
}

ogc_object * ogc_object :: clone() const
{
   switch (_obj_type)
   {
#  define CASE(o,n) \
      case OGC_OBJ_TYPE_##o: \
         return (reinterpret_cast<const ogc_##n *>(this))->clone()

      CASE( ABRTRANS,        abrtrans        );
      CASE( ANCHOR,          anchor          );
      CASE( ANGUNIT,         angunit         );
      CASE( AREA_EXTENT,     area_extent     );
      CASE( AXIS,            axis            );
      CASE( BASE_ENGR_CRS,   base_engr_crs   );
      CASE( BASE_GEOD_CRS,   base_geod_crs   );
      CASE( BASE_PARAM_CRS,  base_param_crs  );
      CASE( BASE_PROJ_CRS,   base_proj_crs   );
      CASE( BASE_TIME_CRS,   base_time_crs   );
      CASE( BASE_VERT_CRS,   base_vert_crs   );
      CASE( BBOX_EXTENT,     bbox_extent     );
      CASE( BEARING,         bearing         );
      CASE( BOUND_CRS,       bound_crs       );
      CASE( CITATION,        citation        );
      CASE( COMPOUND_CRS,    compound_crs    );
      CASE( CONVERSION,      conversion      );
      CASE( COORD_OP,        coord_op        );
      CASE( CS,              cs              );
      CASE( DERIVING_CONV,   deriving_conv   );
      CASE( ELLIPSOID,       ellipsoid       );
      CASE( ENGR_CRS,        engr_crs        );
      CASE( ENGR_DATUM,      engr_datum      );
      CASE( GEOD_CRS,        geod_crs        );
      CASE( GEOD_DATUM,      geod_datum      );
      CASE( ID,              id              );
      CASE( IMAGE_CRS,       image_crs       );
      CASE( IMAGE_DATUM,     image_datum     );
      CASE( LENUNIT,         lenunit         );
      CASE( MERIDIAN,        meridian        );
      CASE( METHOD,          method          );
      CASE( OP_ACCURACY,     op_accuracy     );
      CASE( ORDER,           order           );
      CASE( PARAMETER,       parameter       );
      CASE( PARAM_FILE,      param_file      );
      CASE( PARAM_CRS,       param_crs       );
      CASE( PARAM_DATUM,     param_datum     );
      CASE( PARAMUNIT,       paramunit       );
      CASE( PRIMEM,          primem          );
      CASE( PROJ_CRS,        proj_crs        );
      CASE( REMARK,          remark          );
      CASE( SCALEUNIT,       scaleunit       );
      CASE( SCOPE,           scope           );
      CASE( TIME_CRS,        time_crs        );
      CASE( TIME_DATUM,      time_datum      );
      CASE( TIME_EXTENT,     time_extent     );
      CASE( TIME_ORIGIN,     time_origin     );
      CASE( TIMEUNIT,        timeunit        );
      CASE( UNIT,            unit            );
      CASE( URI,             uri             );
      CASE( VERT_CRS,        vert_crs        );
      CASE( VERT_DATUM,      vert_datum      );
      CASE( VERT_EXTENT,     vert_extent     );

#  undef CASE

      default:
         break;
   }

   return OGC_NULL;
}

/*------------------------------------------------------------------------
 * compare for computational equality
 */
bool ogc_object :: is_equal(
   const ogc_object * p1,
   const ogc_object * p2)
{
   if ( p1 == OGC_NULL && p2 == OGC_NULL ) return true;
   if ( p1 == OGC_NULL || p2 == OGC_NULL ) return false;
   if ( p1->obj_type() != p2->obj_type() ) return false;

   switch ( p1->obj_type() )
   {
#  define CASE(o,n) \
      case OGC_OBJ_TYPE_##o: \
         return ogc_##n::is_equal(reinterpret_cast<const ogc_##n *>(p1), \
                                  reinterpret_cast<const ogc_##n *>(p2))

      CASE( ABRTRANS,        abrtrans        );
      CASE( ANCHOR,          anchor          );
      CASE( ANGUNIT,         angunit         );
      CASE( AREA_EXTENT,     area_extent     );
      CASE( AXIS,            axis            );
      CASE( BASE_ENGR_CRS,   base_engr_crs   );
      CASE( BASE_GEOD_CRS,   base_geod_crs   );
      CASE( BASE_PARAM_CRS,  base_param_crs  );
      CASE( BASE_PROJ_CRS,   base_proj_crs   );
      CASE( BASE_TIME_CRS,   base_time_crs   );
      CASE( BASE_VERT_CRS,   base_vert_crs   );
      CASE( BBOX_EXTENT,     bbox_extent     );
      CASE( BEARING,         bearing         );
      CASE( BOUND_CRS,       bound_crs       );
      CASE( CITATION,        citation        );
      CASE( COMPOUND_CRS,    compound_crs    );
      CASE( CONVERSION,      conversion      );
      CASE( COORD_OP,        coord_op        );
      CASE( CS,              cs              );
      CASE( DERIVING_CONV,   deriving_conv   );
      CASE( ELLIPSOID,       ellipsoid       );
      CASE( ENGR_CRS,        engr_crs        );
      CASE( ENGR_DATUM,      engr_datum      );
      CASE( GEOD_CRS,        geod_crs        );
      CASE( GEOD_DATUM,      geod_datum      );
      CASE( ID,              id              );
      CASE( IMAGE_CRS,       image_crs       );
      CASE( IMAGE_DATUM,     image_datum     );
      CASE( LENUNIT,         lenunit         );
      CASE( MERIDIAN,        meridian        );
      CASE( METHOD,          method          );
      CASE( OP_ACCURACY,     op_accuracy     );
      CASE( ORDER,           order           );
      CASE( PARAMETER,       parameter       );
      CASE( PARAM_FILE,      param_file      );
      CASE( PARAM_CRS,       param_crs       );
      CASE( PARAM_DATUM,     param_datum     );
      CASE( PARAMUNIT,       paramunit       );
      CASE( PRIMEM,          primem          );
      CASE( PROJ_CRS,        proj_crs        );
      CASE( REMARK,          remark          );
      CASE( SCALEUNIT,       scaleunit       );
      CASE( SCOPE,           scope           );
      CASE( TIME_CRS,        time_crs        );
      CASE( TIME_DATUM,      time_datum      );
      CASE( TIME_EXTENT,     time_extent     );
      CASE( TIME_ORIGIN,     time_origin     );
      CASE( TIMEUNIT,        timeunit        );
      CASE( UNIT,            unit            );
      CASE( URI,             uri             );
      CASE( VERT_CRS,        vert_crs        );
      CASE( VERT_DATUM,      vert_datum      );
      CASE( VERT_EXTENT,     vert_extent     );

#  undef CASE

      default:
         break;
   }

   return false;
}

bool ogc_object :: is_equal(
   const ogc_object * p) const
{
   return is_equal(this, p);
}

/*------------------------------------------------------------------------
 * compare
 */
bool ogc_object :: is_identical(
   const ogc_object * p1,
   const ogc_object * p2)
{
   if ( p1 == OGC_NULL && p2 == OGC_NULL ) return true;
   if ( p1 == OGC_NULL || p2 == OGC_NULL ) return false;
   if ( p1->obj_type() != p2->obj_type() ) return false;

   switch ( p1->obj_type() )
   {
#  define CASE(o,n) \
      case OGC_OBJ_TYPE_##o: \
         return ogc_##n::is_identical(reinterpret_cast<const ogc_##n *>(p1), \
                                      reinterpret_cast<const ogc_##n *>(p2))

      CASE( ABRTRANS,        abrtrans        );
      CASE( ANCHOR,          anchor          );
      CASE( ANGUNIT,         angunit         );
      CASE( AREA_EXTENT,     area_extent     );
      CASE( AXIS,            axis            );
      CASE( BASE_ENGR_CRS,   base_engr_crs   );
      CASE( BASE_GEOD_CRS,   base_geod_crs   );
      CASE( BASE_PARAM_CRS,  base_param_crs  );
      CASE( BASE_PROJ_CRS,   base_proj_crs   );
      CASE( BASE_TIME_CRS,   base_time_crs   );
      CASE( BASE_VERT_CRS,   base_vert_crs   );
      CASE( BBOX_EXTENT,     bbox_extent     );
      CASE( BEARING,         bearing         );
      CASE( BOUND_CRS,       bound_crs       );
      CASE( CITATION,        citation        );
      CASE( COMPOUND_CRS,    compound_crs    );
      CASE( CONVERSION,      conversion      );
      CASE( COORD_OP,        coord_op        );
      CASE( CS,              cs              );
      CASE( DERIVING_CONV,   deriving_conv   );
      CASE( ELLIPSOID,       ellipsoid       );
      CASE( ENGR_CRS,        engr_crs        );
      CASE( ENGR_DATUM,      engr_datum      );
      CASE( GEOD_CRS,        geod_crs        );
      CASE( GEOD_DATUM,      geod_datum      );
      CASE( ID,              id              );
      CASE( IMAGE_CRS,       image_crs       );
      CASE( IMAGE_DATUM,     image_datum     );
      CASE( LENUNIT,         lenunit         );
      CASE( MERIDIAN,        meridian        );
      CASE( METHOD,          method          );
      CASE( OP_ACCURACY,     op_accuracy     );
      CASE( ORDER,           order           );
      CASE( PARAMETER,       parameter       );
      CASE( PARAM_FILE,      param_file      );
      CASE( PARAM_CRS,       param_crs       );
      CASE( PARAM_DATUM,     param_datum     );
      CASE( PARAMUNIT,       paramunit       );
      CASE( PRIMEM,          primem          );
      CASE( PROJ_CRS,        proj_crs        );
      CASE( REMARK,          remark          );
      CASE( SCALEUNIT,       scaleunit       );
      CASE( SCOPE,           scope           );
      CASE( TIME_CRS,        time_crs        );
      CASE( TIME_DATUM,      time_datum      );
      CASE( TIME_EXTENT,     time_extent     );
      CASE( TIME_ORIGIN,     time_origin     );
      CASE( TIMEUNIT,        timeunit        );
      CASE( UNIT,            unit            );
      CASE( URI,             uri             );
      CASE( VERT_CRS,        vert_crs        );
      CASE( VERT_DATUM,      vert_datum      );
      CASE( VERT_EXTENT,     vert_extent     );

#  undef CASE

      default:
         break;
   }

   return false;
}

bool ogc_object :: is_identical(
   const ogc_object * p) const
{
   return is_identical(this, p);
}

} /* namespace OGC */

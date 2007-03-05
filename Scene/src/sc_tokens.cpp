// Copyright (c) 2002 Steffen Buchholz

#include "sc_tokens.h"
#include <stdlib.h>
#include <string.h>

sc_TokenPair tokenMap[] = {
  // sorted below this line
  {"PL_LIGHT_NONE", TOK_PL_LIGHT_NONE},
  {"PL_LIGHT_POINT", TOK_PL_LIGHT_POINT},
  {"PL_LIGHT_POINT_ANGLE", TOK_PL_LIGHT_POINT_ANGLE},
  {"PL_LIGHT_POINT_DISTANCE", TOK_PL_LIGHT_POINT_DISTANCE},
  {"PL_LIGHT_VECTOR", TOK_PL_LIGHT_VECTOR},
  {"PL_SHADE_FLAT", TOK_PL_SHADE_FLAT},
  {"PL_SHADE_FLAT_DISTANCE", TOK_PL_SHADE_FLAT_DISTANCE},
  {"PL_SHADE_GOURAUD", TOK_PL_SHADE_GOURAUD},
  {"PL_SHADE_GOURAUD_DISTANCE", TOK_PL_SHADE_GOURAUD_DISTANCE},
  {"PL_SHADE_NONE", TOK_PL_SHADE_NONE},
  {"PL_TEXENV_ADD", TOK_PL_TEXENV_ADD},
  {"PL_TEXENV_AVG", TOK_PL_TEXENV_AVG},
  {"PL_TEXENV_ENVMINUSTEX", TOK_PL_TEXENV_ENVMINUSTEX},
  {"PL_TEXENV_MAX", TOK_PL_TEXENV_MAX},
  {"PL_TEXENV_MIN", TOK_PL_TEXENV_MIN},
  {"PL_TEXENV_MUL", TOK_PL_TEXENV_MUL},
  {"PL_TEXENV_TEXMINUSENV", TOK_PL_TEXENV_TEXMINUSENV},
  {"ambient0", TOK_ambient0},
  {"ambient1", TOK_ambient1},
  {"ambient2", TOK_ambient2},
  {"backfacecull", TOK_backfacecull},
  {"background", TOK_background},
  {"box", TOK_box},
  {"camera", TOK_camera},
  {"cameras", TOK_cameras},
  {"cap", TOK_cap},
  {"capbottom", TOK_capbottom},
  {"captop", TOK_captop},
  {"cob", TOK_cob},
  {"color", TOK_color},
  {"cone", TOK_cone},
  {"cylinder", TOK_cylinder},
  {"d", TOK_d},
  {"diffuse0", TOK_diffuse0},
  {"diffuse1", TOK_diffuse1},
  {"diffuse2", TOK_diffuse2},
  {"divh", TOK_divh},
  {"divr", TOK_divr},
  {"environment", TOK_environment},
  {"envscaling", TOK_envscaling},
  {"fadedist", TOK_fadedist},
  {"falloff", TOK_falloff},
  {"flipnormals", TOK_flipnormals},
  {"fov", TOK_fov},
  {"global", TOK_global},
  {"h", TOK_h},
  {"id", TOK_id},
  {"intensity", TOK_intensity},
  {"jaw", TOK_jaw},
  {"light", TOK_light},
  {"lights", TOK_lights},
  {"material", TOK_material},
  {"materials", TOK_materials},
  {"no", TOK_no},
  {"numgradients", TOK_numgradients},
  {"o3ds", TOK_o3ds},
  {"obj", TOK_obj},
  {"objects", TOK_objects},
  {"optimize", TOK_optimize},
  {"pan", TOK_pan},
  {"perspectivecorrect", TOK_perspectivecorrect},
  {"pitch", TOK_pitch},
  {"plane", TOK_plane},
  {"r", TOK_r},
  {"r1", TOK_r1},
  {"r2", TOK_r2},
  {"relative", TOK_relative},
  {"res", TOK_res},
  {"rescale", TOK_rescale},
  {"roll", TOK_roll},
  {"rotate", TOK_rotate},
  {"scale", TOK_scale},
  {"scene", TOK_scene},
  {"shadetype", TOK_shadetype},
  {"shininess", TOK_shininess},
  {"sort", TOK_sort},
  {"specular0", TOK_specular0},
  {"specular1", TOK_specular1},
  {"specular2", TOK_specular2},
  {"sphere", TOK_sphere},
  {"src", TOK_src},
  {"target", TOK_target},
  {"texenvmode", TOK_texenvmode},
  {"texscaling", TOK_texscaling},
  {"texture", TOK_texture},
  {"textures", TOK_textures},
  {"torus", TOK_torus},
  {"transformations", TOK_transformations},
  {"translate", TOK_translate},
  {"transparent", TOK_transparent},
  {"type", TOK_type},
  {"w", TOK_w},
  {"x", TOK_x},
  {"xa", TOK_xa},
  {"xp", TOK_xp},
  {"y", TOK_y},
  {"ya", TOK_ya},
  {"yes", TOK_yes},
  {"yp", TOK_yp},
  {"z", TOK_z},
  {"za", TOK_za},
  {"zp", TOK_zp}
  // sorted above this line
};

unsigned int tokenMapSize = sizeof tokenMap / sizeof tokenMap[0];

/**
** Vergleichsfunktion für bsearch und sc_TokenPair
*/
static int
cmpTokenPair( sc_TokenPair *arg1, sc_TokenPair *arg2 )
{
   /* Vergleich der Schlüssel */
	return strcmp( arg1->key, arg2->key );
}


sc_TokenPair *
sc_search(const char *name)
{
	sc_TokenPair key = {name, TOK_UNKNOWN};  
	sc_TokenPair *res = (sc_TokenPair *)
		bsearch(&key, tokenMap, tokenMapSize, sizeof key, (int (*)(const 
			void*, const void*))cmpTokenPair);
	return res;
}

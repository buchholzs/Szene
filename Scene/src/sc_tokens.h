// Copyright (c) 2002 Steffen Buchholz

#ifndef _Scenetok_H_
#define _Scenetok_H_

/*
** Aufzählung der Tokenwerte (scene.dtd)
*/
enum sc_Tokens {
  // sorted below this line
  TOK_CAMERA,
  TOK_LIGHT,
  TOK_OBJECT,
  TOK_PL_LIGHT_NONE,
  TOK_PL_LIGHT_POINT,
  TOK_PL_LIGHT_POINT_ANGLE,
  TOK_PL_LIGHT_POINT_DISTANCE,
  TOK_PL_LIGHT_VECTOR,
  TOK_PL_SHADE_FLAT,
  TOK_PL_SHADE_FLAT_DISTANCE,
  TOK_PL_SHADE_GOURAUD,
  TOK_PL_SHADE_GOURAUD_DISTANCE,
  TOK_PL_SHADE_NONE,
  TOK_PL_TEXENV_ADD,
  TOK_PL_TEXENV_AVG,
  TOK_PL_TEXENV_ENVMINUSTEX,
  TOK_PL_TEXENV_MAX,
  TOK_PL_TEXENV_MIN,
  TOK_PL_TEXENV_MUL,
  TOK_PL_TEXENV_TEXMINUSENV,
  TOK_ambient0,
  TOK_ambient1,
  TOK_ambient2,
  TOK_animations,
  TOK_backfacecull,
  TOK_background,
  TOK_box,
  TOK_camera,
  TOK_cameras,
  TOK_cap,
  TOK_capbottom,
  TOK_captop,
  TOK_cob,
  TOK_color,
  TOK_cone,
  TOK_cylinder,
  TOK_d,
  TOK_diffuse0,
  TOK_diffuse1,
  TOK_diffuse2,
  TOK_divh,
  TOK_divr,
  TOK_duration,
  TOK_environment,
  TOK_envscaling,
  TOK_fadedist,
  TOK_falloff,
  TOK_flipnormals,
  TOK_fov,
  TOK_global,
  TOK_h,
  TOK_id,
  TOK_intensity,
  TOK_jaw,
  TOK_light,
  TOK_lights,
  TOK_material,
  TOK_materials,
  TOK_mover,
  TOK_no,
  TOK_numgradients,
  TOK_o3ds,
  TOK_obj,
  TOK_objects,
  TOK_optimize,
  TOK_pan,
  TOK_perspectivecorrect,
  TOK_pitch,
  TOK_plane,
  TOK_point,
  TOK_r,
  TOK_r1,
  TOK_r2,
  TOK_relative,
  TOK_repeat,
  TOK_res,
  TOK_rescale,
  TOK_roll,
  TOK_rotate,
  TOK_scale,
  TOK_scene,
  TOK_shadetype,
  TOK_shininess,
  TOK_sort,
  TOK_specular0,
  TOK_specular1,
  TOK_specular2,
  TOK_sphere,
  TOK_src,
  TOK_target,
  TOK_texenvmode,
  TOK_texscaling,
  TOK_texture,
  TOK_textures,
  TOK_torus,
  TOK_transformations,
  TOK_translate,
  TOK_transparent,
  TOK_type,
  TOK_w,
  TOK_x,
  TOK_xa,
  TOK_xp,
  TOK_y,
  TOK_ya,
  TOK_yes,
  TOK_yp,
  TOK_z,
  TOK_za,
  TOK_zp,
  // sorted above this line
  TOK_UNKNOWN /* no token */
};

/*
** Schlüssel-/Tokenwert-Typ. 
*/
extern "C" struct sc_TokenPair {
  const char *key;
  enum sc_Tokens val;
};

/*
** Tabelle mit Schlüssel-/Tokenwerten. Mittels bsearch kann diese Tabelle 
** durchsucht werden.
*/
extern sc_TokenPair tokenMap[];

// Anzahl der Tokens in tokenMap
extern unsigned int tokenMapSize;


/*
** Sucht nach einem Schlüssel in der Tokentabelle
** 
** Parameter:
**		key : Suchschlüssel
** Returns:
**		Pointer auf den gefundenen Eintrag; oder NULL
*/
sc_TokenPair *
sc_search(const char *name);
#endif


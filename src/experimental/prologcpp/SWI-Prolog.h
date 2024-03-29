/*  $Id$

    Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        wielemak@science.uva.nl
    WWW:           http://www.swi-prolog.org
    Copyright (C): 1985-2006, University of Amsterdam

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _FLI_H_INCLUDED
#define _FLI_H_INCLUDED

#ifndef __SWI_PROLOG__			/* use this to switch on Prolog dialect */
#define __SWI_PROLOG__			/* normally defined by the plld compiler driver */
#endif

#if defined(_MSC_VER) && !defined(__WINDOWS__)
#define __WINDOWS__ 1
#endif

#include <stdarg.h>
#include <stdlib.h>			/* get size_t */
#include <stddef.h>
#ifdef __WINDOWS__
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#if (_MSC_VER < 1300)
typedef long intptr_t;
typedef unsigned long uintptr_t;
#endif
#else
#include <inttypes.h>			/* more portable than stdint.h */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
This interface has been changed considerable  between version 2.1.14 and
2.5.0. You may get most old code to work using

	#define PL_OLD_INTERFACE

before loading this file.  See end of this file.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* PLVERSION: 10000 * <Major> + 100 * <Minor> + <Patch> */

#ifndef PLVERSION
#define PLVERSION 50659
#endif

		 /*******************************
		 *	       EXPORT		*
		 *******************************/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Traditional and ELF-based Unix systems  don't   need  all this, but COFF
based systems need  to  import  and   export  symbols  explicitely  from
executables and shared objects (DLL). On some systems (e.g. AIX) this is
achieved using import/export files, on Windows   this  is achieved using
special  declarations  on  exported  symbols.  So,  a  symbol  is  local
(static), shared between the objects building   an executable or DLL (no
special declaration) or exported from the executable or DLL.

Both using native Microsoft MSVC as well   as recent Cygwin (tested 1.1)
compilers support __declspec(...) for exporting symbols.

As SWI-Prolog.h can be included seperately or together with this file we
duplicated this stuff.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef _PL_EXPORT_DONE
#define _PL_EXPORT_DONE

#if (defined(_MSC_VER) || defined(__CYGWIN__)) && !defined(__LCC__)
#define HAVE_DECLSPEC
#endif

#ifdef HAVE_DECLSPEC
# ifdef PL_KERNEL
#define PL_EXPORT(type)		__declspec(dllexport) type
#define PL_EXPORT_DATA(type)	__declspec(dllexport) type
#define install_t	 	void
# else
#  ifdef __BORLANDC__
#define PL_EXPORT(type)	 	type _stdcall
#define PL_EXPORT_DATA(type)	extern type
#  else
#define PL_EXPORT(type)	 	extern type
#define PL_EXPORT_DATA(type)	__declspec(dllimport) type
#  endif
#define install_t	 	__declspec(dllexport) void
# endif
#else /*HAVE_DECLSPEC*/
#define PL_EXPORT(type)	 	extern type
#define PL_EXPORT_DATA(type)	extern type
#define install_t	 	void
#endif /*HAVE_DECLSPEC*/
#endif /*_PL_EXPORT_DONE*/


		 /*******************************
		 *	       TYPES		*
		 *******************************/

#ifdef _PL_INCLUDE_H
typedef Module		module_t;	/* a module */
typedef Procedure	predicate_t;	/* a predicate handle */
typedef Record		record_t;	/* handle to a recorded term */
typedef struct PL_local_data *PL_engine_t; /* handle to a engine */
#else
typedef	uintptr_t	atom_t;		/* Prolog atom */
typedef void *		module_t;	/* Prolog module */
typedef void *		predicate_t;	/* Prolog procedure */
typedef void *		record_t;	/* Prolog recorded term */
typedef uintptr_t	term_t;		/* opaque term handle */
typedef uintptr_t	qid_t;		/* opaque query handle */
typedef uintptr_t	PL_fid_t;	/* opaque foreign context handle */
typedef void *		control_t;	/* non-deterministic control arg */
typedef void *		PL_engine_t;	/* opaque engine handle */
#endif
typedef uintptr_t	functor_t;	/* Name/arity pair */
typedef uintptr_t	PL_atomic_t;	/* same a word */
typedef uintptr_t	foreign_t;	/* return type of foreign functions */
typedef wchar_t	        pl_wchar_t;	/* Prolog wide character */
#ifdef __cplusplus
typedef void * 		pl_function_t;	/* can only pass function as void * */
#else
typedef foreign_t	(*pl_function_t)(); /* foreign language functions */
#endif

#ifndef NORETURN
#define NORETURN
#endif

#define fid_t PL_fid_t			/* avoid AIX name-clash */

					/* values for PL_get_term_value() */
typedef union
{ int64_t i;				/* PL_INTEGER */
  double f;				/* PL_FLOAT */
  char * s;				/* PL_STRING */
  atom_t a;				/* PL_ATOM */
  struct				/* PL_TERM */
  { atom_t name;
    int    arity;
  } t;
} term_value_t;

#ifndef TRUE
#define TRUE	(1)
#define FALSE	(0)
#endif

		 /*******************************
		 *      TERM-TYPE CONSTANTS	*
		 *******************************/
					/* PL_unify_term() arguments */
#define	PL_VARIABLE	 (1)		/* nothing */
#define PL_ATOM		 (2)		/* const char * */
#define PL_INTEGER	 (3)		/* int */
#define PL_FLOAT	 (4)		/* double */
#define PL_STRING	 (5)		/* const char * */
#define PL_TERM		 (6)

					/* PL_unify_term() */
#define PL_FUNCTOR	 (10)		/* functor_t, arg ... */
#define PL_LIST		 (11)		/* length, arg ... */
#define PL_CHARS	 (12)		/* const char * */
#define PL_POINTER	 (13)		/* void * */
					/* PlArg::PlArg(text, type) */
#define PL_CODE_LIST	 (14)		/* [ascii...] */
#define PL_CHAR_LIST	 (15)		/* [h,e,l,l,o] */
#define PL_BOOL		 (16)		/* PL_set_feature() */
#define PL_FUNCTOR_CHARS (17)		/* PL_unify_term() */
#define _PL_PREDICATE_INDICATOR (18)	/* predicate_t (Procedure) */
#define PL_SHORT	 (19)		/* short */
#define PL_INT		 (20)		/* int */
#define PL_LONG		 (21)		/* long */
#define PL_DOUBLE	 (22)		/* double */
#define PL_NCHARS	 (23)		/* size_t, const char * */
#define PL_UTF8_CHARS	 (24)		/* const char * */
#define PL_UTF8_STRING	 (25)		/* const char * */
#define PL_INT64	 (26)		/* int64_t */
#define PL_NUTF8_CHARS	 (27)		/* size_t, const char * */
#define PL_NUTF8_CODES	 (29)		/* size_t, const char * */
#define PL_NUTF8_STRING	 (30)		/* size_t, const char * */
#define PL_NWCHARS	 (31)		/* size_t, const wchar_t * */
#define PL_NWCODES	 (32)		/* size_t, const wchar_t * */
#define PL_NWSTRING	 (33)		/* size_t, const wchar_t * */
#define PL_MBCHARS	 (34)		/* const char * */
#define PL_MBCODES	 (35)		/* const char * */
#define PL_MBSTRING	 (36)		/* const char * */
#define PL_INTPTR	 (37)		/* intptr_t */


		/********************************
		*    DETERMINISTIC CALL/RETURN  *
		*********************************/

#define	PL_succeed	return TRUE	/* succeed deterministically */
#define PL_fail		return FALSE	/* fail */


		/********************************
		* NON-DETERMINISTIC CALL/RETURN *
		*********************************/

/*  Note 1: Non-deterministic foreign functions may also use the deterministic
    return methods PL_succeed and PL_fail.

    Note 2: The argument to PL_retry is a 30 bits signed integer (intptr_t).
*/

#define PL_FIRST_CALL		(0)
#define PL_CUTTED		(1)
#define PL_REDO			(2)

#define PL_retry(n)		return _PL_retry(n)
#define PL_retry_address(a)	return _PL_retry_address(a)

PL_EXPORT(foreign_t)	_PL_retry(intptr_t);
PL_EXPORT(foreign_t)	_PL_retry_address(void *);
PL_EXPORT(int)	 	PL_foreign_control(control_t);
PL_EXPORT(intptr_t)	 	PL_foreign_context(control_t);
PL_EXPORT(void *)	PL_foreign_context_address(control_t);


		/********************************
		*      REGISTERING FOREIGNS     *
		*********************************/

typedef struct PL_extension
{ const char   *predicate_name;		/* Name of the predicate */
  short		arity;			/* Arity of the predicate */
  pl_function_t	function;		/* Implementing functions */
  short		flags;			/* Or of PL_FA_... */
} PL_extension;

#define PL_FA_NOTRACE		(0x01)	/* foreign cannot be traced */
#define PL_FA_TRANSPARENT	(0x02)	/* foreign is module transparent */
#define PL_FA_NONDETERMINISTIC	(0x04)	/* foreign is non-deterministic */
#define PL_FA_VARARGS		(0x08)	/* call using t0, ac, ctx */
#define PL_FA_CREF		(0x10)	/* Internal: has clause-reference */
#define PL_FA_ISO		(0x20)	/* Internal: ISO core predicate */

extern			PL_extension PL_extensions[]; /* not Win32! */
PL_EXPORT(void)		PL_register_extensions(const PL_extension *e);
PL_EXPORT(void)		PL_register_extensions_in_module(const char *module, const PL_extension *e);
PL_EXPORT(int)		PL_register_foreign(const char *name, int arity,
					    pl_function_t func, int flags);
PL_EXPORT(int)		PL_register_foreign_in_module(const char *module,
						      const char *name, int arity,
						      pl_function_t func, int flags);
PL_EXPORT(void)		PL_load_extensions(const PL_extension *e);


		 /*******************************
		 *	      LICENSE		*
		 *******************************/

void			PL_license(const char *license, const char *module);

		/********************************
		*            MODULES            *
		*********************************/

PL_EXPORT(module_t)	PL_context(void);
PL_EXPORT(atom_t)	PL_module_name(module_t module);
PL_EXPORT(module_t)	PL_new_module(atom_t name);
PL_EXPORT(int)		PL_strip_module(term_t in, module_t *m, term_t out);


		 /*******************************
		 *	     CALL-BACK		*
		 *******************************/

#ifdef PL_KERNEL
#define PL_Q_DEBUG		0x01	/* = TRUE for backward compatibility */
#endif
#define PL_Q_NORMAL		0x02	/* normal usage */
#define PL_Q_NODEBUG		0x04	/* use this one */
#define PL_Q_CATCH_EXCEPTION	0x08	/* handle exceptions in C */
#define PL_Q_PASS_EXCEPTION	0x10	/* pass to parent environment */
#ifdef PL_KERNEL
#define PL_Q_DETERMINISTIC	0x20	/* call was deterministic */
#endif

			/* Foreign context frames */
PL_EXPORT(fid_t)	PL_open_foreign_frame(void);
PL_EXPORT(void)		PL_rewind_foreign_frame(fid_t cid);
PL_EXPORT(void)		PL_close_foreign_frame(fid_t cid);
PL_EXPORT(void)		PL_discard_foreign_frame(fid_t cid);

			/* Finding predicates */
PL_EXPORT(predicate_t)	PL_pred(functor_t f, module_t m);
PL_EXPORT(predicate_t)	PL_predicate(const char *name, int arity,
				     const char* module);
PL_EXPORT(int)		PL_predicate_info(predicate_t pred,
					  atom_t *name, int *arity,
					  module_t *module);

			/* Call-back */
PL_EXPORT(qid_t)	PL_open_query(module_t m, int flags,
				      predicate_t pred, term_t t0);
PL_EXPORT(int)		PL_next_solution(qid_t qid);
PL_EXPORT(void)		PL_close_query(qid_t qid);
PL_EXPORT(void)		PL_cut_query(qid_t qid);

			/* Simplified (but less flexible) call-back */
PL_EXPORT(int)		PL_call(term_t t, module_t m);
PL_EXPORT(int)		PL_call_predicate(module_t m, int debug,
					  predicate_t pred, term_t t0);
			/* Handling exceptions */
PL_EXPORT(term_t)	PL_exception(qid_t qid);
PL_EXPORT(int)		PL_raise_exception(term_t exception);
PL_EXPORT(int)		PL_throw(term_t exception);


		 /*******************************
		 *        TERM-REFERENCES	*
		 *******************************/

			/* Creating and destroying term-refs */
PL_EXPORT(term_t)	PL_new_term_refs(int n);
PL_EXPORT(term_t)	PL_new_term_ref(void);
PL_EXPORT(term_t)	PL_copy_term_ref(term_t from);
PL_EXPORT(void)		PL_reset_term_refs(term_t r);

			/* Constants */
PL_EXPORT(atom_t)	PL_new_atom(const char *s);
PL_EXPORT(atom_t)	PL_new_atom_nchars(size_t len, const char *s);
PL_EXPORT(atom_t)	PL_new_atom_wchars(size_t len, const wchar_t *s);
PL_EXPORT(const char *)	PL_atom_chars(atom_t a);
PL_EXPORT(const char *) PL_atom_nchars(atom_t a, size_t *len);
PL_EXPORT(const wchar_t *) PL_atom_wchars(atom_t a, size_t *len);
#ifndef O_DEBUG_ATOMGC
PL_EXPORT(void)		PL_register_atom(atom_t a);
PL_EXPORT(void)		PL_unregister_atom(atom_t a);
#endif
PL_EXPORT(functor_t)	PL_new_functor(atom_t f, int a);
PL_EXPORT(atom_t)	PL_functor_name(functor_t f);
PL_EXPORT(int)		PL_functor_arity(functor_t f);

			/* Get C-values from Prolog terms */
PL_EXPORT(int)		PL_get_atom(term_t t, atom_t *a);
PL_EXPORT(int)		PL_get_bool(term_t t, int *value);
PL_EXPORT(int)		PL_get_atom_chars(term_t t, char **a);
#define PL_get_string_chars(t, s, l) PL_get_string(t,s,l)
					/* PL_get_string() is depricated */
PL_EXPORT(int)		PL_get_string(term_t t, char **s, size_t *len);
PL_EXPORT(int)		PL_get_chars(term_t t, char **s, unsigned int flags);
PL_EXPORT(int)		PL_get_list_chars(term_t l, char **s,
					  unsigned int flags);
PL_EXPORT(int)		PL_get_atom_nchars(term_t t, size_t *len, char **a);
PL_EXPORT(int)		PL_get_list_nchars(term_t l,
					   size_t *len, char **s,
					   unsigned int flags);
PL_EXPORT(int)		PL_get_nchars(term_t t,
				      size_t *len, char **s,
				      unsigned int flags);
PL_EXPORT(int)		PL_get_integer(term_t t, int *i);
PL_EXPORT(int)		PL_get_long(term_t t, long *i);
PL_EXPORT(int)		PL_get_pointer(term_t t, void **ptr);
PL_EXPORT(int)		PL_get_float(term_t t, double *f);
PL_EXPORT(int)		PL_get_functor(term_t t, functor_t *f);
PL_EXPORT(int)		PL_get_name_arity(term_t t, atom_t *name, int *arity);
PL_EXPORT(int)		PL_get_module(term_t t, module_t *module);
PL_EXPORT(int)		PL_get_arg(int index, term_t t, term_t a);
PL_EXPORT(int)		PL_get_list(term_t l, term_t h, term_t t);
PL_EXPORT(int)		PL_get_head(term_t l, term_t h);
PL_EXPORT(int)		PL_get_tail(term_t l, term_t t);
PL_EXPORT(int)		PL_get_nil(term_t l);
PL_EXPORT(int)		PL_get_term_value(term_t t, term_value_t *v);
PL_EXPORT(char *)	PL_quote(int chr, const char *data);

			/* Verify types */
PL_EXPORT(int)		PL_term_type(term_t t);
PL_EXPORT(int)		PL_is_variable(term_t t);
PL_EXPORT(int)		PL_is_ground(term_t t);
PL_EXPORT(int)		PL_is_atom(term_t t);
PL_EXPORT(int)		PL_is_integer(term_t t);
PL_EXPORT(int)		PL_is_string(term_t t);
PL_EXPORT(int)		PL_is_float(term_t t);
PL_EXPORT(int)		PL_is_rational(term_t t);
PL_EXPORT(int)		PL_is_compound(term_t t);
PL_EXPORT(int)		PL_is_callable(term_t t);
PL_EXPORT(int)		PL_is_functor(term_t t, functor_t f);
PL_EXPORT(int)		PL_is_list(term_t t);
PL_EXPORT(int)		PL_is_atomic(term_t t);
PL_EXPORT(int)		PL_is_number(term_t t);
PL_EXPORT(int)		PL_is_acyclic(term_t t);

			/* Assign to term-references */
PL_EXPORT(void)		PL_put_variable(term_t t);
PL_EXPORT(void)		PL_put_atom(term_t t, atom_t a);
PL_EXPORT(void)		PL_put_atom_chars(term_t t, const char *chars);
PL_EXPORT(void)		PL_put_string_chars(term_t t, const char *chars);
PL_EXPORT(void)		PL_put_list_chars(term_t t, const char *chars);
PL_EXPORT(void)		PL_put_list_codes(term_t t, const char *chars);
PL_EXPORT(void)		PL_put_atom_nchars(term_t t, size_t l, const char *chars);
PL_EXPORT(void)		PL_put_string_nchars(term_t t, size_t len, const char *chars);
PL_EXPORT(void)		PL_put_list_nchars(term_t t, size_t l, const char *chars);
PL_EXPORT(void)		PL_put_list_ncodes(term_t t, size_t l, const char *chars);
PL_EXPORT(void)		PL_put_integer(term_t t, long i);
PL_EXPORT(void)		PL_put_pointer(term_t t, void *ptr);
PL_EXPORT(void)		PL_put_float(term_t t, double f);
PL_EXPORT(void)		PL_put_functor(term_t t, functor_t functor);
PL_EXPORT(void)		PL_put_list(term_t l);
PL_EXPORT(void)		PL_put_nil(term_t l);
PL_EXPORT(void)		PL_put_term(term_t t1, term_t t2);

			/* construct a functor or list-cell */
PL_EXPORT(void)		PL_cons_functor(term_t h, functor_t f, ...);
PL_EXPORT(void)		PL_cons_functor_v(term_t h, functor_t fd, term_t a0);
PL_EXPORT(void)		PL_cons_list(term_t l, term_t h, term_t t);

			/* Unify term-references */
PL_EXPORT(int)		PL_unify(term_t t1, term_t t2);
PL_EXPORT(int)		PL_unify_atom(term_t t, atom_t a);
PL_EXPORT(int)		PL_unify_atom_chars(term_t t, const char *chars);
PL_EXPORT(int)		PL_unify_list_chars(term_t t, const char *chars);
PL_EXPORT(int)		PL_unify_list_codes(term_t t, const char *chars);
PL_EXPORT(int)		PL_unify_string_chars(term_t t, const char *chars);
PL_EXPORT(int)		PL_unify_atom_nchars(term_t t, size_t l, const char *s);
PL_EXPORT(int)		PL_unify_list_ncodes(term_t t, size_t l, const char *s);
PL_EXPORT(int)		PL_unify_list_nchars(term_t t, size_t l, const char *s);
PL_EXPORT(int)		PL_unify_string_nchars(term_t t,
					       size_t len,
					       const char *chars);
PL_EXPORT(int)		PL_unify_integer(term_t t, intptr_t n);
PL_EXPORT(int)		PL_unify_float(term_t t, double f);
PL_EXPORT(int)		PL_unify_pointer(term_t t, void *ptr);
PL_EXPORT(int)		PL_unify_functor(term_t t, functor_t f);
PL_EXPORT(int)		PL_unify_list(term_t l, term_t h, term_t t);
PL_EXPORT(int)		PL_unify_nil(term_t l);
PL_EXPORT(int)		PL_unify_arg(int index, term_t t, term_t a);
PL_EXPORT(int)		PL_unify_term(term_t t, ...);
PL_EXPORT(int)		PL_unify_chars(term_t t, int flags,
				       size_t len, const char *s);


		 /*******************************
		 *    WIDE CHARACTER VERSIONS	*
		 *******************************/

PL_EXPORT(int)		PL_unify_wchars(term_t t, int type,
					size_t len, const pl_wchar_t *s);
PL_EXPORT(int)		PL_unify_wchars_diff(term_t t, term_t tail, int type,
					size_t len, const pl_wchar_t *s);
PL_EXPORT(int)		PL_get_wchars(term_t l,
				      size_t *length, pl_wchar_t **s,
				      unsigned flags);
PL_EXPORT(size_t)	PL_utf8_strlen(const char *s, size_t len);


		 /*******************************
		 *	   WIDE INTEGERS	*
		 *******************************/


PL_EXPORT(int)		PL_get_int64(term_t t, int64_t *i);
PL_EXPORT(int)		PL_unify_int64(term_t t, int64_t value);
PL_EXPORT(void)		PL_put_int64(term_t t, int64_t i);


		 /*******************************
		 *     ATTRIBUTED VARIABLES	*
		 *******************************/

PL_EXPORT(int)		PL_is_attvar(term_t t);
PL_EXPORT(int)		PL_get_attr(term_t v, term_t a);


		 /*******************************
		 *	       BLOBS		*
		 *******************************/

#define PL_BLOB_MAGIC_B	0x75293a00	/* Magic to validate a blob-type */
#define PL_BLOB_VERSION 1		/* Current version */
#define PL_BLOB_MAGIC	(PL_BLOB_MAGIC_B|PL_BLOB_VERSION)

#define PL_BLOB_UNIQUE	0x01		/* Blob content is unique */
#define PL_BLOB_TEXT	0x02		/* blob contains text */
#define PL_BLOB_NOCOPY	0x04		/* do not copy the data */
#define PL_BLOB_WCHAR	0x08		/* wide character string */

typedef struct PL_blob_t
{ uintptr_t		magic;		/* PL_BLOB_MAGIC */
  uintptr_t		flags;		/* PL_BLOB_* */
  char *		name;		/* name of the type */
  int			(*release)(atom_t a);
  int			(*compare)(atom_t a, atom_t b);
#ifdef SIO_MAGIC
  int			(*write)(IOSTREAM *s, atom_t a, int flags);
#else
  int			(*write)(void *s, atom_t a, int flags);
#endif
  void			(*acquire)(atom_t a);
#ifdef SIO_MAGIC
  int			(*save)(atom_t a, IOSTREAM *s);
  atom_t		(*load)(IOSTREAM *s);
#else
  int			(*save)(atom_t a, void*);
  atom_t		(*load)(void *s);
#endif
					/* private */
  void *		reserved[10];	/* for future extension */
  int			registered;	/* Already registered? */
  int			rank;		/* Rank for ordering atoms */
  struct PL_blob_t *    next;		/* next in registered type-chain */
  atom_t		atom_name;	/* Name as atom */
} PL_blob_t;

PL_EXPORT(int)		PL_is_blob(term_t t, PL_blob_t **type);
PL_EXPORT(int)		PL_unify_blob(term_t t, void *blob, size_t len,
				      PL_blob_t *type);
PL_EXPORT(int)		PL_put_blob(term_t t, void *blob, size_t len,
				    PL_blob_t *type);
PL_EXPORT(int)		PL_get_blob(term_t t, void **blob, size_t *len,
				    PL_blob_t **type);

PL_EXPORT(void*)	PL_blob_data(atom_t a,
				     size_t *len,
				     struct PL_blob_t **type);

PL_EXPORT(void)		PL_register_blob_type(PL_blob_t *type);
PL_EXPORT(PL_blob_t*)	PL_find_blob_type(const char* name);
PL_EXPORT(int)		PL_unregister_blob_type(PL_blob_t *type);


#ifdef __GNU_MP__

		 /*******************************
		 *	       GMP		*
		 *******************************/

PL_EXPORT(int)	PL_get_mpz(term_t t, mpz_t mpz);
PL_EXPORT(int)	PL_get_mpq(term_t t,  mpq_t mpq);
PL_EXPORT(int)	PL_unify_mpz(term_t t, mpz_t mpz);
PL_EXPORT(int)	PL_unify_mpq(term_t t, mpq_t mpq);

#endif /*__GNU_MP__*/

		 /*******************************
		 *	  FILENAME SUPPORT	*
		 *******************************/

#define PL_FILE_ABSOLUTE	0x01	/* return absolute path */
#define PL_FILE_OSPATH		0x02	/* return path in OS notation */
#define PL_FILE_SEARCH		0x04	/* use file_search_path */
#define PL_FILE_EXIST		0x08	/* demand file to exist */
#define PL_FILE_READ		0x10	/* demand read-access */
#define PL_FILE_WRITE		0x20	/* demand write-access */
#define PL_FILE_EXECUTE		0x40	/* demand execute-access */
#define PL_FILE_NOERRORS	0x80	/* do not raise exceptions */

PL_EXPORT(int)		PL_get_file_name(term_t n, char **name, int flags);
PL_EXPORT(void)		PL_changed_cwd(void); /* foreign code changed CWD */
PL_EXPORT(const char *) PL_cwd(void);


		 /*******************************
		 *   QUINTUS WRAPPER SUPPORT	*
		 *******************************/

PL_EXPORT(int)		PL_cvt_i_integer(term_t p, long *c);
PL_EXPORT(int)		PL_cvt_i_float(term_t p, double *c);
PL_EXPORT(int)		PL_cvt_i_single(term_t p, float *c);
PL_EXPORT(int)		PL_cvt_i_string(term_t p, char **c);
PL_EXPORT(int)		PL_cvt_i_atom(term_t p, atom_t *c);
PL_EXPORT(int)		PL_cvt_o_integer(intptr_t c, term_t p);
PL_EXPORT(int)		PL_cvt_o_float(double c, term_t p);
PL_EXPORT(int)		PL_cvt_o_single(float c, term_t p);
PL_EXPORT(int)		PL_cvt_o_string(const char *c, term_t p);
PL_EXPORT(int)		PL_cvt_o_atom(atom_t c, term_t p);


		 /*******************************
		 *	     COMPARE		*
		 *******************************/

PL_EXPORT(int)		PL_compare(term_t t1, term_t t2);
PL_EXPORT(int)		PL_same_compound(term_t t1, term_t t2);

		 /*******************************
		 *	     MESSAGES		*
		 *******************************/

PL_EXPORT(int)		PL_warning(const char *fmt, ...);
PL_EXPORT(void)		PL_fatal_error(const char *fmt, ...);

		 /*******************************
		 *      RECORDED DATABASE	*
		 *******************************/

PL_EXPORT(record_t)	PL_record(term_t term);
PL_EXPORT(void)		PL_recorded(record_t record, term_t term);
PL_EXPORT(void)		PL_erase(record_t record);

PL_EXPORT(char *)	PL_record_external(term_t t, size_t *size);
PL_EXPORT(int)		PL_recorded_external(const char *rec, term_t term);
PL_EXPORT(int)		PL_erase_external(char *rec);

		 /*******************************
		 *	      FEATURES		*
		 *******************************/

PL_EXPORT(int)		PL_set_feature(const char *name, int type, ...);

		 /*******************************
		 *	INTERNAL FUNCTIONS	*
		 *******************************/

PL_EXPORT(PL_atomic_t)	_PL_get_atomic(term_t t);
PL_EXPORT(void)		_PL_put_atomic(term_t t, PL_atomic_t a);
PL_EXPORT(int)		_PL_unify_atomic(term_t t, PL_atomic_t a);
PL_EXPORT(void)		_PL_copy_atomic(term_t t, PL_atomic_t a);
PL_EXPORT(void)		_PL_get_arg(int index, term_t t, term_t a);


		 /*******************************
		 *	    CHAR BUFFERS	*
		 *******************************/

#define CVT_ATOM	0x0001
#define CVT_STRING	0x0002
#define CVT_LIST	0x0004
#define CVT_INTEGER	0x0008
#define CVT_FLOAT	0x0010
#define CVT_VARIABLE	0x0020
#define CVT_NUMBER	(CVT_INTEGER|CVT_FLOAT)
#define CVT_ATOMIC	(CVT_NUMBER|CVT_ATOM|CVT_STRING)
#define CVT_WRITE	0x0040		/* as of version 3.2.10 */
#define CVT_ALL		(CVT_ATOMIC|CVT_LIST)
#define CVT_MASK	0x00ff

#define BUF_DISCARDABLE	0x0000
#define BUF_RING	0x0100
#define BUF_MALLOC	0x0200

#define CVT_EXCEPTION	0x10000		/* throw exception on error */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Output   representation   for   PL_get_chars()     and    friends.   The
prepresentation type REP_FN is for   PL_get_file_name()  and friends. On
Windows we use UTF-8 which is translated   by the `XOS' layer to Windows
UNICODE file functions.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#define REP_ISO_LATIN_1 0x0000		/* output representation */
#define REP_UTF8 	0x1000
#define REP_MB		0x2000
#ifdef __WINDOWS__
#define REP_FN		REP_UTF8
#else
#define REP_FN		REP_MB
#endif

#define PL_DIFF_LIST	0x20000		/* PL_unify_chars() */


#ifdef SIO_MAGIC			/* defined from <SWI-Stream.h> */
		 /*******************************
		 *	  STREAM SUPPORT	*
		 *******************************/

					/* Make IOSTREAM known to Prolog */
PL_EXPORT(int)  	PL_open_stream(term_t t, IOSTREAM *s); /* compat */
PL_EXPORT(int)  	PL_unify_stream(term_t t, IOSTREAM *s);
PL_EXPORT(int)  	PL_get_stream_handle(term_t t, IOSTREAM **s);
PL_EXPORT(int) 		PL_release_stream(IOSTREAM *s);
PL_EXPORT(IOSTREAM *)	PL_open_resource(module_t m,
					 const char *name,
					 const char *rc_class,
					 const char *mode);

PL_EXPORT(IOSTREAM *)*_PL_streams(void);	/* base of streams */
#ifndef PL_KERNEL
#define Suser_input  (_PL_streams()[0])
#define Suser_output (_PL_streams()[1])
#define Suser_error  (_PL_streams()[2])
#endif

#define PL_WRT_QUOTED		0x01	/* quote atoms */
#define PL_WRT_IGNOREOPS	0x02	/* ignore list/operators */
#define PL_WRT_NUMBERVARS	0x04	/* print $VAR(N) as a variable */
#define PL_WRT_PORTRAY		0x08	/* call portray */
#define PL_WRT_CHARESCAPES	0x10	/* Output ISO escape sequences */
#define PL_WRT_BACKQUOTED_STRING 0x20	/* Write strings as `...` */
					/* Write attributed variables */
#define PL_WRT_ATTVAR_IGNORE	0x040	/* Default: just write the var */
#define PL_WRT_ATTVAR_DOTS	0x080	/* Write as Var{...} */
#define PL_WRT_ATTVAR_WRITE	0x100	/* Write as Var{Attributes} */
#define PL_WRT_ATTVAR_PORTRAY	0x200	/* Use Module:portray_attrs/2 */
#define PL_WRT_ATTVAR_MASK \
	(PL_WRT_ATTVAR_IGNORE | \
	 PL_WRT_ATTVAR_DOTS | \
	 PL_WRT_ATTVAR_WRITE | \
	 PL_WRT_ATTVAR_PORTRAY)

PL_EXPORT(int) PL_write_term(IOSTREAM *s,
			      term_t term,
			      int precedence,
			      int flags);

					/* PL_ttymode() results */
#define PL_NOTTY	0		/* -tty in effect */
#define PL_RAWTTY	1		/* get_single_char/1 */
#define PL_COOKEDTTY	2		/* normal input */

PL_EXPORT(int)		PL_ttymode(IOSTREAM *s);

#endif /*SIO_MAGIC*/

PL_EXPORT(int) PL_chars_to_term(const char *chars,
				 term_t term);


		 /*******************************
		 *	    EMBEDDING		*
		 *******************************/

PL_EXPORT(int)		PL_initialise(int argc, char **argv);
PL_EXPORT(int)		PL_is_initialised(int *argc, char ***argv);
#ifdef __CYGWIN__
PL_EXPORT(void)		PL_install_readline(void);
#else
install_t		PL_install_readline(void);
#endif
PL_EXPORT(int)		PL_toplevel(void);
PL_EXPORT(int)		PL_cleanup(int status);
PL_EXPORT(void)		PL_cleanup_fork();
PL_EXPORT(void)		PL_halt(int status) NORETURN;

		 /*******************************
		 *      INPUT/PROMPT/ETC	*
		 *******************************/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
NOTE: the functions in this section are   not  documented, as as yet not
adviced for public usage.  They  are   intended  to  provide an abstract
interface for the GNU readline  interface   as  defined in pl-rl.c. This
abstract interface is necessary to make an embeddable system without the
readline overhead.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
					/* PL_dispatch() modes */
#define PL_DISPATCH_NOWAIT    0		/* Dispatch only once */
#define PL_DISPATCH_WAIT      1		/* Dispatch till input available */
#define PL_DISPATCH_INSTALLED 2		/* dispatch function installed? */

PL_EXPORT(int)		PL_dispatch(int fd, int wait);
PL_EXPORT(void)		PL_add_to_protocol(const char *buf, size_t count);
PL_EXPORT(char *)	PL_prompt_string(int fd);
PL_EXPORT(void)		PL_write_prompt(int dowrite);
PL_EXPORT(void)		PL_prompt_next(int fd);
PL_EXPORT(char *)	PL_atom_generator(const char *prefix, int state);
PL_EXPORT(pl_wchar_t*)  PL_atom_generator_w(const pl_wchar_t *pref,
					    pl_wchar_t *buffer,
					    size_t buflen,
					    int state);
PL_EXPORT(void)		PL_clock_wait_ticks(intptr_t waited);


		 /*******************************
		 *	MEMORY ALLOCATION	*
		 *******************************/

PL_EXPORT(void *)	PL_malloc(size_t size);
PL_EXPORT(void *)	PL_realloc(void *mem, size_t size);
PL_EXPORT(void)		PL_free(void *mem);

		/********************************
		*             HOOKS		*
		********************************/

#define PL_DISPATCH_INPUT   0		/* There is input available */
#define PL_DISPATCH_TIMEOUT 1		/* Dispatch timeout */

typedef int  (*PL_dispatch_hook_t)(int fd);
typedef void (*PL_abort_hook_t)(void);
typedef void (*PL_initialise_hook_t)(int argc, char **argv);
typedef void (*PL_async_hook_t)(void);	/* Win32 only (O_ASYNC_HOOK) */
typedef int  (*PL_agc_hook_t)(atom_t a);

PL_EXPORT(PL_dispatch_hook_t) 	PL_dispatch_hook(PL_dispatch_hook_t);
PL_EXPORT(void)	       		PL_abort_hook(PL_abort_hook_t);
PL_EXPORT(void)	       		PL_initialise_hook(PL_initialise_hook_t);
PL_EXPORT(int)		      	PL_abort_unhook(PL_abort_hook_t);
PL_EXPORT(PL_async_hook_t)    	PL_async_hook(unsigned int, PL_async_hook_t);
PL_EXPORT(PL_agc_hook_t)      	PL_agc_hook(PL_agc_hook_t);


		/********************************
		*            SIGNALS            *
		*********************************/

#define PL_SIGSYNC	0x00010000	/* call handler synchronously */

PL_EXPORT(void) (*PL_signal(int sig, void (*func)(int)))(int);
PL_EXPORT(void) PL_interrupt(int sig);
PL_EXPORT(int)  PL_raise(int sig);
PL_EXPORT(int)  PL_handle_signals(void);
PL_EXPORT(int) 	PL_get_signum_ex(term_t sig, int *n);


		/********************************
		*      PROLOG ACTION/QUERY      *
		*********************************/

#define	PL_ACTION_TRACE		1	/* switch to trace mode */
#define PL_ACTION_DEBUG		2	/* switch to debug mode */
#define PL_ACTION_BACKTRACE	3	/* show a backtrace (stack dump) */
#define PL_ACTION_BREAK		4	/* create a break environment */
#define PL_ACTION_HALT		5	/* halt Prolog execution */
#define PL_ACTION_ABORT		6	/* generate a Prolog abort */
					/* 7: Obsolete PL_ACTION_SYMBOLFILE */
#define PL_ACTION_WRITE		8	/* write via Prolog i/o buffer */
#define PL_ACTION_FLUSH		9	/* Flush Prolog i/o buffer */
#define PL_ACTION_GUIAPP	10	/* Win32: set when this is a gui */
#define PL_ACTION_ATTACH_CONSOLE 11	/* MT: Attach a console */
#define PL_GMP_SET_ALLOC_FUNCTIONS 12	/* GMP: do not change allocation functions */

PL_EXPORT(int)	 PL_action(int, ...);	/* perform some action */
PL_EXPORT(void) PL_on_halt(void (*)(int, void *), void *);

		/********************************
		*         QUERY PROLOG          *
		*********************************/

#define PL_QUERY_ARGC		1	/* return main() argc */
#define PL_QUERY_ARGV		2	/* return main() argv */
					/* 3: Obsolete PL_QUERY_SYMBOLFILE */
					/* 4: Obsolete PL_QUERY_ORGSYMBOLFILE*/
#define PL_QUERY_GETC		5	/* Read character from terminal */
#define PL_QUERY_MAX_INTEGER	6	/* largest integer */
#define PL_QUERY_MIN_INTEGER	7	/* smallest integer */
#define PL_QUERY_MAX_TAGGED_INT	8	/* largest tagged integer */
#define PL_QUERY_MIN_TAGGED_INT	9	/* smallest tagged integer */
#define PL_QUERY_VERSION        10	/* 207006 = 2.7.6 */
#define PL_QUERY_MAX_THREADS	11	/* maximum thread count */
#define PL_QUERY_ENCODING	12	/* I/O encoding */
#define PL_QUERY_USER_CPU	13	/* User CPU in milliseconds */

PL_EXPORT(intptr_t)	PL_query(int);	/* get information from Prolog */


		 /*******************************
		 *	  PROLOG THREADS	*
		 *******************************/

typedef struct
{ long	    local_size;			/* Stack sizes (Kbytes) */
  long	    global_size;
  long	    trail_size;
  long	    argument_size;
  char *    alias;			/* alias name */
  int	  (*cancel)(int id);		/* cancel function */
  void *    reserved[5];		/* reserved for extensions */
} PL_thread_attr_t;


PL_EXPORT(int)	PL_thread_self(void);	/* Prolog thread id (-1 if none) */
PL_EXPORT(int)  PL_unify_thread_id(term_t t, int i);
PL_EXPORT(int)	PL_get_thread_id_ex(term_t t, int *idp);
PL_EXPORT(int)	PL_thread_attach_engine(PL_thread_attr_t *attr);
PL_EXPORT(int)	PL_thread_destroy_engine(void);
PL_EXPORT(int)	PL_thread_at_exit(void (*function)(void *),
				  void *closure,
				  int global);
#if defined(_WINDOWS_)			/* <windows.h> is included */
PL_EXPORT(int) PL_w32thread_raise(DWORD dwTid, int sig);
#endif

		 /*******************************
		 *	 ENGINES (MT-ONLY)	*
		 *******************************/

#define PL_ENGINE_MAIN	  ((PL_engine_t)0x1)
#define PL_ENGINE_CURRENT ((PL_engine_t)0x2)

#define PL_ENGINE_SET   0		/* engine set successfully */
#define PL_ENGINE_INVAL	2		/* engine doesn't exist */
#define PL_ENGINE_INUSE	3		/* engine is in use */

PL_EXPORT(PL_engine_t)	PL_create_engine(PL_thread_attr_t *attributes);
PL_EXPORT(int)		PL_set_engine(PL_engine_t engine, PL_engine_t *old);
PL_EXPORT(int)		PL_destroy_engine(PL_engine_t engine);


		 /*******************************
		 *	     PROFILER		*
		 *******************************/

typedef struct
{ int	(*unify)(term_t t, void *handle); 	/* implementation --> Prolog */
  int   (*get)(term_t t, void **handle);	/* Prolog --> implementation */
  void	(*activate)(int active);		/* (de)activate */
  intptr_t	magic;					/* PROFTYPE_MAGIC */
} PL_prof_type_t;

PL_EXPORT(int)		PL_register_profile_type(PL_prof_type_t *type);
PL_EXPORT(void*)	PL_prof_call(void *handle, PL_prof_type_t *type);
PL_EXPORT(void)		PL_prof_exit(void *node);


		 /*******************************
		 *	 WINDOWS MESSAGES	*
		 *******************************/

#ifdef _WINDOWS_			/* <windows.h> is included */
#define PL_MSG_EXCEPTION_RAISED -1
#define PL_MSG_IGNORED 0
#define PL_MSG_HANDLED 1

PL_EXPORT(LRESULT)	PL_win_message_proc(HWND hwnd,
					    UINT message,
					    WPARAM wParam,
					    LPARAM lParam);
#endif /*_WINDOWS_*/


		 /*******************************
		 *       FAST XPCE SUPPORT	*
		 *******************************/

typedef struct
{ int type;				/* PL_INTEGER or PL_ATOM */
  union
  { uintptr_t i;			/* integer reference value */
    atom_t	  a;			/* atom reference value */
  } value;
} xpceref_t;

PL_EXPORT(int)	_PL_get_xpce_reference(term_t t, xpceref_t *ref);
PL_EXPORT(int)  _PL_unify_xpce_reference(term_t t, xpceref_t *ref);
PL_EXPORT(void) _PL_put_xpce_reference_i(term_t t, uintptr_t r);
PL_EXPORT(void) _PL_put_xpce_reference_a(term_t t, atom_t name);

		 /*******************************
		 *        COMPATIBILITY		*
		 *******************************/

#ifdef PL_OLD_INTERFACE

typedef term_t term;
typedef PL_atomic_t atomic;

#ifndef _PL_INCLUDE_H
					/* renamed functions */
#define PL_is_var(t)		PL_is_variable(t)
#define PL_is_int(t)		PL_is_integer(t)
#define PL_is_term(t)		PL_is_compound(t)
#define PL_type(t)		PL_term_type(t)
#define PL_atom_value(a)	(char *)PL_atom_chars((atom_t)(a))
#define PL_predicate(f, m)	PL_pred(f, m)

					/* force undefined symbols */
					/* if PL_OLD_INTERFACE isn't set */
#define PL_strip_module(t, m)	_PL_strip_module(t, m)
#define PL_atomic(t)		_PL_atomic(t)
#define PL_float_value(t)	_PL_float_value(t)
#define PL_integer_value(t)	_PL_integer_value(t)
#define PL_string_value(t)	_PL_string_value(t)
#define PL_functor(t)		_PL_functor(t)
#define PL_arg(t, n)		_PL_arg(t, n)
#define PL_new_term()		_PL_new_term()
#define PL_new_integer(i)	_PL_new_integer(i)
#define PL_new_float(f)		_PL_new_float(f)
#define PL_new_string(s)	_PL_new_string(s)
#define PL_new_var()		_PL_new_var()
#define PL_term(a)		_PL_term(a)
#define PL_unify_atomic(t, a)	_PL_unify_atomic(t, (PL_atomic_t) (a))

typedef fid_t			bktrk_buf;
#define PL_mark(b)		(*(b) = PL_open_foreign_frame())
#define PL_bktrk(b)		PL_discard_foreign_frame(*(b))
#endif /*_PL_INCLUDE_H*/

		 /*******************************
		 *	     ANALYSIS		*
		 *******************************/

PL_EXPORT(PL_atomic_t)	_PL_atomic(term_t t);
PL_EXPORT(int64_t)	_PL_integer_value(PL_atomic_t t);
PL_EXPORT(double)	_PL_float_value(PL_atomic_t t);
PL_EXPORT(char *)	_PL_string_value(PL_atomic_t t);
PL_EXPORT(char *)	_PL_list_string_value(term_t t);
PL_EXPORT(functor_t)	_PL_functor(term_t t);
PL_EXPORT(term_t)	_PL_arg(term_t t, int n);


		 /*******************************
		 *	     CONSTRUCT		*
		 *******************************/

PL_EXPORT(term_t)	_PL_new_term(void);
PL_EXPORT(PL_atomic_t)	_PL_new_integer(intptr_t i);
PL_EXPORT(PL_atomic_t)	_PL_new_float(double f);
PL_EXPORT(PL_atomic_t)	_PL_new_string(const char *s);
PL_EXPORT(PL_atomic_t)	_PL_new_var(void);
PL_EXPORT(term_t)	_PL_term(PL_atomic_t a);

		 /*******************************
		 *	       UNIFY		*
		 *******************************/

PL_EXPORT(int)		_PL_unify_atomic(term_t t, PL_atomic_t a);

		 /*******************************
		 *	       MODULES		*
		 *******************************/

PL_EXPORT(term_t)	_PL_strip_module(term_t t, module_t *m);

#endif /*PL_OLD_INTERFACE*/

#ifdef __cplusplus
}
#endif

#endif /*_FLI_H_INCLUDED*/

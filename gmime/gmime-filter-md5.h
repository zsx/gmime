/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  Authors: Jeffrey Stedfast <fejj@ximian.com>
 *
 *  Copyright 2002 Ximian, Inc. (www.ximian.com)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Street #330, Boston, MA 02111-1307, USA.
 *
 */


#ifndef __GMIME_FILTER_MD5_H__
#define __GMIME_FILTER_MD5_H__

#ifdef __cplusplus
extern "C" {
#pragma }
#endif /* __cplusplus */

#include <gmime/md5-utils.h>
#include <gmime/gmime-filter.h>

#define GMIME_TYPE_FILTER_MD5            (g_mime_filter_md5_get_type ())
#define GMIME_FILTER_MD5(obj)            (GMIME_CHECK_CAST ((obj), GMIME_TYPE_FILTER_MD5, GMimeFilterMd5))
#define GMIME_FILTER_MD5_CLASS(klass)    (GMIME_CHECK_CLASS_CAST ((klass), GMIME_TYPE_FILTER_MD5, GMimeFilterMd5Class))
#define GMIME_IS_FILTER_MD5(obj)         (GMIME_CHECK_TYPE ((obj), GMIME_TYPE_FILTER_MD5))
#define GMIME_IS_FILTER_MD5_CLASS(klass) (GMIME_CHECK_CLASS_TYPE ((klass), GMIME_TYPE_FILTER_MD5))
#define GMIME_FILTER_MD5_GET_CLASS(obj)  (GMIME_CHECK_GET_CLASS ((obj), GMIME_TYPE_FILTER_MD5, GMimeFilterMd5Class))

typedef struct _GMimeFilterMd5 GMimeFilterMd5;
typedef struct _GMimeFilterMd5Class GMimeFilterMd5Class;

struct _GMimeFilterMd5 {
	GMimeFilter parent_object;
	
	MD5Context md5;
};

struct _GMimeFilterMd5Class {
	GMimeFilterClass parent_class;
	
};


GType g_mime_filter_md5_get_type (void);

GMimeFilter *g_mime_filter_md5_new (void);

void g_mime_filter_md5_get_digest (GMimeFilterMd5 *md5, unsigned char digest[16]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GMIME_FILTER_MD5_H__ */
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


#ifndef __GMIME_SESSION_H__
#define __GMIME_SESSION_H__

#ifdef __cplusplus
extern "C" {
#pragma }
#endif /* __cplusplus */

#include <glib.h>
#include <glib-object.h>

#include "gmime-type-utils.h"
#include "gmime-exception.h"

#define GMIME_TYPE_SESSION            (g_mime_session_get_type ())
#define GMIME_SESSION(obj)            (GMIME_CHECK_CAST ((obj), GMIME_TYPE_SESSION, GMimeSession))
#define GMIME_SESSION_CLASS(klass)    (GMIME_CHECK_CLASS_CAST ((klass), GMIME_TYPE_SESSION, GMimeSessionClass))
#define GMIME_IS_SESSION(obj)         (GMIME_CHECK_TYPE ((obj), GMIME_TYPE_SESSION))
#define GMIME_IS_SESSION_CLASS(klass) (GMIME_CHECK_CLASS_TYPE ((klass), GMIME_TYPE_SESSION))
#define GMIME_SESSION_GET_CLASS(obj)  (GMIME_CHECK_GET_CLASS ((obj), GMIME_TYPE_SESSION, GMimeSessionClass))

typedef struct _GMimeSession GMimeSession;
typedef struct _GMimeSessionClass GMimeSessionClass;

struct _GMimeSession {
	GObject parent_object;
	
};

struct _GMimeSessionClass {
	GObjectClass parent_class;
	
	gboolean (*is_online) (GMimeSession *session);
	
	char *   (*request_passwd) (GMimeSession *session, const char *prompt,
				    gboolean secret, const char *item,
				    GMimeException *ex);
	
	void     (*forget_passwd)  (GMimeSession *session, const char *item,
				    GMimeException *ex);
};


GType g_mime_session_get_type (void);


gboolean g_mime_session_is_online (GMimeSession *session);

char *g_mime_session_request_passwd (GMimeSession *session, const char *prompt,
				     gboolean secret, const char *item,
				     GMimeException *ex);

void g_mime_session_forget_passwd (GMimeSession *session, const char *item,
				   GMimeException *ex);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GMIME_SESSION_H__ */
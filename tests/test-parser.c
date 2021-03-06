/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*  GMime
 *  Copyright (C) 2000-2009 Jeffrey Stedfast
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
 *  Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include <gmime/gmime.h>

#ifndef G_OS_WIN32
#define ENABLE_ZENTIMER
#include "zentimer.h"
#endif

/*#define TEST_RAW_HEADER*/
#define TEST_PRESERVE_HEADERS
#define PRINT_MIME_STRUCT
/*#define TEST_WRITE_TO_STREAM*/

static void
print_depth (int depth)
{
	int i;
	
	for (i = 0; i < depth; i++)
		fprintf (stdout, "   ");
}

static void
print_mime_struct (GMimeObject *part, int depth)
{
	const GMimeContentType *type;
	GMimeMultipart *multipart;
	GMimeMessagePart *mpart;
	GMimeObject *subpart;
	gboolean has_md5;
	int i, n;
	
	print_depth (depth);
	type = g_mime_object_get_content_type (part);
	has_md5 = g_mime_object_get_header (part, "Content-Md5") != NULL;
	fprintf (stdout, "Content-Type: %s/%s%s", type->type, type->subtype,
		 has_md5 ? "; md5sum=" : "\n");
	
	if (GMIME_IS_MULTIPART (part)) {
		multipart = (GMimeMultipart *) part;
		
		n = g_mime_multipart_get_count (multipart);
		for (i = 0; i < n; i++) {
			subpart = g_mime_multipart_get_part (multipart, i);
			print_mime_struct (subpart, depth + 1);
		}
	} else if (GMIME_IS_MESSAGE_PART (part)) {
		mpart = (GMimeMessagePart *) part;
		
		if (mpart->message)
			print_mime_struct (mpart->message->mime_part, depth + 1);
	} else if (has_md5) {
		/* validate the Md5 sum */
		if (g_mime_part_verify_content_md5 ((GMimePart *) part))
			fprintf (stdout, "GOOD\n");
		else
			fprintf (stdout, "BAD\n");
	}
}

static void
test_parser (GMimeStream *stream)
{
	GMimeParser *parser;
	GMimeMessage *message;
	char *text;
	
	fprintf (stdout, "\nTesting MIME parser...\n\n");
	
	parser = g_mime_parser_new ();
	g_mime_parser_init_with_stream (parser, stream);
	
	ZenTimerStart (NULL);
	message = g_mime_parser_construct_message (parser);
	ZenTimerStop (NULL);
	ZenTimerReport (NULL, "gmime::parser_construct_message");
	
	g_object_unref (parser);
	
	ZenTimerStart (NULL);
	text = g_mime_object_to_string ((GMimeObject *) message);
	ZenTimerStop (NULL);
	ZenTimerReport (NULL, "gmime::message_to_string");
	/*fprintf (stdout, "Result should match previous MIME message dump\n\n%s\n", text);*/
	g_free (text);
	
#ifdef TEST_RAW_HEADER
	{
		char *raw;
		
		raw = g_mime_message_get_headers (message);
		fprintf (stdout, "\nTesting raw headers...\n\n%s\n", raw);
		g_free (raw);
	}
#endif
	
#ifdef TEST_PRESERVE_HEADERS
	{
		GMimeStream *stream;
		
		g_mime_header_list_set_stream (GMIME_OBJECT (message)->headers, NULL);
		
		fprintf (stdout, "\nTesting preservation of headers...\n\n");
		stream = g_mime_stream_file_new (stdout);
		/*g_mime_header_set_stream (GMIME_OBJECT (message)->headers, NULL);*/
		g_mime_header_list_write_to_stream (GMIME_OBJECT (message)->headers, stream);
		g_mime_stream_flush (stream);
		GMIME_STREAM_FILE (stream)->fp = NULL;
		g_object_unref (stream);
		fprintf (stdout, "\n");
	}
#endif
	
#ifdef TEST_WRITE_TO_STREAM
	stream = g_mime_stream_fs_new (2);
	g_mime_object_write_to_stream (GMIME_OBJECT (message), stream);
	g_mime_stream_flush (stream);
	GMIME_STREAM_FS (stream)->fd = -1;
	g_object_unref (stream);
#endif
	
#ifdef PRINT_MIME_STRUCT
	/* print mime structure */
	print_mime_struct (message->mime_part, 0);
#endif
	
	g_object_unref (message);
}



/* you can only enable one of these at a time... */
/*#define STREAM_BUFFER*/
/*#define STREAM_MEM*/
/*#define STREAM_MMAP*/

int main (int argc, char **argv)
{
	char *filename = NULL;
	GMimeStream *stream;
	int fd;
	
	g_mime_init (0);
	
	if (argc > 1)
		filename = argv[1];
	else
		return 0;
	
	if ((fd = open (filename, O_RDONLY, 0)) == -1)
		return 0;
	
#ifdef STREAM_MMAP
	stream = g_mime_stream_mmap_new (fd, PROT_READ, MAP_PRIVATE);
	g_assert (stream != NULL);
#else
	stream = g_mime_stream_fs_new (fd);
#endif /* STREAM_MMAP */
	
#ifdef STREAM_MEM
	istream = g_mime_stream_mem_new ();
	g_mime_stream_write_to_stream (stream, istream);
	g_mime_stream_reset (istream);
	g_object_unref (stream);
	stream = istream;
#endif
	
#ifdef STREAM_BUFFER
	istream = g_mime_stream_buffer_new (stream,
					    GMIME_STREAM_BUFFER_BLOCK_READ);
	g_object_unref (stream);
	stream = istream;
#endif
	
	test_parser (stream);
	
	g_object_unref (stream);
	
	g_mime_shutdown ();
	
	return 0;
}

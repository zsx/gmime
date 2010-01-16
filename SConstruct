# vim: ft=python expandtab

import os
from site_init import GBuilder, Initialize

opts = Variables()
opts.Add(PathVariable('PREFIX', 'Installation prefix', os.path.expanduser('~/FOSS'), PathVariable.PathIsDirCreate))
opts.Add(BoolVariable('DEBUG', 'Build with Debugging information', 0))
opts.Add(PathVariable('PERL', 'Path to the executable perl', r'C:\Perl\bin\perl.exe', PathVariable.PathIsFile))

env = Environment(variables = opts,
                  ENV=os.environ, tools = ['default', GBuilder])

Initialize(env)

GMIME_MAJOR_VERSION=2
GMIME_MINOR_VERSION=5
GMIME_MICRO_VERSION=0
GMIME_BINARY_AGE=0
GMIME_INTERFACE_AGE=0
GMIME_API_MAJOR=2
GMIME_API_MINOR=6
GMIME_API_VERSION_STRING="%d.%d" % (GMIME_API_MAJOR, GMIME_API_MINOR)
GMIME_VERSION_STRING="%d.%d.%d" % (GMIME_MAJOR_VERSION, GMIME_MINOR_VERSION, GMIME_MICRO_VERSION)

env['DOT_IN_SUBS'] = {'@PACKAGE_VERSION@': GMIME_VERSION_STRING,
					  '@GMIME_VERSION@': GMIME_VERSION_STRING,
					  '@GMIME_MAJOR_VERSION@': str(GMIME_MAJOR_VERSION),
					  '@GMIME_MINOR_VERSION@': str(GMIME_MINOR_VERSION),
					  '@GMIME_MICRO_VERSION@': str(GMIME_MICRO_VERSION),
                                          '@GMIME_BINARY_AGE@': str(GMIME_BINARY_AGE),
                                          '@GMIME_INTERFACE_AGE@': str(GMIME_INTERFACE_AGE),
					  '@VERSION@': GMIME_VERSION_STRING,
                                          '@GMIME_API_VERSION@': GMIME_API_VERSION_STRING,
                                          '@GMIME_LIBS@': "-lgmime -lws2_32 -liconv",
					  '@prefix@': env['PREFIX'],
 					  '@exec_prefix@': '${prefix}/bin',
					  '@libdir@': '${prefix}/lib',
					  '@includedir@': '${prefix}/include'}
env.DotIn('build/vs2008/config-win32.h', 'build/vs2008/config-win32.h.in')
env.DotIn('gmime/gmime-version.h', 'gmime/gmime-version.h.in')
env.DotIn('gmime.pc', 'gmime.pc.in')
gmimeinclude_HEADERS = Split("\
	gmime.h				\
	gmime-charset.h			\
	gmime-cipher-context.h		\
	gmime-content-type.h		\
	gmime-data-wrapper.h		\
	gmime-disposition.h		\
	gmime-encodings.h		\
	gmime-error.h			\
	gmime-filter.h			\
	gmime-filter-basic.h		\
	gmime-filter-best.h		\
	gmime-filter-charset.h		\
	gmime-filter-crlf.h		\
	gmime-filter-enriched.h		\
	gmime-filter-from.h		\
	gmime-filter-gzip.h		\
	gmime-filter-html.h		\
	gmime-filter-md5.h		\
	gmime-filter-strip.h		\
	gmime-filter-windows.h		\
	gmime-filter-yenc.h		\
	gmime-gpg-context.h		\
	gmime-header.h			\
	gmime-iconv.h			\
	gmime-iconv-utils.h		\
	gmime-message.h			\
	gmime-message-part.h		\
	gmime-message-partial.h		\
	gmime-multipart.h		\
	gmime-multipart-encrypted.h	\
	gmime-multipart-signed.h	\
	gmime-object.h			\
	gmime-param.h			\
	gmime-parser.h			\
	gmime-part.h			\
	gmime-pkcs7-context.h		\
	gmime-stream.h			\
	gmime-stream-buffer.h		\
	gmime-stream-cat.h		\
	gmime-stream-file.h		\
	gmime-stream-filter.h		\
	gmime-stream-fs.h		\
	gmime-stream-gio.h		\
	gmime-stream-mem.h		\
	gmime-stream-mmap.h		\
	gmime-stream-null.h		\
	gmime-stream-pipe.h		\
	gmime-utils.h			\
	gmime-version.h			\
	internet-address.h")

env.Alias('install', env.Install('$PREFIX/include/gmime-'+ GMIME_API_VERSION_STRING + '/gmime', map(lambda x: "gmime/" + x, gmimeinclude_HEADERS)))
env.Alias('install', env.Install('$PREFIX/lib', 'build/vs2008/DEBUG/gmime.lib'))
env.Alias('install', env.Install('$PREFIX/lib/pkgconfig', 'gmime.pc'))

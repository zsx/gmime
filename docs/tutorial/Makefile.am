.PHONY: html pdf

EXTRA_DIST = gmime-tut.sgml

html:
if HAVE_DOCBOOK
	if test -w $(srcdir); then \
	  (cd $(srcdir); \
	   db2html gmime-tut.sgml; \
	   test -d html && rm -r html; \
	   mv gmime-tut html); \
	fi
else
	echo "***"
	echo "*** Warning: Tutorial not built"
	echo "***"
endif

pdf:
if HAVE_DOCBOOK
	if test -w $(srcdir); then \
	  (cd $(srcdir); db2pdf gmime-tut.sgml); \
	fi
else
	echo "***"
	echo "*** Warning: Tutorial not built"
	echo "***"
endif

dist-hook: html
if HAVE_DOCBOOK
	cp -Rp $(srcdir)/html $(distdir)
else
	echo "*** DISTRIBUTION IS INCOMPLETE"
	echo "***"
endif


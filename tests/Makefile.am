## Process this file with automake to produce Makefile.in

SUBDIRS = .

INCLUDES = 				\
	-I$(top_srcdir) 		\
	-I$(top_srcdir)/util		\
	-DG_LOG_DOMAIN=\"gmime-tests\"	\
	-DG_DISABLE_DEPRECATED		\
	$(GMIME_CFLAGS)			\
	$(GLIB_CFLAGS)

AUTOMATED_TESTS =	\
	test-iconv	\
	test-streams	\
	test-cat	\
	test-headers	\
	test-mbox	\
	test-mime	\
	test-pgp	\
	test-pgpmime

MANUAL_TESTS =		\
	test-best	\
	test-parser 	\
	test-html 	\
	test-partial	\
	test-pkcs7	\
	test-smime

noinst_PROGRAMS = $(AUTOMATED_TESTS) $(MANUAL_TESTS)

DEPS = $(top_builddir)/gmime/libgmime-$(GMIME_API_VERSION).la
LDADDS = $(top_builddir)/gmime/libgmime-$(GMIME_API_VERSION).la $(GLIB_LIBS)

test_best_SOURCES = test-best.c
test_best_LDFLAGS = 
test_best_DEPENDENCIES = $(DEPS)
test_best_LDADD = $(LDADDS)

test_mime_SOURCES = test-mime.c testsuite.c testsuite.h
test_mime_LDFLAGS = 
test_mime_DEPENDENCIES = $(DEPS)
test_mime_LDADD = $(LDADDS)

test_headers_SOURCES = test-headers.c testsuite.c testsuite.h
test_headers_LDFLAGS = 
test_headers_DEPENDENCIES = $(DEPS)
test_headers_LDADD = $(LDADDS)

test_parser_SOURCES = test-parser.c
test_parser_LDFLAGS = 
test_parser_DEPENDENCIES = $(DEPS)
test_parser_LDADD = $(LDADDS)

test_mbox_SOURCES = test-mbox.c testsuite.c testsuite.h
test_mbox_LDFLAGS = 
test_mbox_DEPENDENCIES = $(DEPS)
test_mbox_LDADD = $(LDADDS)

test_streams_SOURCES = test-streams.c testsuite.c testsuite.h
test_streams_LDFLAGS = 
test_streams_DEPENDENCIES = $(DEPS)
test_streams_LDADD = $(LDADDS)

test_cat_SOURCES = test-cat.c testsuite.c testsuite.h
test_cat_LDFLAGS = 
test_cat_DEPENDENCIES = $(DEPS)
test_cat_LDADD = $(LDADDS)

test_html_SOURCES = test-html.c
test_html_LDFLAGS = 
test_html_DEPENDENCIES = $(DEPS)
test_html_LDADD = $(LDADDS)

test_iconv_SOURCES = test-iconv.c testsuite.c testsuite.h
test_iconv_LDFLAGS = 
test_iconv_DEPENDENCIES = $(DEPS)
test_iconv_LDADD = $(LDADDS)

test_partial_SOURCES = test-partial.c
test_partial_LDFLAGS = 
test_partial_DEPENDENCIES = $(DEPS)
test_partial_LDADD = $(LDADDS)

test_pgp_SOURCES = test-pgp.c testsuite.c testsuite.h
test_pgp_LDFLAGS = 
test_pgp_DEPENDENCIES = $(DEPS)
test_pgp_LDADD = $(LDADDS)

test_pgpmime_SOURCES = test-pgpmime.c testsuite.c testsuite.h
test_pgpmime_LDFLAGS = 
test_pgpmime_DEPENDENCIES = $(DEPS)
test_pgpmime_LDADD = $(LDADDS)

test_pkcs7_SOURCES = test-pkcs7.c testsuite.c testsuite.h
test_pkcs7_LDFLAGS = 
test_pkcs7_DEPENDENCIES = $(DEPS)
test_pkcs7_LDADD = $(LDADDS)

test_smime_SOURCES = test-smime.c testsuite.c testsuite.h
test_smime_LDFLAGS = 
test_smime_DEPENDENCIES = $(DEPS)
test_smime_LDADD = $(LDADDS)

EXTRA_DIST = test1.eml test2.eml test3.eml

VERBOSITY=-v

check-local: $(AUTOMATED_TESTS)
	failed_tests=""; \
	failed=0; \
	passed=0; \
 \
	for test in $(AUTOMATED_TESTS); do \
		testdatadir="data/`echo $${test} | sed -e 's/test-//'`"; \
		testdir="$(srcdir)/$${testdatadir}"; \
		if [ ! -d "$${testdir}" ]; then \
			testdir="$${testdatadir}"; \
		fi; \
		./$${test} $(VERBOSITY) $${testdir}; \
		if [ $$? -ne 0 ]; then \
			failed_tests="$${failed_tests}\n $${test}"; \
			failed=`expr $${failed} + 1`; \
		else \
			passed=`expr $${passed} + 1`; \
		fi; \
	done; \
 \
	echo "Results: $${passed} tests passed; $${failed} tests failed."; \
	if [ $${failed} -ne 0 ]; then \
		echo -e "Failed tests: $${failed_tests}"; \
	fi

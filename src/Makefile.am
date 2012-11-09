all: all-am
	@if test -n "${TEST}"; then \
		$(TESTS_ENVIRONMENT) ${TEST}; \
	fi

bin_PROGRAMS = test-gtk test-builder test-theming

test_gtk_SOURCES = test-gtk.c
test_gtk_CFLAGS = ${STRICT_CFLAGS} ${GLIB_CFLAGS} ${GTK_CFLAGS}
test_gtk_LDFLAGS = ${GLIB_LIBS} ${GTK_LIBS}

test_builder_SOURCES = test-builder.c
test_builder_CFLAGS = ${STRICT_CFLAGS} ${GLIB_CFLAGS} ${GTK_CFLAGS}
test_builder_LDFLAGS = ${GLIB_LIBS} ${GTK_LIBS}

test_theming_SOURCES = test-theming.c
test_theming_CFLAGS = ${STRICT_CFLAGS} ${GLIB_CFLAGS} ${GTK_CFLAGS}
test_theming_LDFLAGS = ${GLIB_LIBS} ${GTK_LIBS}

TESTS = ${bin_PROGRAMS}
bin_PROGRAMS = locopdf
locopdf_SOURCES = locopdf.cpp keyhandler.cpp choicebox.cpp entrybox.cpp dialogs.cpp database.cpp

# set the include path found by configure
INCLUDES= $(all_includes) @ECORE_CFLAGS@ @EDJE_CFLAGS@ @EPDF_CFLAGS@ @EVAS_CFLAGS@ @SQLITE_CFLAGS@

# the library search path.
locopdf_LDFLAGS = $(all_libraries) @ECORE_LIBS@ @EVAS_LIBS@ @EDJE_LIBS@ @EPDF_LIBS@ @SQLITE_LIBS@ -lecore_evas

include ../aminclude.am

bin_PROGRAMS=haddrscan_detector
haddrscan_detector_SOURCES=haddrscan_detector.c fields.c fields.h
haddrscan_detector_LDADD=-ltrap -lunirec -lnemea-common
haddrscan_detector_CXXFLAGS=-O2
haddrscan_detector_CFLAGS=-O2

EXTRA_DIST=haddrscan_aggregator.py README.md
bin_SCRIPTS=haddrscan_aggregator.py

pkgdocdir=${docdir}/haddrscan_detector
pkgdoc_DATA=README.md


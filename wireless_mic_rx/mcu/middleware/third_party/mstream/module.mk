MSTREAM_SRC = middleware/third_party/mstream/src
MSTREAM_LIB = middleware/third_party/mstream/lib

#LIBS += $(MSTREAM_LIB)/libmstream.a
LIBS += $(SOURCE_DIR)/middleware/third_party/mstream/lib/libmstream.a
C_FILES  += $(MSTREAM_SRC)/mstream_lib_sample.c



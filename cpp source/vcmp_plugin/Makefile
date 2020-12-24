CC       := g++
DIRS     := .
EXT      := cpp
PROJNAME := geoip04

INCDIRS = -I. -I/geoip-api-c/libGeoIP/
LIBDIRS = -L./geoip-api-c/libGeoIP/.libs/
STCLIBS = -lGeoIP
DYNLIBS = -ldl -lpthread
BASEOBJDIR = objdir

CFLAGS   = -Wall -O2 -lm -fPIC -c -D_WCHAR_T_EXISTS -DLINUX -D_SQ$(BITCOUNT) -DNDEBUG $(INCDIRS)

SOURCES  = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.$(EXT)))
OBJDIR   = $(BASEOBJDIR)/$(BUILDTYPE)$(BITCOUNT)
OBJS     = $(patsubst %.$(EXT), $(OBJDIR)/%.o, $(SOURCES))
PROG     = $(PROJNAME)$(BUILDTYPE)$(BITCOUNT).so
PROGPATH = $(OBJDIR)/$(PROG)

LDFLAGS = -Wl,-Bsymbolic $(LIBDIRS) -shared
LDLIBS = -Wl,-Bstatic $(STCLIBS) -Wl,-Bdynamic $(DYNLIBS)
COMMONFLAGS = -m$(BITCOUNT) 

ifeq ($(BUILDTYPE), dbg)
	COMMONFLAGS += -g
else
	COMMONFLAGS += -s
endif

build: build32 build64
build32:
	$(MAKE) BITCOUNT=32 BUILDTYPE=rel xbuild
build64:
	$(MAKE) BITCOUNT=64 BUILDTYPE=rel xbuild

debug: debug32 debug64
debug32:
	$(MAKE) BITCOUNT=32 BUILDTYPE=dbg xbuild
debug64:
	$(MAKE) BITCOUNT=64 BUILDTYPE=dbg xbuild

xbuild: $(PROGPATH)
	@mkdir -p build
	cp $(PROGPATH) build/$(PROG)

$(PROGPATH): $(OBJS)
	./prepare.sh $(COMMONFLAGS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $(COMMONFLAGS) -o $(PROGPATH) $(OBJS) $(LDLIBS)
	
-include $(OBJS:.o=.o.d)

$(OBJDIR)/%.o: %.$(EXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(COMMONFLAGS) -c $< -o $@
	$(CC) -MM $(CFLAGS) $< > $@.d
	@mv -f $@.d $@.d.tmp
	@sed -e 's|.*:|$@:|' < $@.d.tmp > $@.d
	@sed -e 's/.*://' -e 's/\\$$//' < $@.d.tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $@.d
	@rm -f $@.d.tmp

.PHONY: clean
	
clean:
	-@rm -R -f $(BASEOBJDIR)
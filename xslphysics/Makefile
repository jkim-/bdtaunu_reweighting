# directory configuration
# -----------------------

# objects to package into the shared library
OBJECTS = BXlnuKin.o BVlnuKin.o \
          ISGW2PseudoscalarFF.o CLNPseudoscalarFF.o \
          ISGW2VectorFF.o CLNVectorFF.o LinearQ2VectorFF.o \
          BPlnuDecayRate.o BVlnuDecayRate.o \
          BDss0FF.o BDss0lnuDecayRate.o \
          BD1primeFF.o BD1primelnuDecayRate.o \
          BD1FF.o BD1lnuDecayRate.o \
          BD2FF.o BD2lnuDecayRate.o

LIBNAME = libxslphysics.so

# external dependencies
# ---------------------

FF_REWEIGHT_ROOT = /home/dchao/workspace/bdtaunu_reweighting
UTILS_INCDIR = $(FF_REWEIGHT_ROOT)/utils
UTILS_LIBDIR = $(FF_REWEIGHT_ROOT)/utils

CLHEP_ROOT = /usr/local/CLHEP_2.3.3.1
CLHEP_INCDIR = $(CLHEP_ROOT)/include
CLHEP_LIBDIR = $(CLHEP_ROOT)/lib

INCFLAGS += -I$(UTILS_INCDIR) -I$(CLHEP_INCDIR)
LDFLAGS += -L $(UTILS_LIBDIR) -L $(CLHEP_LIBDIR) \
           -Wl,-rpath,$(UTILS_LIBDIR) -lreweight_utils \
           -Wl,-rpath,$(CLHEP_LIBDIR) -lCLHEP-2.3.3.1

# build rules
# -----------

CXX := g++
CXXFLAGS = -Wall -fPIC -pedantic -pthread -std=c++11 -O2

SRCS = $(wildcard *.cc)
BUILDDIR = build

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

lib : $(addprefix $(BUILDDIR)/, $(OBJECTS))
	if [ "$(shell uname)" = "Darwin" ]; then \
    SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/$(LIBNAME)"; \
  else \
    SHARED_LIB_FLAG="-shared -Wl,-soname,$(LIBNAME)"; \
  fi; \
	$(CXX) $(LDFLAGS) $${SHARED_LIB_FLAG} $^ -o $(LIBNAME)

$(BUILDDIR)/%.o : %.cc
$(BUILDDIR)/%.o : %.cc $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(notdir $(basename $(SRCS))))

clean : 
	@rm -f *~ $(BINARIES) $(BUILDDIR)/* $(LIBNAME)

cleanall : clean
	@rm -f $(DEPDIR)/*

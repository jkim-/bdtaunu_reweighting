BINARIES = test9

OBJECTS = 

FF_REWEIGHT_ROOT = /Users/dchao/workspace/bdtaunu_reweighting
INCDIR = $(FF_REWEIGHT_ROOT)/include
LIBDIR = $(FF_REWEIGHT_ROOT)/lib
UTILS_INCDIR = $(FF_REWEIGHT_ROOT)/utils
UTILS_LIBDIR = $(FF_REWEIGHT_ROOT)/utils

CLHEP_INCDIR = /usr/local/include
CLHEP_LIBDIR = /usr/local/lib

BOOST_ROOT = /usr/local/boost_1_56_0
BOOST_INCDIR = /usr/local/boost_1_56_0
BOOST_LIBDIR = $(BOOST_ROOT)/stage/lib

LIBPQ_ROOT = /usr/local/pgsql
LIBPQ_INCDIR = $(LIBPQ_ROOT)/include
LIBPQ_LIBDIR = $(LIBPQ_ROOT)/lib

INCFLAGS = -I$(INCDIR) -I$(UTILS_INCDIR) -I$(CLHEP_INCDIR) \
					 -I$(BOOST_INCDIR) -I$(LIBPQ_INCDIR)
LDFLAGS = -L $(LIBDIR) -L $(UTILS_LIBDIR) -L $(CLHEP_LIBDIR) \
					-L$(BOOST_LIBDIR) -L$(LIBPQ_LIBDIR) \
					-Wl,-rpath,$(LIBDIR) -lff_reweight \
					-Wl,-rpath,$(UTILS_LIBDIR) -lff_reweight_utils \
					-Wl,-rpath,$(CLHEP_LIBDIR) -lCLHEP-2.3.3.1 \
					-Wl,-rpath,$(BOOST_LIBDIR) -lboost_program_options \
					-Wl,-rpath,$(LIBPQ_LIBDIR) -lpq

CXX := g++
CXXFLAGS = -Wall -fPIC -pthread -std=c++11 -DNDEBUG -O2 -Wno-unused-local-typedef -Wno-redeclared-class-member

SRCS = $(wildcard *.cc)
BUILDDIR = build

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all : $(BINARIES)

gauss_legendre_example : $(addprefix $(BUILDDIR)/, gauss_legendre_example.o gauss_legendre.o)
	$(CXX) $(LDFLAGS) $^ -o $@

test% : $(addprefix $(BUILDDIR)/, test%.o $(OBJECTS))
	$(CXX) $(LDFLAGS) $^ -o $@
	
$(BUILDDIR)/%.o : %.cc
$(BUILDDIR)/%.o : %.cc $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

clean : 
	@rm -f *~ $(BINARIES) $(BUILDDIR)/* *.pdf *.gif *.png *.gv *.ps *.csv

cleanall : clean
	@rm -f $(DEPDIR)/*

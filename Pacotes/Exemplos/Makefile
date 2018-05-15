CXXFLAGS := -I.. -I../../Erros $(CXXFLAGS)

LDFLAGS := -L.. $(LDFLAGS)

LDLIBS := -lUtilitarios $(LDLIBS)

PROGS = data1

all: $(PROGS)

clean:
	rm -f $(PROGS) *.o *~

data1.o: data1.C ../Utilitarios/data.H ../Utilitarios/data_impl.H \
  ../Utilitarios/ignoradores.H ../Utilitarios/ignoradores_impl.H \
  ../../Erros/Erros/erros.H ../../Erros/Erros/erros_impl.H
